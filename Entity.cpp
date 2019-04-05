#include "Entity.h"
#include "Level.h"


//Updating position of the entity
void Entity::updatePos(float deltaTime) {

	if (velXR > 1)
		velXR = 1;
	if (velXL < -1)
		velXL = -1;
	int oldPosX = newPosX;
	int oldPosY = newPosY;
	newPosX += velXR * deltaTime;
	newPosX += velXL * deltaTime;

	if (velYU > 3)
		velYU = 3;
	newPosY += velYU * deltaTime;
	//std::cout << deltaTime << std::endl;
	collision();
	collisionResponse(oldPosX, oldPosY);
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
	collidingXLeft = false;
	collidingXRight = false;
	collidingAboveLeft = false;
	collidingAboveRight = false;
	collidingBelowLeft = false;
	collidingBelowRight = false;
}



//Draws entity
void Entity::drawEntity(float deltaTime) {
	updatePos(deltaTime);
//add texture to the polygon here.
	glBegin(GL_POLYGON);
	glVertex2d(newPosX, newPosY);	 //bottom left
	glVertex2d(newPosX + 50, newPosY); //bottom right
	glVertex2d(newPosX + 50, newPosY + 50); //top right
	glVertex2d(newPosX, newPosY + 50);//top left
	glEnd();
}

//Collision detection
void Entity::collision()
{
	//+ 1 tile, not pixels(50)
	int left_tile	= newPosX / level->getTileWidth();
	int right_tile	= newPosX / level->getTileWidth() + 1;
	int top_tile	= newPosY / level->getTileHeight() + 1;
	int bottom_tile = newPosY / level->getTileHeight();
	/*std::cout << "Right " << right_tile << std::endl;
	std::cout << "Top " << top_tile << std::endl;*/
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
	collidingAboveLeft = false;
	collidingAboveRight = false;
	collidingBelowLeft = false;
	collidingBelowRight = false;
	//collision left/right
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
	//collision above and below
	char tileAboveLeft = level->getTile(left_tile, top_tile);
	char tileAboveRight = level->getTile(right_tile, top_tile);
	char tileBelowLeft = level->getTile((left_tile), bottom_tile - 1);
	char tileBelowRight = level->getTile(right_tile, bottom_tile - 1);
	if (tileAboveLeft == '=')
	{
		collidingAboveLeft = true;
	}
	if (tileAboveRight == '=')
	{
		collidingAboveRight = true;
	}
	if(tileBelowLeft == '=')
	{
		collidingBelowLeft = true;
	}
	if (tileBelowRight == '=')
	{
		collidingBelowRight = true;
	}
}

void Entity::collisionResponse(int oldPosX, int oldPosY)
{

	if (collidingXLeft) {
		newPosX = posX;
		velXL = 0;

	}
	else if (collidingXRight) {
		newPosX = posX;
		velXR = 0;
		
	}
	if (collidingAboveLeft)
	{
		newPosY = posY;
		velYU = 0;
		
	}
	else if (collidingAboveRight)
	{
		newPosY = posY;
		velYD = 0;
	
	}
	if (collidingBelowLeft)
	{
		newPosY = posY;
		velYU = 0;
		
	}
	else if (collidingBelowRight)
	{
		newPosY = posY;
		velYD = 0;
		
	}
}