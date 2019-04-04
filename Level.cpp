#include "Level.h"

inline char Level::getTile(int x, int y) {
	if (x >= 0 && x <= levelWidth && y >= 0 && y <= levelHeight) {
		//if the position is in bounds of the level
		//return corresponding tile
		return levelTexture[y * levelWidth + x];
	}
	else
		return ' ';
}

void Level::drawLevel(int level) {
	levelTexture += "@-----------------=------=-===--=====------------@";
	levelTexture += "@---=-------------=---------------=----------==--@";
	levelTexture += "@---=-------------=----========---=-----------=--@";
	levelTexture += "@---====----------=---------------=-----------=--@";
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
	levelTexture += "@---------=--------------------------------------@";
	levelTexture += "@--------=-=-------------------------------------@";
	levelTexture += "@-------=---=------------=-----------------------@";
	levelTexture += "@-----=------=-----------=---------------=-------@";
	levelTexture += "@----=---------=---------=-===----=------=--==---@";
	levelTexture += "@---=-----------=--------=---=--=---=----=----=--@";//y=20,x=51
//This beibe reverses the whole string, not just X or Y. Now it starts bottom right->top left
	std::reverse(levelTexture.begin(), levelTexture.end());
	for (int x = levelWidth; x >= 0 ; x--) {
		for (int y = 0; y < levelHeight; y++) {
			char tileID = getTile(x, y);
			switch (tileID)
			{
			case '=':
				glColor3f(0.5, 0.2, 0.3);
				glBegin(GL_POLYGON);
				glVertex2d(x * tileWidth, y * tileHeight);
				glVertex2d(x * tileWidth + tileWidth, y * tileHeight);
				glVertex2d(x * tileWidth + tileWidth, y * tileHeight + tileHeight);
				glVertex2d(x * tileWidth, y * tileHeight + tileHeight);
				glEnd();
				break;

			case '@':
				glColor3f(0, 0.35, 0.86);
				glBegin(GL_POLYGON);
				glVertex2d(x * tileWidth, y * tileHeight);
				glVertex2d(x * tileWidth + tileWidth, y * tileHeight);
				glVertex2d(x * tileWidth + tileWidth, y * tileHeight + tileHeight);
				glVertex2d(x * tileWidth, y * tileHeight + tileHeight);
				glEnd();
				break;
			}
		}

	}
}
