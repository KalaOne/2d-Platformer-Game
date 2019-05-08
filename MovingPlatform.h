#pragma once
#include "Entity.h"
#include "Platform.h"

class MovingPlatform : public Entity {
private:
	int pos = 0;
	int travelDistance;
	bool moveUp = true, moveRight = true;
	float newPosX = 0.0, newPosY = 0.0;
	float platformVelX = 0.3, platformVelY = 0.3;

public:
	MovingPlatform(float xPos, float yPos, float w, float h, int td, char* texturePath) : Entity(xPos, yPos, w, h, texturePath)
	{
		travelDistance = td;
		newPosX = xPos;
		newPosY = yPos;
		width = w;
		height = h;
	}

	float getCurrentX()
	{
		return newPosX;
	}

	float getCurrentY()
	{
		return newPosY;
	}
	int getWidth()
	{
		return width;
	}

	int getHeight()
	{
		return height;
	}

	bool checkMoveUp()
	{
		return moveUp;
	}

	bool checkMoveRight()
	{
		return moveRight;
	}

	void drawPlatformRight(float dt);
	void drawPlatformUp(float dt);
	void updatePosX(int travelDistance, float dt);
	void updatePosY(int travelDistance, float dt);
};
