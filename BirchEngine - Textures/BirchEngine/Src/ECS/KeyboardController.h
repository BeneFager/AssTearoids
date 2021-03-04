#pragma once
#include "../Game.h"
#include "ECS.h"
#include "Components.h"
#include "../AssetManager.h"



class KeyboardController : public Component
{
public:
	TransformComponent *transform;
	SpriteComponent *sprite;

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
		//Fixa rotation på spelaren
		//fixa skjut

		//whileLoop eller något? (_8(I)
		if(Game::event.type == SDL_KEYDOWN)
		{
			switch(Game::event.key.keysym.sym)
			{
				case SDLK_w:

					transform->SetCenter();
					transform->UpdateForward(transform->TAngle);
					//transform->velocity -= transform->NormalizeVector2D(transform->GetForward() - transform->GetCenter());
					transform->velocity -= transform->GetForward();

					break;
				case SDLK_s:
					transform->UpdateForward(transform->TAngle);
					transform->velocity = transform->NormalizeVector2D(transform->GetForward() - transform->GetCenter());

					break;
				case SDLK_a:
					transform->TAngle += 4;
					transform->UpdateForward(transform->TAngle);
					sprite->turnSpeed = transform->forwardToDegrees(transform->GetForward());
					//std::cout << sprite->turnSpeed << std::endl;
					//std::cout << transform->GetForward() << std::endl;
					break;
				case SDLK_d:

					transform->TAngle -= 4;
					transform->UpdateForward(transform->TAngle);
					sprite->turnSpeed = transform->forwardToDegrees(transform->GetForward());
					//std::cout << sprite->turnSpeed << std::endl;
					//std::cout << transform->GetForward() << std::endl;
					break;
				case SDLK_SPACE:
					Game::assets->CreateProjectile(transform->GetCenter(), transform->NormalizeVector2D(transform->GetCenter() - (transform->GetForward() + transform->GetCenter())), 500, 5, "point");
					break;
				case SDLK_0:
					std::cout << transform->GetForward() << " forward" << std::endl;
					std::cout << transform->GetCenter() << " Center" << std::endl;
				default:
					break;
			}
		}

		if(Game::event.type == SDL_KEYUP)
		{
			switch(Game::event.key.keysym.sym)
			{
				case SDLK_w:
					transform->velocity.Zero();
					break;
				case SDLK_s:
					transform->velocity.Zero();
					break;
				case SDLK_ESCAPE:
					Game::isRunning = false;
					break;
				default:
					break;
			}
		}
	}


};