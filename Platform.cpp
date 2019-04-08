#include "Platform.h"

void Platform::updatePosX(int travelDistance, bool right, float deltaTime)
{
	//Never stops moving to left... Somehow doesn't apply positive velocity....
	int currentDistance = 0;
	bool moveRight = true;
	while (currentDistance <= travelDistance)
	{
		newPosX += platformVelX * deltaTime;
		currentDistance++;
	}

	while(currentDistance >= 0)
	{
		newPosX += -platformVelX * deltaTime;
		currentDistance--;
	}

}

void Platform::updatePosY(int travelDistance, bool up, float deltaTime)
{
	
}

void Platform::drawPlatform(bool x, bool y, float deltaTime)
{
	updatePosX(50, x, deltaTime);
	updatePosY(5, y, deltaTime);
	glColor3f(1, 1, 0);
	//add texture to the polygon here.
	glBegin(GL_POLYGON);
		glVertex2d(newPosX, newPosY);	 //bottom left
		glVertex2d(newPosX + width, newPosY); //bottom right
		glVertex2d(newPosX + width, newPosY + height); //top right
		glVertex2d(newPosX, newPosY + height);//top left
	glEnd();
}