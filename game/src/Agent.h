#pragma once
#include "raylib.h"
#include "RigidBody.h"

struct Agent
{
	RigidBody rb;
	float speedMax;
	float accelerationMax;
	Vector2 facingDirection;

	Color color = BLUE;
	float radius = 100.0f;

	float visionRange = 200.0f;

	void Draw()
	{
		DrawCircleV(rb.position, 100.0f, color);
	}
};