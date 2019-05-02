#pragma once
#include "GL\freeglut.h"
#include <math.h>
#include <iostream>
#include <chrono>
#include <string>


class Platform;

class Entity {
public:
	float posX = 0, posY = 0, velX = 0, velY = 0;
	float oldPosX, oldPosY;
	float newPosX, newPosY;
	bool lPressed, rPressed;
	bool collideX = false, collideY = false, collideAbove = false;
	float width, height;
	bool grounded = true;
	bool onBlock = false;

	GLuint activeSprite;

	bool debug = false;
	//Constructor for positioning the entity

	Entity(float x, float y, float w, float h) {
		newPosX = x;
		newPosY = y;
		width = w;
		height = h;
	}

	float getX()
	{
		return newPosX;
	}

	float getY()
	{
		return newPosY;
	}

	void AABBResponse();
	void updatePos(float deltaTime);
	void drawEntity(bool enemy,float deltaTime = 0);
	void gravity(float deltaTime);
	void collision();
	//void collisionResponse();
	void AABB(Entity& ent);
	void platformAABB(Platform& plat);
	void drawPlatform(bool moveX,bool moveY, float dt);
};
