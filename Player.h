#pragma once
#include "Entity.h"

class Player : public Entity
{
	bool grounded = true;

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
	
	void gravity(float deltaTime);
};
