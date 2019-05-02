#include "Platform.h"

void Platform::updatePosX(int travelDistance, bool right, float dt)
{
	//If dt used for platform movement, it buggs out..
	if(moveX)
	{
		if (currentDistance <= travelDistance) {
			newPosX += platformVelX * 15;
			currentDistance++;
		}
		else
			moveX = false;
	}
	else {
		if (currentDistance >= 0) {
			newPosX += -platformVelX * 15;
			currentDistance--;
		}
		else
			moveX = true;
	}
}

void Platform::updatePosY(int travelDistance, bool up, float dt)
{
	if (moveY)
	{
		if (currentDistance <= travelDistance) {
			newPosY += platformVelY * 15;
			currentDistance++;
		}
		else
			moveY = false;
	}
	else {
		if (currentDistance >= 0) {
			newPosY += -platformVelY * 15;
			currentDistance--;
		}
		else
			moveY = true;
	}
}

void Platform::drawPlatform(int travelDistance, bool x, bool y, float dt)
{
	if(x)
		updatePosX(travelDistance, x, dt);
	
	if(y)
		updatePosY(travelDistance, y, dt);
	
	glColor3f(1, 1, 0);
	//add texture to the polygon here.
	glBegin(GL_POLYGON);
		glVertex2d(newPosX, newPosY);	 //bottom left
		glVertex2d(newPosX + width, newPosY); //bottom right
		glVertex2d(newPosX + width, newPosY + height); //top right
		glVertex2d(newPosX, newPosY + height);//top left
	glEnd();
}


void Platform::drawPlatFromMap(float dt)
{
	if(moveRight)
	{
		newPosX += velX * dt;
	}
	else
	{
		newPosX -= velX * dt;
	}
	glColor3f(1, 1, 0);
	glPushMatrix();
	
	glBegin(GL_POLYGON);
		glVertex2d(newPosX, newPosY);	 //bottom left
		glVertex2d(newPosX + width, newPosY); //bottom right
		glVertex2d(newPosX + width, newPosY + height); //top right
		glVertex2d(newPosX, newPosY + height);//top left
	glEnd();
	glPopMatrix();
}
