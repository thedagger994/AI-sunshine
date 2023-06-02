#include "rlImGui.h"
#include "Math.h" 
#include <vector>
// When using #include, the default location during compile-time is to start from 
// the location of the file the include statement is in, then look at additional 
//include directories in the project settings So Math.h is next to main.cpp

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Vector2 LimitMagnitude(Vector2 vec, float maxLength)
{
	float length = Length(vec);
	if (length > maxLength)
		return vec * maxLength / length;
	else return vec;
}

//Use the output of this function to add some acceleration to an Agent's velocity
Vector2 Seek(const Vector2& agentPosition, const Vector2& agentVelocity, const Vector2& targetPosition, const float desiredSpeed, const float acceleration)
{
	Vector2 displacementToTarget = targetPosition - agentPosition;
	float distance = Length(displacementToTarget);
	Vector2 directionToTarget = displacementToTarget / distance; // Divide a vector by its length to get a Normalized (lengh is 1) vector in the same direction
	Vector2 desiredVelocity = directionToTarget * desiredSpeed; // Scale a Normalized vector by a scalar to give it the magnitude of that scalar
	Vector2 deltaV = desiredVelocity - agentVelocity; // Determine the change in velocity we need to achieve the desired velocity
	Vector2 outputAcceleration = Normalize(deltaV) * acceleration; // Create an acceleration vector in the direction of the desired change in velociity
	return outputAcceleration;
}

//Physics state -- used in physics update
struct Rigidbody
{
	Vector2 pos = { 0 };
	Vector2 vel = { 0 };
	Vector2 accel = { 0 };
	float orientationRad = 0;
};

void UpdateKinematics(Rigidbody& rb, const float dt)
{
	rb.pos = rb.pos + rb.vel * dt + rb.accel * 0.5f * dt * dt; // kinematic equation
	rb.vel = rb.vel + rb.accel * dt; // update velocity to the final velocity at the end of the frame
}

struct Agent : public Rigidbody
{
	//Visuals -- how it looks
	Texture2D sprite;
	Color tint = WHITE;

	//Stats -- determine its capabilities
	float speedMax = 300; // maximum linear velocity of this agent
	float accelMax = 800; // maximum linear acceleration of this agent

	void Draw()
	{
		Rectangle src = { 0,0,sprite.width, sprite.height };
		Rectangle dst = { pos.x, pos.y, sprite.width, sprite.height };
		DrawTexturePro(sprite, src, dst, { sprite.width * 0.5f, sprite.height * 0.5f }, orientationRad * RAD2DEG, tint);

		//Draw velocity and acceleration
		DrawLineV(pos, pos + vel * 0.5, RED);
		DrawLineV(pos, pos + accel * 0.5, GREEN);
	}


	//Agent class contains helpful functions to pass some of the agent's information to Seek, making it easier to use
	//If you set different speedMax and accelMax stats for different agents, they will respond differently to the same function
	void AddSeek(Vector2 target, float power)
	{
		accel = accel + Seek(pos, vel, target, speedMax, accelMax * power);
	}
};

Vector2 WraparoundScreen(Vector2 position)
{
	return Vector2{
		fmodf(position.x + SCREEN_WIDTH, SCREEN_WIDTH),
		fmodf(position.y + SCREEN_HEIGHT, SCREEN_HEIGHT)
	};
}
static float globalMaxSpeed = 300;
static float globalMaxAcceleration = 800;

std::vector<Agent*> agents; // our container of agent references
Agent a;
Agent b;

int main(void)
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Joss's Game3001 Kinematic Physics example");
	rlImGuiSetup(true); // To get ImGUI ready

	//When debugging, the file path for files you load at runtime defaults to the location of the .vcxproj file (the VS project)
	// out of the folder where the vcxproj file is, into game/assets/textures...
	Texture2D agentTex = LoadTexture("../game/assets/textures/plane.png"); // LoadTexture depends on InitWindow being called.
	a.sprite = agentTex;
	a.pos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	a.accelMax = 2000;
	a.speedMax = 3000;

	b.sprite = agentTex;
	b.pos = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4 };
	b.tint = BLUE;

	b.sprite = LoadTexture("../game/assets/textures/plane.png");

	//add initial agents to the container
	agents.push_back(&a);
	agents.push_back(&b);

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		const float dt = GetFrameTime();
		BeginDrawing();
		ClearBackground(RAYWHITE);

		rlImGuiBegin(); // to make any ImGUI window appear, start here, 
		//then call the relevant functions for each element before calling rlImGuiEnd()

		if (ImGui::DragFloat("Max Speed", &globalMaxSpeed, 1, 0, 2000));
		{
			// change max speed of all agents if the slider is moved
			for (Agent* agent : agents)
			{
				agent->speedMax = globalMaxSpeed;
			}
		}
		if (ImGui::DragFloat("Max Acceleration", &globalMaxAcceleration, 1, -2000, 2000))
		{
			// change max acceleration of all agents if the slider is moved
			for (Agent* agent : agents)
			{
				agent->accelMax = globalMaxAcceleration;
			}
		}
		rlImGuiEnd(); // to make any ImGUI window appear, end with this

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			for (Agent* agent : agents)
			{
				agent->AddSeek(GetMousePosition(), 1.0);//make all Seek
			}
		}

		//Update each agent
		for (Agent* agent : agents)
		{
			//Limit magnitudes according to the agent's stats BEFORE physics update
			agent->vel = LimitMagnitude(agent->vel, agent->speedMax);
			agent->accel = LimitMagnitude(agent->accel, agent->accelMax);

			UpdateKinematics(*agent, dt); //Do kinematic simulation for this agent

			agent->pos = WraparoundScreen(agent->pos); //Keep it on the screen
			agent->Draw(); // Draw it to the screen

			agent->accel = { 0 }; // reset the acceleration experienced by this agent to 0 
			//AFTER Physics update OR at the beginning of the game loop BEFORE you add Seek and Flee etc.
			//Some other code will set it again next frame. If not, it will still keep its velocity
		}

		DrawFPS(10, 10);
		EndDrawing();
	}

	rlImGuiShutdown();
	CloseWindow();
	return 0;
}