#pragma once
#include "GL\freeglut.h"
#include <math.h>
#include <iostream>
#include <chrono>
#include <string>



class Entity {
public:
	float posX = 0, posY = 0, velX = 0, velY = 0;
	float oldPosX, oldPosY;
	float newPosX, newPosY;
	bool lPressed, rPressed;
	bool collideX = false , collideY = false;
	float width, height;

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
	void Entity::AABB(Entity& ent);
};
