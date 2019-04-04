#include "Entity.h"
#include "Level.h"


//Updating position of the entity
void Entity::updatePos(float deltaTime) {
	collisionResponse();
	if (velXR > 6)
		velXR = 6;
	if (velXL < -6)
		velXL = -6;
	posX += velXR * deltaTime;
	posX += velXL * deltaTime;

	if (velYU > 10)
		velYU = 10;
	posY += velYU * deltaTime;

	//reducing velocity when moving right
	if (rPressed == false) {
		velXR += -0.025 * deltaTime;
		if (velXR <= 0)
			velXR = 0;
		if (posX <= 0)
			posX = 0;
	}
	//reducing velocity when moving left
	if (lPressed == false) {
		velXL += 0.025 * deltaTime;
		if (velXL >= 0)
			velXL = 0;
		if (posX <= 0)
			posX = 0;
	}
	lPressed = false;
	rPressed = false;

	
}



//Draws entity
void Entity::drawEntity(float deltaTime) {
	updatePos(deltaTime);
//add texture to the polygon here.
	glBegin(GL_POLYGON);
	glVertex2d(posX, posY);	 //bottom left
	glVertex2d(posX + 50, posY); //bottom right
	glVertex2d(posX + 50, posY + 50); //top right
	glVertex2d(posX, posY + 50);//top left
	glEnd();
}

//Collision detection
void Entity::collision()
{
	//+ 1 tile, not pixels(50)
	int left_tile	= posX / level->getTileWidth();
	int right_tile	= posX / level->getTileWidth() + 1;
	int top_tile	= posY / level->getTileHeight() + 1;
	int bottom_tile = posY / level->getTileHeight();

	if (left_tile < 0)
		left_tile = 0;
	if (right_tile > level->getTileWidth())
		right_tile = level->getTileWidth();
	if (top_tile > level->getTileHeight())
		top_tile = level->getTileHeight();
	if (bottom_tile < 0)
		bottom_tile = 0;
	collidingXLeft = false;
	collidingXRight = false;
	collidingYLeft = false;
	collidingYRight = false;
	char tileLeftX = level->getTile(left_tile, bottom_tile);
	char tileRightX = level->getTile(right_tile, bottom_tile);
	if(tileLeftX== '=')
	{
		//std::cout << "Left" << std::endl;
		collidingXLeft = true;
	}
	if(tileRightX == '=')
	{
		//std::cout << " Right" << std::endl;
		collidingXRight = true;
	}
	char tileLeftY = level->getTile(left_tile, top_tile);
	char tileRightY = level->getTile(right_tile, top_tile);
	if (tileLeftY== '=')
	{
		collidingYLeft = true;
	}
	if (tileRightY == '=')
	{
		collidingYRight = true;
	}
}

void Entity::collisionResponse()
{
	if (collidingXLeft) {
		velXL = 0;
		collidingXLeft = false;
	}
	else if (collidingXRight) {
		velXR = 0;
		collidingXRight = false;
	}
	if (collidingYLeft)
	{
		velYU = 0;
		collidingYLeft = false;
	}
	else if (collidingYRight)
	{
		velYD = 0;
		collidingYRight = false;
	}
}