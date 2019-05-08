#include "Level.h"
#include "Platform.h"

char Level::getTile(int x, int y) {
	if (x >= 0 && x <= levelWidth && y >= 0 && y <= levelHeight) {
		//if the position is in bounds of the level
		//return corresponding tile
		return level1[y * levelWidth + x];
	}
	else
		return ' ';
}

void Level::setTile(int x, int y)
{
	for (int i = 0; i < collectables.size(); i++) {
		if(collectables[i]->getX() == x && collectables[i]->getY() == y)
		{
			collectables.erase(collectables.begin()+i);
		}
	}
	
}
void Level::drawLevel(float dt)
{
	for(Entity* ent : entities)
	{
		ent->drawEntity(dt);
	}
	for(Entity* s: spikes)
	{
		s->drawEntity(dt);
	}
	for(Entity* o : collectables)
	{
		o->drawEntity(dt);
	}
	for (Entity* l : leaves)
	{
		l->drawEntity(dt);
	}
	for(Platform* p : platforms)
	{
		p->drawEntity(dt);
	}
}

void Level::generateLevel(int level) {
	if (level == 1) {
		level1 = "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
		level1 += "@-----------------=---------------=--------------@";
		level1 += "@-----------------=----========---=--------------@";//900
		level1 += "@-----------------=---------------=--------------@";
		level1 += "@------------------------------------------------@";//800
		level1 += "@----=---=----=--=-----------------rrrrrrrr------@";
		level1 += "@----=--=-=----=-=-------------------------------@";
		level1 += "@----=-=-=-=--=-==-------------------------------@";
		level1 += "@-=====-----==---=-----------o-------------------@";//600
		level1 += "@------------------------rrrrr-------------------@";
		level1 += "@-----------o------------------p------------o----@";
		level1 += "@-----------------------ssss------=---=----------@";
		level1 += "@---------=====--p------====--------o----p-===---@";//400
		level1 += "@------s-----------==---------------------------=@";
		level1 += "@--====---rrrrrr------=-------p-=-rrrrrrrrrrr-==-@";
		level1 += "@------------------p-p----=--------o-------------@";
		level1 += "@--ss----------------------==--------------------@";//200
		level1 += "@====---p------sssss----------===-----=----------@";
		level1 += "@-----o--------=====-------------=ssss---p-------@";
		level1 += "@--m-----ssss-------ssssssssss---=====-----------@";//y=20,x=51
		//This beibe reverses the whole string, not just X or Y. Now it starts bottom right->top left
		std::reverse(level1.begin(), level1.end());
		generateTiles();
	}
	else if(level == 3)
	{
		level1 = "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
		level1 += "@-----------------=---------------=--------------@";
		level1 += "@-----------------=----========---=--------------@";
		level1 += "@-----------------=---------------=--------------@";
		level1 += "@------------------------------------------------@";
		level1 += "@------------------------------------------------@";
		level1 += "@------------------------------------------------@";
		level1 += "@--------------==--------------------------------@";
		level1 += "@-------------=--=-------------------------------@";
		level1 += "@--------------==------------o-------------------@";
		level1 += "@-------------------------------------------o----@";
		level1 += "@---------------------------====-----------------@";
		level1 += "@-----------------------------------o----p-===---@";
		level1 += "@------------------------o------------p---------=@";
		level1 += "@------------------------------------------------@";
		level1 += "@------------------------------------------------@";
		level1 += "@--------------------------==--------------====--@";
		level1 += "@------------------------------------------=-----@";
		level1 += "@-----o------------------------p-------p--==-----@";
		level1 += "@------------------------------------m-----------@";//y=20,x=51
		std::reverse(level1.begin(), level1.end());
		generateTiles();
	}
	else if(level == 5)
	{
		level1 = "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
		level1 += "@-----------------=---------------=--------------@";
		level1 += "@-----------------=----========---=--------------@";
		level1 += "@-----------------=---------------=--------------@";
		level1 += "@------------------------------------------------@";
		level1 += "@------------------------------------------------@";
		level1 += "@------------------------------------------------@";
		level1 += "@--------------==--------------------------------@";
		level1 += "@-------------=--=-------------------------------@";
		level1 += "@--------------==------------o-------------------@";
		level1 += "@-------------------------------------------o----@";
		level1 += "@---------------------------====-----------------@";
		level1 += "@-----------------------------------o----p-===---@";
		level1 += "@------------------------o------------p---------=@";
		level1 += "@------------------------------------------------@";
		level1 += "@-----------------------------------------====---@";
		level1 += "@--------------------------==----------=--=------@";
		level1 += "@--------------------------------------=--==-----@";
		level1 += "@-----o--------------------------------=--=------@";
		level1 += "@--------------------------sss---------=--====---@";//y=20,x=51

		std::reverse(level1.begin(), level1.end());
		generateTiles();
	}

}


void Level::generateTiles()
{
	for (int x = levelWidth; x >= 0; x--) {
		for (int y = 0; y < levelHeight; y++) {
			char tileID = getTile(x, y);
			switch (tileID)
			{
			case '=': {
				Entity* column = new Entity(x * tileWidth, y * tileHeight, 50, 50, "Assets/platform_gfx/tiles/block1.png");
				entities.push_back(column);
			}
					  break;
			case '@': {
				Entity* wall = new Entity(x * tileWidth, y * tileHeight, 50, 50, "Assets/platform_gfx/tiles/block4.png");
				entities.push_back(wall);
			}
					  break;

			case 'o': {
				Entity* food = new Entity(true,x * tileWidth, y * tileHeight, 25, 25, "Assets/platform_gfx/tiles/block3.png");
				collectables.push_back(food);
			}
					  break;

			case 'p': {
				Platform* plat = new Platform(x * tileWidth, y * tileHeight, 100, 30, "Assets/platform_gfx/tiles/block2.png");
				platforms.push_back(plat);
			}
					  break;
			case 's': {
				Entity* spike = new Entity(x * tileWidth, y * tileHeight, 50, 20, "Assets/platform_gfx/tiles/spikes1.png");
				spikes.push_back(spike);
			}
					  break;
			case 'm': {
				Entity* leaf = new Entity(x * tileWidth, y * tileHeight, 50, 50, "Assets/platform_gfx/tiles/door.png");
				leaves.push_back(leaf);
			}
					  break;
			}
		}

	}
}