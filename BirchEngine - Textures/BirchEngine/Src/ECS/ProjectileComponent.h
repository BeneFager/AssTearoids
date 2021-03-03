#pragma once

#include "ECS.h"
#include "Components.h"
#include "../Vector2D.h"

class ProjectileComponent : public Component
{
public:
	ProjectileComponent(int rng, int sp, Vector2D vel) : range(rng), speed(sp), velocity(vel)
	{

	}
	~ProjectileComponent()
	{

	}
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		transform->velocity = velocity;
		std::cout << transform->GetForward() << std::endl;
	}

	void update() override
	{
		distance += speed;

		if(distance > range)
		{
			std::cout << "Out of range" << std::endl;
			entity->destroy();
		}
		/*
		else if(transform->position.x > Game::camera.w || transform->position.x < Game::camera.w //fix this
				|| transform->position.y >Game::camera.h || transform->position.y < Game::camera.h //fix this
				) //fix this
		{
			std::cout << "Out of bounds" << std::endl;

			entity->destroy();
		}
		*/
	}

private:
	TransformComponent *transform;
	int range = 0;
	int speed = 0;
	int distance = 0;
	Vector2D velocity;


};