#include "GL\freeglut.h"
#include <math.h>
#include <iostream>
#include <chrono>
#include <string>


class Entity {
public:
	float posX = 0, posY = 0, velX = 0, velY = 0;
	bool grounded = true;
	bool lPressed = false;
	bool rPressed = false;
	float newPosX, newPosY;

	//Constructor for positioning the entity
	Entity() {
		posX = 0;
		posY = 0;
	}

	Entity(float x, float y) {
		posX = x;
		posY = y;
	}

	void updatePos(float deltaTime);
	void drawEntity(float deltaTime);
};