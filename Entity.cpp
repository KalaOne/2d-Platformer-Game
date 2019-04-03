#include "Entity.h"


//Updating position of the entity
void Entity::updatePos(float deltaTime) {
	if (velX > 6)
		velX = 6;
	if (velX < -6)
		velX = -6;
	posX += velX * deltaTime;

	if (velY > 10)
		velY = 10;
	posY += velY * deltaTime;

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