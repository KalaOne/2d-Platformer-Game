//includes areas for keyboard control, mouse control, resizing the window
//and draws a spinning rectangle

//#include "Platform.h"
#pragma once

#include "Image_Loading/nvImage.h"
#include <vector>
#include "Level.h"
#include "Entity.h"
#include "Platform.h"
#include "Player.h"
#include "Enemy.h"
#include "MovingPlatform.h"
#include "windows.h"


using namespace std;

int screenWidth=720, screenHeight=480;
bool* keyStates = new bool[256];
float grav = 0;
float camX = 0, camY = 0;
float oldTime = 0.0;
float dt;
int levels = 4;
bool enemyCollide = false;

vector<Entity*> tiles;
vector<Entity*> collectables;
vector<Entity*> spikes;
vector<Entity*> leaves;
vector<Platform*> platforms;
vector<MovingPlatform*> movingPlatsRight;
vector<MovingPlatform*> movingPlatsUp;
vector<Enemy*> enemies;

//OPENGL FUNCTION PROTOTYPES
void display();				//called in winmain to draw everything to the screen
void reshape(int width, int height);				//called when the window is resized
void init();				//called in winmain when the program starts.
void keyfunction(unsigned char key, int x, int y);
void update();				//called in winmain to update variables#
void texturise();
GLuint loadPNG(char* name);


Level level;
Player player(50,0, 49, 49, "Assets/platform_gfx/hero/hero.png"); // keep in mind each field/tile size is 50. x=1;
Enemy enemy1(200, 0, 25, 25, "Assets/platform_gfx/baddies/output.png"); // closest to left
Enemy enemy2(1200, 600, 25, 25, "Assets/platform_gfx/baddies/output.png");

MovingPlatform pR1(500,50,150,20,1500,"Assets/platform_gfx/tiles/block2.png");
//MovingPlatform pR2(300,100,150,20, 150,"Assets/platform_gfx/tiles/block2.png");
//MovingPlatform pR3(1200, 50, 150,20,100, "Assets/platform_gfx/tiles/block2.png");
MovingPlatform pU1(300,10,150,20,600, "Assets/platform_gfx/tiles/block2.png");
//MovingPlatform pU2(300,50,150,20,200, "Assets/platform_gfx/tiles/block2.png");



GLuint loadPNG(char* name)
{
	// Texture loading object
	nv::Image img;

	GLuint myTextureID;

	// Return true on success
	if (img.loadImageFromFile(name))
	{
		glGenTextures(1, &myTextureID);
		glBindTexture(GL_TEXTURE_2D, myTextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, img.getInternalFormat(), img.getWidth(), img.getHeight(), 0, img.getFormat(), img.getType(), img.getLevel(0));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}

	else
		std::cout << "Failed to load texture. End of the world" << std::endl;;

	return myTextureID;
}

void camera() {

	//call camera on the centre of playerPos
	camX = player.newPosX - (screenWidth / 2);
	camY = player.newPosY - (screenHeight / 2);
	//clamping camera
	if (camX <= 0) camX = 0;
	if (camY <= 0) camY = 0;
	if (camX >= level.getLevelWidth() * level.getTileWidth() - screenWidth) {
		camX = level.getLevelWidth() * level.getTileWidth() - screenWidth;
	}
	if (camY >= level.getLevelHeight() * level.getTileHeight() - screenHeight) {
		camY = level.getLevelHeight() * level.getTileHeight() - screenHeight;
	}

	glTranslatef(-camX, -camY, 0);
}

//keys are released
void keyUp(unsigned char key, int x, int y)
{
	keyStates[key] = false;
}
//keys are being pressed
void keyDown(unsigned char key, int x, int y)
{
	keyStates[key] = true;
}
//handle key functuonality
void keyOperations() {
	if (keyStates[27]) {
		exit(0);
	}
	if(keyStates['r'])
	{
		player.newPosX = 50;
		player.newPosY = 0;
	}
	if (keyStates['w']) {
		if (player.isGrounded() || player.isOnBlock()) {
			//player.posY += 0.1;
			player.velY += 2;
			player.ungroundPlayer();
			player.unblockPlayer();
		}
	}
	if (keyStates['s']) {
		player.velY -= 0.5;
	}

	if (keyStates['a']) {
		player.velX -= 0.5;
		player.ungroundPlayer();
		player.unblockPlayer();
	}

	if (keyStates['d']) {
		player.velX += 0.5;
		player.ungroundPlayer();
		player.unblockPlayer();
	}
}

