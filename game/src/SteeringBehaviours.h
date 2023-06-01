#include "Math.h"
#include "raylib.h"

void Seek(Vector2 agentPosition, Vector2 agentVelocity, Vector2 targetPosition, float desiredSpeed, float acceleration)
{
	Vector2 desiredVelocity = Normalize(targetPosition - agentPosition) * desiredSpeed;
	Vector2 desiredChange = desiredChange - (agentVelocity);
	return Normalize((desiredChange) * acceleration);
}