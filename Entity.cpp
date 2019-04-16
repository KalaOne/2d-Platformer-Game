#include "Platform.h"


//Updating position of the entity
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
	collision();
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
	collidingXLeft = false;
	collidingXRight = false;
	collidingAboveLeft = false;
	collidingAboveRight = false;
	collidingBelowLeft = false;
	collidingBelowRight = false;
}

//Draws entity
void Entity::drawEntity(Level level,bool enemy, float deltaTime) 
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


void Entity::gravity(float deltaTime) 
{
	if (!grounded) {//if player is in the air, reduce velocity
		velY -= 0.025 * deltaTime * 0.5;
	}
	if (newPosY <= 0) { //if player is on the ground, set grounded to true
		grounded = true;
		newPosY = 0; //dont allow player to fall below ground
		velY = 0;
	}
}

//Collision detection
void Entity::collision()
{
	//+ 1 tile, not pixels(50)
	int left_tile	= newPosX / 50;
	int right_tile	= newPosX / 50 + 1;
	int top_tile	= newPosY / 50 + 1;
	int bottom_tile = newPosY / 50;
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
		glVertex2d(left_tile * level->getTileWidth(), bottom_tile * 50);//bot left
		glVertex2d(left_tile * level->getTileWidth() + level->getTileWidth(), bottom_tile * 50);//bot right
		glVertex2d(left_tile * level->getTileWidth() + level->getTileWidth(), bottom_tile * level->getTileHeight() + level->getTileHeight());//top right
		glVertex2d(left_tile * level->getTileWidth(), bottom_tile * level->getTileHeight() + level->getTileHeight());//top left
		glEnd();

		glBegin(GL_LINE_LOOP);
		//bottom right tile
		glVertex2d(left_tile * level->getTileWidth() + level->getTileWidth(), bottom_tile * 50);//bot left
		glVertex2d(left_tile * level->getTileWidth() + level->getTileWidth() + level->getTileWidth(), bottom_tile * 50);//bot right
		glVertex2d(left_tile * level->getTileWidth() + level->getTileWidth() + level->getTileWidth(), bottom_tile * level->getTileHeight() + level->getTileHeight());//top right
		glVertex2d(left_tile * level->getTileWidth() + level->getTileWidth(), bottom_tile * level->getTileHeight() + level->getTileHeight());//top left
		glEnd();

		glBegin(GL_LINE_LOOP);
		//top left tile
		glVertex2d(left_tile * level->getTileWidth(), top_tile * 50);//bot left
		glVertex2d(left_tile * level->getTileWidth() + level->getTileWidth(), top_tile * 50);//bot right
		glVertex2d(left_tile * level->getTileWidth() + level->getTileWidth(), top_tile * level->getTileHeight() + level->getTileHeight());//top right
		glVertex2d(left_tile * level->getTileWidth(), top_tile * level->getTileHeight() + level->getTileHeight());//top left
		glEnd();

		glBegin(GL_LINE_LOOP);
		//top right tile
		glVertex2d(left_tile * level->getTileWidth() + level->getTileWidth(), top_tile * 50);//bot left
		glVertex2d(left_tile * level->getTileWidth() + level->getTileWidth() + level->getTileWidth(), top_tile * 50);//bot right
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
	//collision above and below
	char tileAboveLeft = level->getTile(left_tile, top_tile);
	char tileAboveRight = level->getTile(right_tile, top_tile);
	char tileBelowLeft = level->getTile((left_tile), bottom_tile);
	char tileBelowRight = level->getTile(right_tile, bottom_tile);
	//Blocks collision
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

	//collectables collision
	if(tileLeftX =='o')
		level->changeVisibility();
	if(tileRightX == 'o')
		level->changeVisibility();
	if (tileAboveLeft == 'o')
		level->changeVisibility();
	if (tileAboveRight == 'o')
		level->changeVisibility();
	if (tileBelowLeft == 'o')
		level->changeVisibility();
	if (tileBelowRight == 'o')
		level->changeVisibility();

}

//
//void Entity::collisionResponse()
//{
//	//colliding X
//	if (collidingXLeft) {
//		newPosX = oldPosX;
//	}
//	if (collidingXRight) {
//		newPosX = oldPosX;
//	}
//	//colliding Y
//	if (collidingAboveLeft)
//	{
//		newPosY = oldPosY;	
//	}
//	if (collidingAboveRight)
//	{
//		newPosY = oldPosY;
//	}
//	if (collidingBelowLeft)
//	{
//		newPosY = oldPosY;
//		grounded = true;
//	}
//	if (collidingBelowRight)
//	{
//		newPosY = oldPosY;
//		grounded = true; 
//	}
//}


void Entity::AABB(Platform p)
{
	if (newPosX < (p.getX() + p.getWidth()) &&
		newPosX + 50 > p.getX() &&
		newPosY < (p.getY() + p.getHeight()) &&
		newPosY + 50 > p.getY())
	{
		/*system("cls");
		std::cout << "Colliding" << std::endl;*/
		if (newPosX < (p.getX() + p.getWidth()) &&
			newPosX + 50 > p.getX()) {
			velX = 0;
			newPosX = oldPosX;
			/*system("cls");
			std::cout << "Colliding SIDES" << std::endl;*/
		}
		//Split top and bottom?
		//Check if on top of the plat, if yes, then update player's velocity with platform's velocity.
		if (newPosY < (p.getY() + p.getHeight()) &&
			newPosY + 50 > p.getY()) {
			velY = 0;
			newPosY = oldPosY;
			/*system("cls");
			std::cout << "Colliding UP/DOWN" << std::endl;*/
		}
	}
}