#include "GL\freeglut.h"
#include <math.h>
#include <iostream>
#include <chrono>
#include <string>
#include "Level.h"


class Entity {
public:
	float posX = 0, posY = 0, velXL = 0, velXR = 0, velYU = 0, velYD = 0;
	bool grounded = true;
	bool lPressed = false;
	bool rPressed = false;
	float newPosX, newPosY;
	bool collidingXLeft = false, collidingXRight = false, collidingAboveLeft = false, collidingAboveRight = false, collidingBelowLeft = false, collidingBelowRight = false;;
	Level* level;

	//Constructor for positioning the entity

	Entity(float x, float y, Level& level) {
		newPosX = x;
		newPosY = y;
		this->level = &level;
	}

	void updatePos(float deltaTime);
	void drawEntity(float deltaTime);
	void gravity();
	void collision();
	void collisionResponse(int oldPosX, int oldPosY);
};