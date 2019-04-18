#pragma once
#include "GL\freeglut.h"
#include <math.h>
#include <iostream>
#include <chrono>
#include <string>
#include "Entity.h"


class Platform : public Entity
{
private:
	int currentDistance = 0;
	bool moveX = true, moveY = true;
	float newPosX = 0.0, newPosY = 0.0;
	float platformVelX = 0.01, platformVelY = 0.01;
public:

	Platform(float w, float h, float xPos, float yPos) : Entity(xPos, yPos, w, h)
	{
		width = w;
		height = h;
		newPosX = xPos;
		newPosY = yPos;
	}

	int getWidth()
	{
		return width;
	}

	int getHeight()
	{
		return height;
	}

	

	void updatePosX(int travelDistance, bool right, float deltaTime);
	void updatePosY(int travelDistance, bool up, float deltaTime);
	void drawPlatform(int travelDistance, bool x, bool y, float deltaTime);
	/*void collisionAABB(Entity ent);*/
	
};
