#include "Math.h"
#include "raylib.h"
#include <vector>
#include "rlImGui.h"



//
//Vector2 LimitMagnitude(Vector2 vec, float maxLength)
//{
//	float length = Length(vec);
//	if (length > maxLength)
//		return vec * maxLength / length;
//	else return vec;
//}
//
// 
//void Seek(Vector2 agentPosition, Vector2 agentVelocity, Vector2 targetPosition, float desiredSpeed, float acceleration)
//{
//	Vector2 desiredVelocity = Normalize(targetPosition - agentPosition) * desiredSpeed;
//	Vector2 desiredChange = desiredChange - (agentVelocity);
//	return Normalize((desiredChange) * acceleration);
//}
//Vector2 Seek(const Vector2& agentPosition, const Vector2& agentVelocity, const Vector2& targetPosition, const float desiredSpeed, const float acceleration)
//{
//	Vector2 displacementToTarget = targetPosition - agentPosition;
//	float distance = Length(displacementToTarget);
//	Vector2 directionToTarget = displacementToTarget / distance;	// Divide a vector by its length to get a Normalized (lengh is 1) vector in the same direction
//	Vector2 desiredVelocity = directionToTarget * desiredSpeed;		// Scale a Normalized vector by a scalar to give it the magnitude of that scalar
//	Vector2 deltaV = desiredVelocity - agentVelocity;				// Determine the change in velocity we need to achieve the desired velocity
//	Vector2 outputAcceleration = Normalize(deltaV) * acceleration;	// Create an acceleration vector in the direction of the desired change in velociity
//	return outputAcceleration;
//}