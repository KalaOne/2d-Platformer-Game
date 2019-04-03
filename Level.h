#pragma once
#include "GL\freeglut.h"
#include <math.h>
#include <iostream>
#include <chrono>
#include <string>

int levelWidth = 50, levelHeight = 20;
int tileWidth = 50;
int tileHeight = 50;
std::string levelTexture = "";

auto getTile(int x, int y);
void drawLevel();

