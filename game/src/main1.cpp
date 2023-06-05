//#include <rlImGui.h>
//#include "Math.h"
//#include "Agent.h"
//#include <vector>
//
//#define SCREEN_WIDTH 1280
//#define SCREEN_HIGHT 720
//
//bool CheckCollisionCircle(const Vector2& lineStart, const Vector2& lineEnd, const Vector2& circleCenter, float circleRadius)
//{
//	Vector2 nearestPoint = NearestPoint(lineStart, lineEnd, circleCenter);
//	float distanceToCircleSq = Distance(nearestPoint, circleCenter);
//	return (distanceToCircleSq <= circleRadius * circleRadius);
//}
//
//Agent myAgent;
//Agent obstacle;
//
//std::vector<Agent*> agents;
//
//int main(void)
//{
//	myAgent.rb.position = { 500, 500 };
//	myAgent.radius = 50;
//	agents.push_back(&myAgent);
//
//	obstacle.color = RED;
//	agents.push_back(&obstacle);
//
//	InitWindow(SCREEN_WIDTH, SCREEN_HIGHT, "Sunshine");
//	rlImGuiSetup(true);
//	SetTargetFPS(60);
//
//	bool useGUI = false;
//	while (!WindowShouldClose())
//	{
//		BeginDrawing();
//		ClearBackground(RAYWHITE);
//
//		const float dt = GetFrameTime();
//
//		myAgent.rb.acceleration = myAgent.rb.acceleration + Seek(myAgent.rb.position, myAgent.rb.velocity, obstacle.rb.velocity, myAgent.speedMax, myAgent.accelerationMax);
//		obstacle.rb.position = GetMousePosition();
//
//		Vector2 agentDirection = Normalize(obstacle.rb.position - myAgent.rb.position);
//		Vector2 rightWhisker = Rotate(agentDirection, 30.f * DEG2RAD) * myAgent.visionRange;
//		Vector2 leftWhisker = Rotate(agentDirection, -30.f * DEG2RAD) * myAgent.visionRange;
//
//		Vector2 nearestPoint = NearestPoint(myAgent.rb.position, myAgent.rb.position + rightWhisker, obstacle.rb.position);
//
//		bool rightCollision = CheckCollisionCircle(myAgent.rb.position, myAgent.rb.position + rightWhisker, obstacle.rb.position, obstacle.radius);
//
//		DrawLineV(myAgent.rb.position, myAgent.rb.position + agentDirection * 100, BLACK);
//		DrawLineV(myAgent.rb.position, myAgent.rb.position + rightWhisker * 100, (rightCollision) ?  RED : GREEN);
//		DrawLineV(myAgent.rb.position, myAgent.rb.position + leftWhisker * 100, GREEN);
//
//		for (Agent* agent : agents)
//		{
//			agent->rb.acceleration = LimitMagnitude(agent->rb.acceleration, agent->accelerationMax);
//			agent->rb.velocity = LimitMagnitude(agent->rb.velocity, agent->speedMax);
//			Update(agent->rb, dt);
//			agent->Draw();
//		}
//
//
//		if (IsKeyPressed(KEY_GRAVE)) useGUI = !useGUI;
//		if (useGUI)
//		{
//			rlImGuiBegin();
//			rlImGuiEnd();
//		}
//
//		DrawFPS(10, 10);
//		DrawText("Press ~ to open/close GUI", 10, 30, 20, GRAY);
//
//
//		EndDrawing();
//	}
//
//
//
//	}
//