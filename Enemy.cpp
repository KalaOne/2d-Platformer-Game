#include "Enemy.h"


void Enemy::updatePos(int distance, float dt)
{
	if (right) {
		newPosX += 0.5;
		currentPos++;
		if(currentPos == distance)
			right = false;
	}
	else
	{
		newPosX -= 0.5;
		currentPos--;
		if (currentPos == 0)
			right = true;
	}
}

void Enemy::drawEnemy(int distance, float dt)
{
	glPushMatrix();
		glColor3f(1, 0, 0);
		//std::cout << newPosX << std::endl;
		updatePos(distance, dt);
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
