#include "Platform.h"



void Platform::updatePosX(int travelDistance, float dt)
{
	if (moveRight) {
		newPosX += platformVelX;
		pos++;
		if (pos == travelDistance)
			moveRight = false;
	}
	else
	{
		newPosX -= platformVelX;
		pos--;
		if (pos == 0)
			moveRight = true;
	}
}

void Platform::updatePosY(int travelDistance, float dt)
{
	if(moveUp) {
		newPosY += platformVelX;
		pos++;
		if (pos == travelDistance)
			moveUp = false;
	}
	else
	{
	newPosY -= platformVelY;
	pos--;
	if (pos == 0)
		moveUp = true;
	}
}
//
//void Platform::drawPlatform(int travelDistance, bool x, bool y, float dt)
//{
//	if(x)
//		updatePosX(travelDistance, x, dt);
//	
//	if(y)
//		updatePosY(travelDistance, y, dt);
//	
//	glColor3f(1, 1, 0);
//	//add texture to the polygon here.
//	glBegin(GL_POLYGON);
//		glVertex2d(newPosX, newPosY);	 //bottom left
//		glVertex2d(newPosX + width, newPosY); //bottom right
//		glVertex2d(newPosX + width, newPosY + height); //top right
//		glVertex2d(newPosX, newPosY + height);//top left
//	glEnd();
//}

//
//void Platform::drawPlatFromMap(float dt)
//{
//	if(moveRight)
//	{
//		newPosX += 1.5 * dt;
//	}
//	else
//	{
//		newPosX -= 1.5 * dt;
//	}
//	glColor3f(1, 1, 0);
//	glPushMatrix();
//	glEnable(GL_TEXTURE_2D);
//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
//	glBindTexture(GL_TEXTURE_2D, entityTexture.activeSprite);
//	glBegin(GL_POLYGON);
//		glVertex2d(newPosX, newPosY);	 //bottom left
//		glVertex2d(newPosX + width, newPosY); //bottom right
//		glVertex2d(newPosX + width, newPosY + height); //top right
//		glVertex2d(newPosX, newPosY + height);//top left
//	glEnd();
//	glDisable(GL_TEXTURE_2D);
//	glPopMatrix();
//}
