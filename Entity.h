#pragma once
#include "GL\freeglut.h"

#include <math.h>
#include <iostream>
#include <chrono>
#include <string>

class Player;
class Platform;

struct Texture {
	GLuint activeSprite;
	char* texturePath;
};



class Entity {
public:
	float posX = 0, posY = 0, velX = 0, velY = 0;
	float oldPosX, oldPosY;
	float newPosX, newPosY;
	bool lPressed, rPressed;
	bool collideX = false, collideY = false, collideAbove = false;
	bool collideEnemy = false;
	float width, height;
	bool grounded = true;
	bool onBlock = false;

	Texture entityTexture;
	
	bool debug = false;

	//Constructor for positioning the entity
	Entity(float x, float y, float w, float h, char* texturePath) {
		newPosX = x;
		newPosY = y;
		width = w;
		height = h;
		this->entityTexture.texturePath = texturePath;
	}

	float getX()
	{
		return newPosX;
	}

	float getY()
	{
		return newPosY;
	}

	void texturise(GLuint texture);
	void AABBResponse();
	void updatePos(float deltaTime);
	void drawEntity(float deltaTime = 0);
	void gravity(float deltaTime);
	void collision();
	void AABB(Entity& ent);
	void platformAABB(Platform& plat);
	void enemyAABB(Player& p);
	void spikeCollision(Entity& s);
};
