#include "Platform.h"

void Platform::updatePos(int travelDistance,bool x, float deltaTime)
{
	if (x)
	{
		moveX = true;
	}
	else
		moveY = true;
	int moveDistance = 0;
	if(moveX)
	{
		while(moveDistance <= travelDistance)
		{
			newPosX += platformVelX * deltaTime;
			moveDistance++;
		}
		if( moveDistance == travelDistance)
		{
			while(moveDistance >= 0)
			{
				newPosX += -platformVelX * deltaTime;
				moveDistance--;
			}
		}
	}
	else if(moveY)
	{
		
	}
}

void Platform::drawPlatform(float deltaTime)
{
	updatePos(5, 1, deltaTime);
	glColor3f(1, 1, 0);
	//add texture to the polygon here.
	glBegin(GL_POLYGON);
		glVertex2d(newPosX, newPosY);	 //bottom left
		glVertex2d(newPosX + width, newPosY); //bottom right
		glVertex2d(newPosX + width, newPosY + height); //top right
		glVertex2d(newPosX, newPosY + height);//top left
	glEnd();
}