#pragma once
#include "../../../src/scene/SceneManager.hpp"
#include "../../../src/texture/TextureManager.hpp"
#include "../../../src/tilemap/Tilemap.hpp"

class TestPlayer : public IScene 
{
public:
	void Ready() override;
	void Update(double delta) override;
	void Events(SDL_Event event) override;
	
private:
	EntityID player;
	SDL_Texture* texture;

	Vector2 direction;

	Movement* movement;
	Sprite* sprite;
};