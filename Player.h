#pragma once
#include "Entity.h"

class Player : public Entity
{


public:

	Player(float x, float y, float w, float h) : Entity(x, y, w, h){}

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
