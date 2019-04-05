#pragma once
#include "GL\freeglut.h"
#include <math.h>
#include <iostream>
#include <chrono>
#include <string>


class Platform
{
private:
	int width, height;
	int platformX, platformY;
public:

	Platform(int w, int h)
	{
		width = w;
		height = h;
	}

	int getWidth()
	{
		return width;
	}

	int getHeight()
	{
		return height;
	}

	int getX()
	{
		return platformX;
	}

	int getY()
	{
		return platformY;
	}

	void drawPlatform(int x, int y)
	{
		platformX = x;
		platformY = y;
		glColor3f(1, 1, 0);
	//add texture to the polygon here.
		glBegin(GL_POLYGON);
		glVertex2d(x, y);	 //bottom left
		glVertex2d(x + width, y); //bottom right
		glVertex2d(x + width, y + height); //top right
		glVertex2d(x, y + height);//top left
		glEnd();
	}
};