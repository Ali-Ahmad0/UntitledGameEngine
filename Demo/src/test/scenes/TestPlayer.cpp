#include "TestPlayer.hpp"

void TestPlayer::Ready() 
{
	// Load player texture
	texture = TextureManager::LoadTexture("src/test/assets/character.png");
	preview = TextureManager::LoadTexture("src/test/assets/preview.png");
		
	// Create player entity
	player = ECS::CreateEntity();

	// Add components
	ECS::AddComponent(player, Transform(Vector2(32, 384), 0.0, 3));
	ECS::AddComponent(player, Sprite(texture, 3, 4, 6, 0));
	ECS::AddComponent(player, AABB(Vector2(8, 20), Vector2(12, 12)));
	ECS::AddComponent(player, Movement());
	
	transform = ECS::GetComponent<Transform>(player);

	// Configure sprite animations
	sprite = ECS::GetComponent<Sprite>(player);

	sprite->addAnim("idle_right", { 10 });
	sprite->addAnim("idle_left", { 7 });
	sprite->addAnim("idle_up", { 4 });
	sprite->addAnim("idle_down", { 1 });

	sprite->addAnim("walk_right", { 9, 10, 11 });
	sprite->addAnim("walk_left", { 6, 7, 8 });
	sprite->addAnim("walk_up", { 3, 4, 5 });
	sprite->addAnim("walk_down", { 0, 1, 2 });

	sprite->setAnim("idle_right");
	 
	movement = ECS::GetComponent<Movement>(player);

	// Set camera boundaries
	Camera::boundaries = { 0, 320, 0, 240 };
}

void TestPlayer::Update(double delta) 
{
	// Basic input
	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_LEFT])
	{
		direction = Vector2(-1, 0);
		sprite->setAnim("walk_left");
	}
	else if (state[SDL_SCANCODE_RIGHT])
	{
		direction = Vector2(1, 0);
		sprite->setAnim("walk_right");
	}
	else if (state[SDL_SCANCODE_UP])
	{
		direction = Vector2(0, -1);
		sprite->setAnim("walk_up");
	}
	else if (state[SDL_SCANCODE_DOWN])
	{
		direction = Vector2(0, 1);
		sprite->setAnim("walk_down");
	}
	else
	{
		// Set idle animation based on the last direction
		if (direction.x == -1)
		{
			sprite->setAnim("idle_left");
		}
		else if (direction.x == 1)
		{
			sprite->setAnim("idle_right");
		}
		else if (direction.y == -1)
		{
			sprite->setAnim("idle_up");
		}
		else if (direction.y == 1)
		{
			sprite->setAnim("idle_down");
		}
	}

	movement->direction = direction;
	movement->speed.x = 128.0f * (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_RIGHT]
								|| state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_DOWN]);

	movement->speed.y = movement->speed.x;

	// Upadate camera position
	Camera::SetOffset(Vector2(transform->position.x - 320, transform->position.y - 240));
}

void TestPlayer::Events(SDL_Event event) 
{
	switch (event.key.keysym.sym)
	{
	// Stress test
	case SDLK_RETURN:

		// Spawn entities in random positions
		srand((unsigned int)(time(nullptr)));
		try
		{
			for (int i = 0; i < 1000; i++)
			{
				EntityID entity = ECS::CreateEntity();

				// Set random positions within the screen bounds (640 x 480)
				float randomX = (float)(rand() % 640);
				float randomY = (float)(rand() % 480) - 32;

				// Assign components to the entity
				ECS::AddComponent(entity, Transform(Vector2(randomX, randomY), 0, 3));
				ECS::AddComponent(entity, Sprite(preview));
			}
		}

		catch (const std::runtime_error& e)
		{
			fprintf(stderr, "[ERROR]: %s\n", e.what());
		}

		break;
	default:
		 
		break;
	}
}