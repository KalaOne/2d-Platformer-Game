#pragma once
#include "Entity.h"

class Player : public Entity
{


public:

	Player(float x, float y, float w, float h, char* texturePath) : Entity(x, y, w, h, texturePath){}

	bool isGrounded()
	{
		return grounded;
	}

	void ungroundPlayer()
	{
		grounded = false;
	}

	bool isOnBlock()
	{
		return onBlock;
	}

	void unblockPlayer()
	{
		onBlock = false;
	}
	
	void gravity(float deltaTime);
};
