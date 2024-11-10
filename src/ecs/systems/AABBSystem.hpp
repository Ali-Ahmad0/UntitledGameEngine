#pragma once

#include "BaseSystem.hpp"
#include "../ECS.hpp"

struct AABBSystem : public BaseSystem
{
	void update(ECS& ecs)
	{
		for (auto it1 = entities.begin(); it1 != entities.end(); ++it1)
		{
			EntityID e1 = *it1;

			AABB* box1 = ecs.GetComponent<AABB>(e1); Transform* t1 = ecs.GetComponent<Transform>(e1);

            Vector2 center1 = Vector2::multiply(box1->center, (float)t1->scale);
            center1 = center1.add(t1->position);
			
			// Calculate new boundaries for box1
            Vector2 minA = Vector2::subtract(center1, box1->dimensions.multiply((float)t1->scale / 2));
            Vector2 maxA = Vector2::add(center1, box1->dimensions.multiply((float)t1->scale / 2));

            box1->min = minA;
            box1->max = maxA;

            for (auto it2 = std::next(it1); it2 != entities.end(); ++it2)
            {
                EntityID e2 = *it2;

                AABB* box2 = ecs.GetComponent<AABB>(e2); Transform* t2 = ecs.GetComponent<Transform>(e2);

                Vector2 center2 = Vector2::multiply(box2->center, ((float)t2->scale));
                center2 = center2.add(t2->position);

                // Calculate new boundaries for box2
                Vector2 minB = Vector2::subtract(center2, box2->dimensions.multiply((float)t1->scale / 2));
                Vector2 maxB = Vector2::add(center2, box2->dimensions.multiply((float)t1->scale / 2));

                box2->min = minB;
                box2->max = maxB;

                // Check for collisions between 2 bounding boxes
                if (box1->intersects(*box2)) 
                {
                    // Resolve collisions
                    resolve(box1, t1, box2, t2);
                }
            }
		}
	}

    void resolve(AABB* box1, Transform* t1, AABB* box2, Transform* t2) 
    {
        // Seperate colliding boxes
        if (box1->isSolid && box2->isSolid)
        {
            // Calculate overlap on the x and y axes
            float overlapX = std::min(box1->max.x - box2->min.x, box2->max.x - box1->min.x);
            float overlapY = std::min(box1->max.y - box2->min.y, box2->max.y - box1->min.y);

            // Find the axis with the least overlap and move the entities along that axis
            if (overlapX < overlapY)
            {
                // Move the entities apart along the x-axis
                if (t1->position.x < t2->position.x)
                {
                    if (box1->isRigid)
                    {
                        t1->position.x -= overlapX / 2;
                    }
                    if (box2->isRigid)
                    {
                        t2->position.x += overlapX / 2;
                    }
                }
                else
                {
                    if (box1->isRigid)
                    {
                        t1->position.x += overlapX / 2;
                    }
                    if (box2->isRigid)
                    {
                        t2->position.x -= overlapX / 2;
                    }
                }
            }
            else
            {
                // Move the entities apart along the y-axis
                if (t1->position.y < t2->position.y)
                {
                    if (box1->isRigid)
                    {
                        t1->position.y -= overlapY / 2;
                    }
                    if (box2->isRigid)
                    {
                        t2->position.y += overlapY / 2;
                    }
                }
                else
                {
                    if (box1->isRigid)
                    {
                        t1->position.y += overlapY / 2;
                    }
                    if (box2->isRigid)
                    {
                        t2->position.y -= overlapY / 2;
                    }
                }
            }
        }
        
    }
};