void display()																	
{	
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	//delta time
	float newTime = glutGet(GLUT_ELAPSED_TIME);
	dt = (newTime - oldTime) * 0.75;
	oldTime = newTime;
	camera();
	
	for (Enemy* e : enemies)
	{
		player.AABB(*e);
	}
	level.drawLevel(dt);
	player.drawEntity(dt);
	enemy1.drawEnemy(550, dt);

	//drawing and updating moving platforms
	for(MovingPlatform* u_p: movingPlatsUp)
	{
		u_p->drawPlatformUp(dt);
	}
	for (MovingPlatform* r_p : movingPlatsRight)
	{
		r_p->drawPlatformRight(dt);
	}


	//player collides with everything else.
	for(Entity* ent : tiles)
	{
		player.AABB(*ent);
	}
	for(Platform* p : platforms)
	{
		player.platformAABB(*p);
	}
	for (MovingPlatform* m_plat : movingPlatsRight)
	{
		player.movingPlatsAABB(*m_plat);
	}
	for (MovingPlatform* m_plat : movingPlatsUp)
	{
		player.movingPlatsAABB(*m_plat);
	}
	for(Entity* s : spikes)
	{
		player.spikeCollision(*s);
	}
	

	glFlush();
	glutSwapBuffers();
	
	player.gravity(dt);
}

void reshape(int width, int height)		// Resize the OpenGL window
{
	screenWidth=width; screenHeight = height;           // to ensure the mouse coordinates match 
	// we will use these values to set the coordinate system
	
	glViewport(0,0,width,height);						
	
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									

	gluOrtho2D(0, screenWidth, 0, screenHeight);           // set the coordinate system for the window
	
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									
}
void init()
{
	glClearColor(0.0,0.0,0.0,1.0);						//sets the clear colour to yellow

	level.generateLevel(levels);
	tiles = level.getEntityVector();
	platforms = level.getPlatformVector();
	collectables = level.getCollectablesVector();
	spikes = level.getSpikesVector();
	enemies.push_back(&enemy1);
	//enemies.push_back(&enemy2);
	leaves = level.getLeavesVector();
	movingPlatsRight.push_back(&pR1);
	//movingPlatsRight.push_back(&pR2);
	//movingPlatsRight.push_back(&pR3);
	movingPlatsUp.push_back(&pU1);
	//movingPlatsUp.push_back(&pU2);

	//Texturing all entities
	player.texturise(loadPNG(player.entityTexture.texturePath));
	enemy1.texturise(loadPNG(enemy1.entityTexture.texturePath));
	enemy2.texturise(loadPNG(enemy1.entityTexture.texturePath));

	for (Entity* entity : tiles)
	{
		entity->texturise(loadPNG(entity->entityTexture.texturePath));
	}
	for (Entity* spike : spikes)
	{
		spike->texturise(loadPNG(spike->entityTexture.texturePath));
	}
	for (Entity* food : collectables)
	{
		food->texturise(loadPNG(food->entityTexture.texturePath));
	}
	for (Platform* plat : platforms)
	{
		plat->texturise(loadPNG(plat->entityTexture.texturePath));
	}
	for (MovingPlatform* r_plat : movingPlatsRight)
	{
		r_plat->texturise(loadPNG(r_plat->entityTexture.texturePath));
	}
	for (MovingPlatform* u_plat : movingPlatsUp)
	{
		u_plat->texturise(loadPNG(u_plat->entityTexture.texturePath));
	}
	for(Entity* l : leaves)
	{
		l->texturise(loadPNG(l->entityTexture.texturePath));
	}


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}




void update()
{
	keyOperations();
	glutPostRedisplay();
}
/**************** END OPENGL FUNCTIONS *************************/
int main(int argc, char **argv)
{
	glutInit(&argc,argv);
	//For some reason the keys are flickering between T/F and can't get proper input
	//at the beginning. So setting to false just to be safe.
	keyStates['w'] = false;
	keyStates['s'] = false;
	keyStates['a'] = false;
	keyStates['d'] = false;
	keyStates[27] = false;
	keyStates['r'] = false;
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(screenWidth, screenHeight);
   	glutInitWindowPosition(100,100);
	
	glutCreateWindow("My Game");
	
	init();
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(update);
	
	//add keyboard callback.
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);

	glutMainLoop();
	
	return 0;
}


