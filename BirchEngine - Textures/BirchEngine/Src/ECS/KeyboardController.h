#pragma once
#include "../Game.h"
#include "ECS.h"
#include "Components.h"
#include "../AssetManager.h"



class KeyboardController : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	int count;
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}
	/// <summary>
	/// Input handling
	/// </summary>
	void update() override
	{
		//Pilla

		transform->velocity.x *= .99f;
		transform->velocity.y *= .99f;

		SDL_PumpEvents();
		transform->SetCenter();
		transform->UpdateForward(transform->TAngle);

		state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_W]) {
			transform->velocity = transform->GetForward();
			isPressingW = true;
		}
		if (state[SDL_SCANCODE_A]) {
			transform->TAngle += 4;
			transform->UpdateForward(transform->TAngle);
			sprite->turnSpeed = transform->forwardToDegrees(transform->GetForward());
		}
		if (state[SDL_SCANCODE_D]) {
			transform->TAngle -= 4;
			transform->UpdateForward(transform->TAngle);
			sprite->turnSpeed = transform->forwardToDegrees(transform->GetForward());
		}
		if (state[SDL_SCANCODE_SPACE]) {
			if (Game::Time < timeToNextShot) return;
			transform->SetCenter();
			Game::assets->CreateProjectile(transform->GetCenter(), transform->NormalizeVector2D(
				(transform->GetForward() + transform->GetCenter()) - transform->GetCenter()) + transform->velocity,
				500, 5, "point");
			timeToNextShot = Game::Time + ShootCD;
			std::cout << timeToNextShot << "   " << Game::Time << std::endl;
		}

		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_0:
				std::cout << transform->position << "pos" << std::endl;
				/*std::cout << transform->GetForward() << " forward" << std::endl; */
				std::cout << transform->GetCenter() << " Center" << std::endl;
				break;
			//case SDLK_ESCAPE:
				//Game::isRunning = false;
				//Game::isPaused = !Game::isPaused;
				//break;
			default:
				break;
			}
		}
	}

private:
	const Uint8* state;
	const float ShootCD = 0.5f;
	float timeToNextShot = 0;
	bool isPressingW = false;
};