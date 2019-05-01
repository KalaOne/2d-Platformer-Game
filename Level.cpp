#include "Level.h"
#include "Platform.h"

char Level::getTile(int x, int y) {
	if (x >= 0 && x <= levelWidth && y >= 0 && y <= levelHeight) {
		//if the position is in bounds of the level
		//return corresponding tile
		return levelTexture[y * levelWidth + x];
	}
	else
		return ' ';
}

void Level::drawLevel(float dT)
{
	for(Entity ent : entities)
	{
		ent.drawEntity(0, dT);
	}
}

void Level::generateLevel(int level) {
	levelTexture = "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
	levelTexture += "@-----------------=---------------=--------------@";
	levelTexture += "@-----------------=----========---=--------------@";
	levelTexture += "@-----------------=---------------=--------------@";
	levelTexture += "@------------------------------------------------@";
	levelTexture += "@------------------------------------------------@";
	levelTexture += "@------------------------------------------------@";
	levelTexture += "@--------------==--------------------------------@";
	levelTexture += "@-------------=--=-------------------------------@";
	levelTexture += "@--------------==--------------------------------@";
	levelTexture += "@------------------------------------------------@";
	levelTexture += "@------------------------------------------------@";
	levelTexture += "@------------------------------------------------@";
	levelTexture += "@------------------------------------------------@";
	levelTexture += "@------------------------------------------------@";
	levelTexture += "@------------------------=-----------------------@";
	levelTexture += "@------------------------=---------------o-------@";
	levelTexture += "@------------------------=-----ppp---------------@";
	levelTexture += "@------------------------=-----------------oo----@";
	levelTexture += "@------------------------=--------------------o--@";//y=20,x=51
//This beibe reverses the whole string, not just X or Y. Now it starts bottom right->top left
	std::reverse(levelTexture.begin(), levelTexture.end());
	for (int x = levelWidth; x >= 0 ; x--) {
		for (int y = 0; y < levelHeight; y++) {
			char tileID = getTile(x, y);
			switch (tileID)
			{
			case '=':
				entities.push_back(Entity(x * tileWidth, y * tileHeight, 50, 50));
				break;
			case '@':

				entities.push_back(Entity(x * tileWidth, y * tileHeight, 50, 50));
				break;
			
			case 'o':
				entities.push_back(Entity(x * tileWidth, y * tileHeight, 50, 50));
				break;

			case 'p':
				Platform plat = Platform(20, 20, x * tileWidth, y * tileHeight);
				entities.push_back(plat);
				platforms.push_back(plat);
				break;
			}
		}

	}
}
