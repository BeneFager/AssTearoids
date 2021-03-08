#pragma once

#include "ECS.h"
#include "Components.h"
#include "../Vector2D.h"
#include "../AssManager.h"


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
		std::cout << "spawning more and destroying" << std::endl;
		entity->destroy();
	}

private:
	AssManager* ass;
	TransformComponent* transform;
	int speed;
	float rotSpeed;
	Vector2D velocity;
};
