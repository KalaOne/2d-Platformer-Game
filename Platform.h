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
	int pos = 0;
	bool moveUp = true, moveRight = true;
	float newPosX = 0.0, newPosY = 0.0;
	float platformVelX = 0.5, platformVelY = 0.5;
public:

	Platform(float xPos, float yPos, float w, float h, char* texturePath) : Entity(xPos, yPos, w, h, texturePath)
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

	

	void updatePosX(int travelDistance, float dt);
	void updatePosY(int travelDistance, float dt);
	//void drawPlatform(int travelDistance, bool x, bool y, float dt);
	//void drawPlatFromMap(float dt);
	
};
