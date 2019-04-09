#include "Entity.h"



//Updating position of the entity
void Entity::updatePos(float deltaTime) 
{
	int oldPosX = newPosX;
	int oldPosY = newPosY;

	if (velXR > 0.6) //incrementing by 0.2
		velXR = 0.6;
	if (velXL < -0.6) //incrementing by 0.2
		velXL = -0.6;
	if (velYU > 6) //incrementing by 2
		velYU = 6;

	newPosX += velXR * deltaTime;
	newPosX += velXL * deltaTime;
	newPosY += velYU * deltaTime * 0.5;
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
void Entity::drawEntity(Level level, float deltaTime) 
{
	glPushMatrix();
	glColor3f(0, 1, 0);
	updatePos(deltaTime);
//add texture to the polygon here.
	glBegin(GL_POLYGON);
		glVertex2d(newPosX, newPosY);	 //bottom left
		glVertex2d(newPosX + 50, newPosY); //bottom right
		glVertex2d(newPosX + 50, newPosY + 50); //top right
		glVertex2d(newPosX, newPosY + 50);//top left
	glEnd();
	glPopMatrix();

}


void Entity::gravity(float deltaTime) 
{
	if (!grounded) {//if player is in the air, reduce velocity
		velYU -= 0.025 * deltaTime * 0.5;
	}
	if (newPosY <= 0) { //if player is on the ground, set grounded to true
		grounded = true;
		newPosY = 0; //dont allow player to fall below ground
		velYU = 0;
	}
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
	if (debug) {
		//bottom left tile
		glColor3f(1, 1, 1);
		glBegin(GL_LINE_LOOP);
		glVertex2d(left_tile * level->getTileWidth(), bottom_tile);//bot left
		glVertex2d(left_tile * level->getTileWidth() + level->getTileWidth(), bottom_tile);//bot right
		glVertex2d(left_tile * level->getTileWidth() + level->getTileWidth(), bottom_tile * level->getTileHeight() + level->getTileHeight());//top right
		glVertex2d(left_tile * level->getTileWidth(), bottom_tile * level->getTileHeight() + level->getTileHeight());//top left
		glEnd();

		glBegin(GL_LINE_LOOP);
		//bottom right tile
		glVertex2d(left_tile * level->getTileWidth() + level->getTileWidth(), bottom_tile);//bot left
		glVertex2d(left_tile * level->getTileWidth() + level->getTileWidth() + level->getTileWidth(), bottom_tile);//bot right
		glVertex2d(left_tile * level->getTileWidth() + level->getTileWidth() + level->getTileWidth(), bottom_tile * level->getTileHeight() + level->getTileHeight());//top right
		glVertex2d(left_tile * level->getTileWidth() + level->getTileWidth(), bottom_tile * level->getTileHeight() + level->getTileHeight());//top left
		glEnd();

		glBegin(GL_LINE_LOOP);
		//top left tile
		glVertex2d(left_tile * level->getTileWidth(), top_tile);//bot left
		glVertex2d(left_tile * level->getTileWidth() + level->getTileWidth(), top_tile);//bot right
		glVertex2d(left_tile * level->getTileWidth() + level->getTileWidth(), top_tile * level->getTileHeight() + level->getTileHeight());//top right
		glVertex2d(left_tile * level->getTileWidth(), top_tile * level->getTileHeight() + level->getTileHeight());//top left
		glEnd();

		glBegin(GL_LINE_LOOP);
		//top right tile
		glVertex2d(left_tile * level->getTileWidth() + level->getTileWidth(), top_tile);//bot left
		glVertex2d(left_tile * level->getTileWidth() + level->getTileWidth() + level->getTileWidth(), top_tile);//bot right
		glVertex2d(left_tile * level->getTileWidth() + level->getTileWidth() + level->getTileWidth(), top_tile * level->getTileHeight() + level->getTileHeight());//top right
		glVertex2d(left_tile * level->getTileWidth() + level->getTileWidth(), top_tile * level->getTileHeight() + level->getTileHeight());//top left
		glEnd();
	}
	collidingXLeft = false;
	collidingXRight = false;
	collidingAboveLeft = false;
	collidingAboveRight = false;
	collidingBelowLeft = false;
	collidingBelowRight = false;
	//collision left/right
	char tileLeftX = level->getTile(left_tile, bottom_tile);
	char tileRightX = level->getTile(right_tile, bottom_tile);
	if(tileLeftX== '=' || tileLeftX == '@')
	{
		//std::cout << "Left" << std::endl;
		collidingXLeft = true;
	}
	if(tileRightX == '=' || tileRightX == '@')
	{
		//std::cout << " Right" << std::endl;
		collidingXRight = true;
	}
	//collision above and below
	char tileAboveLeft = level->getTile(left_tile, top_tile);
	char tileAboveRight = level->getTile(right_tile, top_tile);
	char tileBelowLeft = level->getTile((left_tile), bottom_tile);
	char tileBelowRight = level->getTile(right_tile, bottom_tile);
	if (tileAboveLeft == '=' || tileAboveLeft == '@')
	{
		collidingAboveLeft = true;
	}
	if (tileAboveRight == '=' || tileAboveRight == '@')
	{
		collidingAboveRight = true;
	}
	if(tileBelowLeft == '=' || tileBelowLeft == '@')
	{
		collidingBelowLeft = true;
	}
	if (tileBelowRight == '=' || tileBelowRight == '@')
	{
		collidingBelowRight = true;
	}
}

void Entity::collisionResponse(int oldPosX, int oldPosY)
{
	//colliding X
	if (collidingXLeft) {
		velXL = 0;
		newPosX = oldPosX;
	}
	if (collidingXRight) {
		velXR = 0;
		newPosX = oldPosX;
	}
	//colliding Y
	if (collidingAboveLeft)
	{
		newPosY = oldPosY;
		velYU = 0;
		
	}
	if (collidingAboveRight)
	{
		newPosY = oldPosY;
		velYD = 0;
	
	}
	if (collidingBelowLeft)
	{
		newPosY = oldPosY;
		grounded = true;
	}
	if (collidingBelowRight)
	{
		newPosY = oldPosY;
		grounded = true; 
	}
}
