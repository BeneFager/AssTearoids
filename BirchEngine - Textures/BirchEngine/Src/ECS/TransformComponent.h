#pragma once
#include "Components.h"
#include "../Vector2D.h"
#include <math.h>


class TransformComponent : public Component
{
public:

	Vector2D position;
	Vector2D velocity;
	Vector2D forward;
	Vector2D center;

	int speed = 3;
	int TAngle = 0;


	// defaults for collider
	int height = 32;
	int width = 32;
	int scale = 1;


	TransformComponent()
	{
		position.x = 0;
		position.y = 0;
	}

	TransformComponent(int sc)
	{
		position.x = 400;
		position.y = 320;

		scale = sc;
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int h, int  w, int sc)
	{
		position.x = x;
		position.y = y;

		height = h;
		width = w;
		scale = sc;
		SetForward();
		SetCenter();
	}

	void init() override
	{
		velocity.Zero(); //kanske ta bort
	}

	void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}

	void UpdateForward(int angle)
	{
		//angle = angle * (3.1415 / 180);
		if(TAngle + angle >= 360) TAngle = 0;
		if(TAngle - angle <= -360) TAngle = 0;
		std::cout << TAngle << std::endl;
		//Vector2D dir = forward - center;
		forward.x = cos(angle) + GetCenter().x; //- dir.y * sin(angle);
		forward.y = sin(angle) + GetCenter().y; //+ dir.y * cos(angle);
		
	}

	//void NewSetForward()
	//{
	//	float hypo = sqrtf(center.)
	//}


	Vector2D NormalizeVector2D(Vector2D vector)
	{
		float magnitude = sqrtf(vector.x * vector.x + vector.y * vector.y);
		return Vector2D(vector.x / magnitude, vector.y / magnitude);

	}
	void SetForward()
	{
		forward.x = position.x + 16;
		forward.y = position.y;
	}

	void SetCenter()
	{
		center.x = position.x + 16;
		center.y = position.y + 16;
	}


	Vector2D GetCenter()
	{
		return center;
	}

	Vector2D GetForward()
	{
		return forward;
	}
};