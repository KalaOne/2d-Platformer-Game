#include "Platform.h"
#include "Entity.h"
#include <typeinfo>
#include "Player.h"
#include "MovingPlatform.h"

void Entity::updatePos(float deltaTime)
{
	oldPosX = newPosX;
	oldPosY = newPosY;

	if (velX > 1) //incrementing by 0.5
		velX = 1;
	if (velX < -1) //incrementing by 0.5
		velX = -1;
	if (velY > 6) //incrementing by 2
		velY = 6;

	newPosX += velX * deltaTime;
	newPosY += velY * deltaTime * 0.5;
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
void Entity::drawEntity(float deltaTime) 
{
	glPushMatrix();//player movement and drawing
		glColor4f(0, 1, 0,0.5);
		updatePos(deltaTime);
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

void Entity::texturise(GLuint texture)
{
	this->entityTexture.activeSprite = texture;
}

bool Entity::AABB(Entity& ent)
{

	collideX = false;
	collideY = false;
	collideAbove = false;
	collideEnemy = false;//Collision with every entity
	if(ent.isCollectable)
	{
		if (newPosX < (ent.getX() + ent.width) &&
			newPosX + width > ent.getX() &&
			newPosY < (ent.getY() + ent.height) &&
			newPosY + height > ent.getY())
		{
			return true;
		}
	}
	else {
		if (newPosX < (ent.getX() + ent.width) &&
			newPosX + width > ent.getX() &&
			newPosY < (ent.getY() + ent.height) &&
			newPosY + height > ent.getY())
		{

			if (ent.checkIfEnemy()) // if colliding with enemy
			{
				//std::cout << "Bam!" << std::endl;
				collideEnemy = true;
			}
			else {
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
		}
	}
	AABBResponse();
	return false;
}

void Entity::platformAABB(Platform& plat)
{
	collideX = false;
	collideY = false;
	collideAbove = false;
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
			collideAbove = true;
		}
	}
	AABBResponse();
}

void Entity::movingPlatsAABB(MovingPlatform& mp)
{
	collideX = false;
	collideY = false;
	collideAbove = false;
	moveUpPlatform = false;
	moveRightPlatform = false;
	moveLeftPlatform = false;
	onPlatform = false;
	if (newPosX < (mp.getCurrentX() + mp.getWidth()) &&
		newPosX + width > mp.getCurrentX() &&
		newPosY < (mp.getCurrentY() + mp.getHeight()) &&
		newPosY + height > mp.getCurrentY())
	{
		//player on top of platform
		if (oldPosY >= (mp.getCurrentY() + mp.height) - 0.1) {
			collideY = true;
			if (mp.checkMoveUp()) {
				moveUpPlatform = true;
				onBlock = true;
				newPosY += mp.velY;
			}
			if (mp.checkMoveRight()) {
				//rPressed = true;
				onBlock = true;
				velX = mp.getCurrentVelX();
			}
			else {
				//lPressed = true;
				onBlock = true;
				velX -= mp.getCurrentVelX();
			}
		}
		//left of platform
		else if ((oldPosX + width) < mp.getCurrentX() + 0.02)
		{
			//std::cout << "collide right" << std::endl;
			collideX = true;
		}
		//right of platform
		else if (oldPosX > (mp.getCurrentX() + mp.width) - 0.02) {
			//std::cout << "collide left" << std::endl;
			collideX = true;
		}

		//player is below
		else if ((oldPosY + height) >= mp.getCurrentY() - 0.1) {
			//std::cout << "collide head" << std::endl;
			collideY = true;
			collideAbove = true;
		}
	}
	AABBResponse();
}

void Entity::spikeCollision(Entity& s)
{
	if (newPosX < (s.getX() + s.width) &&
		newPosX + width > s.getX() &&
		newPosY < (s.getY() + s.height))
	{
		newPosX = 50;
		newPosY = 0;
	}
}

void Entity::AABBResponse()
{
	if (collideX)
	{
		velX = 0;
		newPosX = oldPosX;
	}
	if (collideY)
	{
		velY = 0;
		newPosY = oldPosY;
	}
	if (collideAbove)
	{
		velY = 0;
		newPosY = oldPosY - 0.5;
	}
	if(collideEnemy)
	{
		//std::cout << "Enemy !" << std::endl;
		velX = velX * 0.5;
		velY = velY * 0.5;
	}
}