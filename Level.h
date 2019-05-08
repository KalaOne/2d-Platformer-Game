#pragma once
#include "GL\freeglut.h"
#include <math.h>
#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include "Entity.h"
#include "Platform.h"

class Level {
private:
	int levelWidth = 50, levelHeight = 20;
	int const tileWidth = 50;
	int const tileHeight = 50;
	std::string level1 = "";
	std::string level2 = "";
	std::string level3 = "";
	bool colliding = false;
	bool visible = true;
	std::vector<Entity*> entities;
	std::vector<Platform*> platforms;
	std::vector<Platform*> platUp;
	std::vector<Platform*> platRight;
	std::vector<Platform*> movingPlatforms;
	std::vector<Entity*> leaves;
	std::vector<Entity*> collectables;
	std::vector<Entity*> spikes;


public:
	int getLevelWidth()
	{
		return levelWidth;
	}
	int getLevelHeight()
	{
		return levelHeight;
	}
	int getTileWidth()
	{
		return tileWidth;
	}
	int getTileHeight()
	{
		return tileHeight;
	}
	void changeVisibility()
	{
		if (visible)
			visible = false;
	}


	std::vector<Platform*> getPlatformVector()
	{
		return platforms;
	}

	std::vector<Entity*> getEntityVector()
	{
		return entities;
	}
	std::vector<Entity*> getSpikesVector()
	{
		return spikes;
	}
	std::vector<Entity*> getCollectablesVector()
	{
		return collectables;
	}
	std::vector<Entity*> getLeavesVector()
	{
		return leaves;
	}

	char getTile(int x, int y);
	void generateLevel(int level);
	void drawLevel(float dt);
	void generateTiles();
};
