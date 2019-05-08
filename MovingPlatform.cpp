#include "MovingPlatform.h"

void MovingPlatform::updatePosX(int travelDistance, float dt)
{
	if (moveRight) {
		newPosX += platformVelX;
		pos++;
		if (pos >= travelDistance)
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

void MovingPlatform::updatePosY(int travelDistance, float dt)
{
	if (moveUp) {
		newPosY += platformVelY;
		pos++;
		if (pos >= travelDistance)
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

void MovingPlatform::drawPlatformUp(float dt)
{
	glPushMatrix();//player movement and drawing
		glColor4f(0, 1, 0, 0.5);
		updatePosY(travelDistance, dt);
		glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			glBindTexture(GL_TEXTURE_2D, entityTexture.activeSprite);
			glBegin(GL_POLYGON);
			glTexCoord2f(0, 0); glVertex2d(newPosX, newPosY);	 //bottom left
			glTexCoord2f(1, 0); glVertex2d(newPosX + width, newPosY); //bottom right
			glTexCoord2f(1, 1); glVertex2d(newPosX + width, newPosY + height); //top right
			glTexCoord2f(0, 1); glVertex2d(newPosX, newPosY + height);//top left
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void MovingPlatform::drawPlatformRight(float dt)
{
	glPushMatrix();//player movement and drawing
		glColor4f(0, 1, 0, 0.5);
		updatePosX(travelDistance,dt);
		glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			glBindTexture(GL_TEXTURE_2D, entityTexture.activeSprite);
			glBegin(GL_POLYGON);
			glTexCoord2f(0, 0); glVertex2d(newPosX, newPosY);	 //bottom left
			glTexCoord2f(1, 0); glVertex2d(newPosX + width, newPosY); //bottom right
			glTexCoord2f(1, 1); glVertex2d(newPosX + width, newPosY + height); //top right
			glTexCoord2f(0, 1); glVertex2d(newPosX, newPosY + height);//top left
			glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}