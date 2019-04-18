#include "Platform.h"
#include "Entity.h"
#include "Player.h"
#include <typeinfo>


void Entity::updatePos(float deltaTime)
{
	oldPosX = newPosX;
	oldPosY = newPosY;

	if (velX > 0.6) //incrementing by 0.2
		velX = 0.6;
	if (velX < -0.6) //incrementing by 0.2
		velX = -0.6;
	if (velY > 6) //incrementing by 2
		velY = 6;

	newPosX += velX * deltaTime;
	newPosY += velY * deltaTime * 0.5;
	//system("cls");
	//std::cout << newPosX << " X" << std::endl;
	//std::cout << newPosY << " Y" << std::endl;
	//collision();
	//collisionResponse(oldPosX, oldPosY);
	//reducing velocity when moving right
	if (rPressed == false) {
		velX += -0.025 * deltaTime;
		if (velX <= 0)
			velX = 0;
		if (posX <= 0)
			posX = 0;
	}
	//reducing velocity when moving left
	if (lPressed == false) {
		velX += 0.025 * deltaTime;
		if (velX >= 0)
			velX = 0;
		if (posX <= 0)
			posX = 0;
	}
	lPressed = false;
	rPressed = false;
}


//Draws entity
void Entity::drawEntity(bool enemy, float deltaTime) 
{
	if (!enemy) {//player movement and drawing
		glColor3f(0, 1, 0);
		updatePos(deltaTime);
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		//glBindTexture(GL_TEXTURE_2D, texName);
	//add texture to the polygon here.
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 0); glVertex2d(newPosX, newPosY);	 //bottom left
		glTexCoord2f(0, 1); glVertex2d(newPosX + 50, newPosY); //bottom right
		glTexCoord2f(1, 1); glVertex2d(newPosX + 50, newPosY + 50); //top right
		glTexCoord2f(1, 0); glVertex2d(newPosX, newPosY + 50);//top left
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
	else
	{
		//Enemy movement and drawing here.
		glColor3f(1, 0, 0);
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		//glBindTexture(GL_TEXTURE_2D, texName);
	//add texture to the polygon here.
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 0); glVertex2d(newPosX, newPosY);	 //bottom left
		glTexCoord2f(0, 1); glVertex2d(newPosX + 50, newPosY); //bottom right
		glTexCoord2f(1, 1); glVertex2d(newPosX + 50, newPosY + 50); //top right
		glTexCoord2f(1, 0); glVertex2d(newPosX, newPosY + 50);//top left
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}

}


void Entity::AABB(Entity& ent)
{
	//bool x = newPosX + width >= ent.getX() && ent.getX() + ent.width >= newPosX;
	//bool y = newPosY + height >= ent.getY() && ent.getY() + ent.height >= newPosY;

	collideX = false;
	collideY = false;
	////if the entity is platform, use 
	//if (typeid(ent) == typeid(Platform)) {
	//	if (newPosX < (ent.getX() + ent.width) &&
	//		newPosX + 50 > ent.getX() &&
	//		newPosY < (ent.getY() + ent.height) &&
	//		newPosY + 50 > ent.getY())
	//	{
	//		if (newPosX < (ent.getX() + ent.width) &&
	//			newPosX + ent.width > ent.getX()) {
	//			collideX = true;
	//			
	//		}
	//		if (newPosY < (ent.getY() + ent.height) &&
	//			newPosY + ent.height > ent.getY()) {
	//			collideY = true;
	//		}
	//	}
	//}
	//else {
		if (newPosX < (ent.getX() + ent.width) &&
			newPosX + width > ent.getX() &&
			newPosY < (ent.getY() + ent.height) &&
			newPosY + height > ent.getY())
		{
		
			if (newPosX < (ent.getX() + ent.width) &&
				newPosX + width > ent.getX()) {
				collideX = true;
			
			}
			if (newPosY < (ent.getY() + ent.height) &&
				newPosY + height > ent.getY()) {
				collideY = true;
			}
		}
	//}

	//if(x && y)
		AABBResponse();
}

void Entity::AABBResponse()
{
	if(collideX)
	{
		velX = 0;
		newPosX = oldPosX;
	}
	if(collideY)
	{
		velY = 0;
		newPosY = oldPosY;
	}
}