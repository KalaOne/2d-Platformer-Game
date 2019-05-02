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
	glPushMatrix();
	if (!enemy) {//player movement and drawing
		glColor4f(0, 1, 0,0);
		updatePos(deltaTime);
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, activeSprite);
	//add texture to the polygon here.
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 0); glVertex2d(newPosX, newPosY);	 //bottom left
		glTexCoord2f(1, 0); glVertex2d(newPosX + width, newPosY); //bottom right
		glTexCoord2f(1, 1); glVertex2d(newPosX + width, newPosY + height); //top right
		glTexCoord2f(0, 1); glVertex2d(newPosX, newPosY + height);//top left
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
	else if(enemy)
	{
		//Enemy movement and drawing here.
		glColor4f(1, 0, 0, 0);
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, activeSprite);
	//add texture to the polygon here.
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 0); glVertex2d(newPosX, newPosY);	 //bottom left
		glTexCoord2f(1, 0); glVertex2d(newPosX + width, newPosY); //bottom right
		glTexCoord2f(1, 1); glVertex2d(newPosX + width, newPosY + height); //top right
		glTexCoord2f(0, 1); glVertex2d(newPosX, newPosY + height);//top left
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
	glPopMatrix();

}


void Entity::AABB(Entity& ent)
{
	collideX = false;
	collideY = false;
	collideAbove = false;
//Collision with every entity
	if (newPosX < (ent.getX() + ent.width) &&
		newPosX + width > ent.getX() &&
		newPosY < (ent.getY() + ent.height) &&
		newPosY + height > ent.getY())
	{
		//player on top of entity
		if (oldPosY >= (ent.getY() + ent.height) - 0.1) {
			//std::cout << "collide feet" << std::endl;
			collideY = true;
			onBlock = true;
		}
		//left of entity
		else if ((oldPosX + width) < ent.getX() + 0.02)
		{
			//std::cout << "collide right" << std::endl;
			collideX = true;
		}
		//right of entity
		else if (oldPosX > (ent.getX() + ent.width) - 0.02) {
			//std::cout << "collide left" << std::endl;
			collideX = true;
		}

		//player is below
		else if ((oldPosY + height) >= ent.getY() - 0.5) {
			//std::cout << "collide head" << std::endl;
			collideY = true;
			collideAbove = true;
			
		}

	}
	
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
	if(collideAbove)
	{
		velY = 0;
		newPosY = oldPosY - 0.5;
	}
}



void Entity::platformAABB(Platform& plat)
{
	collideX = false;
	collideY = false;
	if(newPosX < (plat.getX() + plat.getWidth()) &&
		newPosX + width > plat.getX() &&
		newPosY < (plat.getY() + plat.getHeight()) &&
		newPosY + height > plat.getY())
	{
		//player on top of platform
		if (oldPosY >= (plat.getY() + plat.height) - 0.1) {
			//std::cout << "collide feet" << std::endl;
			collideY = true;
			onBlock = true;
			newPosX += plat.velX;
			newPosY += plat.velY;
		}
		//left of entity
		else if ((oldPosX + width) < plat.getX() + 0.02)
		{
			//std::cout << "collide right" << std::endl;
			collideX = true;
		}
		//right of entity
		else if (oldPosX > (plat.getX() + plat.width) - 0.02) {
			//std::cout << "collide left" << std::endl;
			collideX = true;
		}

		//player is below
		else if ((oldPosY + height) >= plat.getY() - 0.1) {
			//std::cout << "collide head" << std::endl;
			collideY = true;
		}
	}
	AABBResponse();
}