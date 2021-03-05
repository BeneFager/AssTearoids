#pragma once

#include "ECS.h"
#include "Components.h"
#include "../Vector2D.h"


class AsstearoidComponent : public Component
{
public:
	AsstearoidComponent() = default;
	AsstearoidComponent(Vector2D vel) : velocity(vel)
	{
	}
	~AsstearoidComponent()
	{

	}


	void init()override
	{
		transform = &entity->getComponent<TransformComponent>();
		transform->velocity = velocity;
	}

	void update() override
	{

	}

	void OnDestroy()
	{
		if(SP > 0)
		{
			//spawn more
		}
		std::cout << "spawning more and destroying" << std::endl;
		entity->destroy();
	}
	
private:
	TransformComponent* transform;
	int speed;
	float rotSpeed;
	int SP = 0;
	Vector2D velocity;
};
