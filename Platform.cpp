#include "Platform.h"

void Platform::updatePosX(int travelDistance, bool right, float deltaTime)
{
	////Never stops moving to left... Somehow doesn't apply positive velocity....
	//int currentDistance = 0;
	//bool moveRight = true;
	//while (currentDistance <= travelDistance)
	//{
	//	newPosX += platformVelX * deltaTime;
	//	currentDistance++;
	//}

	//while(currentDistance >= 0)
	//{
	//	newPosX += -platformVelX * deltaTime;
	//	currentDistance--;
	//}

//Other option
	if (right)
	{
		moveX = true;
	}
	int moveDistance = 0;
	if (moveX)
	{
		while (moveDistance <= travelDistance)
		{
			newPosX += platformVelX * deltaTime * 0.25;
			moveDistance++;
		}
		if (moveDistance >= travelDistance)
		{
			while (moveDistance >= 0)
			{
				newPosX += -platformVelX * deltaTime * 0.25;
				moveDistance--;
			}
		}
	}
	else if (moveY)
	{

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