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
	bool moveX = true, moveY = true, moveRight = true;
	float newPosX = 0.0, newPosY = 0.0;
	float platformVelX = 0.01, platformVelY = 0.01;
public:

	Platform(float xPos, float yPos, float w, float h) : Entity(xPos, yPos, w, h)
	{
		newPosX = xPos;
		newPosY = yPos;
		width = w;
		height = h;
	}

	int getWidth()
	{
		return width;
	}

	int getHeight()
	{
		return height;
	}

	

	void updatePosX(int travelDistance, bool right, float dt);
	void updatePosY(int travelDistance, bool up, float dt);
	void drawPlatform(int travelDistance, bool x, bool y, float dt);
	void drawPlatFromMap(float dt);
	
};
