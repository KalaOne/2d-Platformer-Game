#include "Player.h"

//Updating position of the entity




void Player::gravity(float deltaTime)
{
	if (!grounded) {//if player is in the air, reduce velocity
		velY -= 0.025 * deltaTime * 0.5;
	}
	if (newPosY <= 0) { //if player is oyeahn the ground, set grounded to true
		grounded = true;
		newPosY = 0; //dont allow player to fall below ground
		velY = 0;
	}
}