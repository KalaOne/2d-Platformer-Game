#include "Level.h"

auto getTile(int x, int y) {
	if (x >= 0 && x <= levelWidth && y >= 0 && y <= levelHeight) {
		//if the position is in bounds of the level
		//return corresponding tile
		return levelTexture[y * levelWidth + x];
	}
	else
		return ' ';
}

void drawLevel() {
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
	levelTexture += "@-----===---=-----------------------=------------@";
	levelTexture += "@k---=-------=----------------------=------------@";
	levelTexture += "@-k--=---------=---------------------=------====-@";
	levelTexture += "@--k=----------==-------------------=------=--=--@";//y=20,x=51
//try inversing the loop to get the right area. GEE GEE
	for (int y = 0; y < levelHeight; y++) {
		for (int x = 0; x < levelWidth; x++) {
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