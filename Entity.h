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
	bool collidingXLeft = false, collidingXRight = false, collidingYLeft = false, collidingYRight = false;
	Level* level;

	//Constructor for positioning the entity

	Entity(float x, float y, Level& level) {
		posX = x;
		posY = y;
		this->level = &level;
	}

	void updatePos(float deltaTime);
	void drawEntity(float deltaTime);
	void collision();
	void collisionResponse(int oldPosX, int oldPosY);
};