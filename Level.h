#pragma once
#include "GL\freeglut.h"
#include <math.h>
#include <iostream>
#include <chrono>
#include <string>

class Level {
private:
	int levelWidth = 50, levelHeight = 20;
	int tileWidth = 50;
	int tileHeight = 50;
	std::string levelTexture = "";
	bool colliding = false;
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
	char getTile(int x, int y);
	void drawLevel(int level);
	void collision();
};