#include "GL\freeglut.h"
#include <math.h>
#include <iostream>
#include <chrono>
#include <string>
#include "Level.h"


class Platform;

class Entity {
public:
	float posX = 0, posY = 0, velX = 0, velY = 0;
	float oldPosX, oldPosY;
	bool grounded = true;
	bool lPressed = false;
	bool rPressed = false;
	float newPosX, newPosY;
	bool collidingXLeft = false, collidingXRight = false, collidingAboveLeft = false, collidingAboveRight = false, collidingBelowLeft = false, collidingBelowRight = false;
	Level* level;
	bool enemyMove = true;

	bool debug = false;
	//Constructor for positioning the entity

	Entity(float x, float y, Level& level) {
		newPosX = x;
		newPosY = y;
		this->level = &level;
	}

	void updatePos(float deltaTime);
	void drawEntity(Level level,bool enemy,float deltaTime);
	void gravity(float deltaTime);
	void collision();
	//void collisionResponse();
	void Entity::AABB(Platform p);
};
