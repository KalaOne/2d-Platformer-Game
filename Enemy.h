#pragma once
#include "Entity.h"


class Enemy : public Entity
{
private:
	int currentPos = 0;
	bool right = true;
public:

	Enemy(int x, int y, int w, int h, char* texturePath) : Entity(x, y, w, h, texturePath)
	{
		//std::cout << "Creating enemy" << std::endl;
		this->enemy = true;
	}

	
	void updatePos(int distance, float dt);
	void drawEnemy(int distance, float dt);
};
