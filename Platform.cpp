#include "Platform.h"

void Platform::updatePosX(int travelDistance, bool right, float deltaTime)
{
	//If deltaTime used for platform movement it buggs out..
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

void Platform::updatePosY(int travelDistance, bool up, float deltaTime)
{
	
}

void Platform::drawPlatform(int travelDistance, bool x, bool y, float deltaTime)
{
	updatePosX(1000, x, deltaTime);
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

void Platform::collisionAABB(Entity ent)
{
	if (ent.newPosX < (getX() + getWidth()) &&
		ent.newPosX + 50 > getX() &&
		ent.newPosY < (getY() + getHeight()) &&
		ent.newPosY + 50 > getY())
	{
		std::cout << "Colliding with the platform" << std::endl;
	}
}
