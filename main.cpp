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
int levels = 1;
bool enemyCollide = false;
float startTime = 0;
float currentTime = 0;
int numCollect = 0;

struct Time
{
	int mm = 0, ss = 0, ms = 0, totalTime = 0, remMS = 0;
	string min = "", sec = "", msec = "";
	string time = "";
	string displayScore = "Time so far: " + time;
};

Time t;
vector<Entity*> tiles;
vector<Entity*> collectables;
vector<Entity*> spikes;
vector<Entity*> leaves;
vector<Platform*> platforms;
vector<MovingPlatform*> movingPlatsRight;
vector<MovingPlatform*> movingPlatsUp;
vector<Enemy*> enemies;
string collectableDisplay = to_string(numCollect) + " collectables.";

//OPENGL FUNCTION PROTOTYPES
void display();				//called in winmain to draw everything to the screen
void reshape(int width, int height);				//called when the window is resized
void init();				//called in winmain when the program starts.
void keyfunction(unsigned char key, int x, int y);
void update();				//called in winmain to update variables#
void texturise();
void addTextures();
void applyCollision();
void calcTime();
void drawScoringScreen();
void drawStartScreen();
GLuint loadPNG(char* name);
void displayTimer();
GLuint bg;
GLuint startScreen;

Level level;
Player player(950,550, 49, 49, "Assets/platform_gfx/hero/hero.png"); // keep in mind each field/tile size is 50. x=1;
Enemy enemy1(200, 0, 50, 50, "Assets/platform_gfx/baddies/output.png"); // closest to left
Enemy enemy2(1750, 400, 50, 50, "Assets/platform_gfx/baddies/output.png");

MovingPlatform pR1(220,250,150,20,1350,"Assets/platform_gfx/tiles/block2.png");
MovingPlatform pR2(1000,500,50,20, 950,"Assets/platform_gfx/tiles/block2.png");
MovingPlatform pR3(1600, 175, 30,20,800, "Assets/platform_gfx/tiles/block2.png");
//MovingPlatform pU1(300,10,150,20,600, "Assets/platform_gfx/tiles/block2.png");
//MovingPlatform pU2(300,50,150,20,200, "Assets/platform_gfx/tiles/block2.png");


//function to display the timer
void displayTimer(string str, float x, float y,float r, float g, float b)
{
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	for(char c : str){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}
}

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
	if(levels == 0)
	{
		if(keyStates[13] || keyStates[10])
		{
			level.updateLevel(levels);
			level.drawLevel(dt);
		}
	}
	if(keyStates['r'])
	{
		player.newPosX = 50;
		player.newPosY = 0;
		startTime = currentTime;
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

void addTextures()
{
	//Texturing all entities
	player.texturise(loadPNG(player.entityTexture.texturePath));
	enemy1.texturise(loadPNG(enemy1.entityTexture.texturePath));
	enemy2.texturise(loadPNG(enemy2.entityTexture.texturePath));

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
	for (Entity* l : leaves)
	{
		l->texturise(loadPNG(l->entityTexture.texturePath));
	}

}
void applyCollision()
{
	//player collides with everything else.
	for (Enemy* e : enemies)//enemies
	{
		player.AABB(*e);
	}
	for (Entity* ent : tiles)//world objects
	{
		player.AABB(*ent);
	}
	for (Platform* p : platforms)//static platforms
	{
		player.platformAABB(*p);
	}
	for (MovingPlatform* m_plat : movingPlatsRight)//platforms moving x
	{
		player.movingPlatsAABB(*m_plat);
	}
	for (MovingPlatform* m_plat : movingPlatsUp)//platfroms moving y
	{
		player.movingPlatsAABB(*m_plat);
	}
	for (Entity* s : spikes)//spikes
	{
		player.spikeCollision(*s);
	}
	for (Entity* c : collectables)//collectables
	{
		if (player.AABB(*c)) {
			level.setTile(c->getX(), c->getY());
			numCollect++;
		}
	}
	for(Entity* l : leaves) //exits to next level
	{
		if(player.Leaf(*l)){

			cout << "Sleeping...." << endl;
			drawScoringScreen();
			level.generateLevel(level.updateLevel(levels));
			//Sleep(2000);
			//Clear the level vector, generate the level again and draw it.
		}
	}
}

void drawBackground()
{
	
	glPushMatrix();//player movement and drawing
	
	glEnable(GL_TEXTURE_2D);
	//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, bg);
		glColor4f(0,0,0,0);
		glBegin(GL_POLYGON);
			glTexCoord2f(0, 0); glVertex2d(0, 0);	 //bottom left
			glTexCoord2f(1, 0); glVertex2d(800, 0); //bottom right
			glTexCoord2f(1, 1); glVertex2d(800, 600); //top right
			glTexCoord2f(0, 1); glVertex2d(0, 600);//top left
		glEnd();
	glDisable(GL_TEXTURE_2D);
	//glDisable(GL_BLEND);
	//glColor3f(1, 1, 1);
	glPopMatrix();
}

void drawStartScreen()
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, startScreen);
		glColor4f(0, 0, 0, 1);
		glBegin(GL_POLYGON);
			glTexCoord2f(0, 0); glVertex2d(0, 0);	 //bottom left
			glTexCoord2f(1, 0); glVertex2d(screenWidth , 0); //bottom right
			glTexCoord2f(1, 1); glVertex2d(screenWidth, screenHeight); //top right
			glTexCoord2f(0, 1); glVertex2d(0, screenHeight);//top left
		glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void drawScoringScreen()
{
	glPushMatrix();
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
			 glVertex2d(0, 0);	 //bottom left
			 glVertex2d(800, 0); //bottom right
			 glVertex2d(800, 600); //top right
			 glVertex2d(0, 600);//top left
	glEnd();
	glPopMatrix();
	calcTime();
	displayTimer(collectableDisplay, screenWidth / 2 - 100, screenHeight / 2 + 50, 0.8, 0, 0.2);
	displayTimer(t.displayScore,screenWidth / 2 - 200,screenHeight / 2, 0.8,0,0.2);
}
void calcTime()
{
	t.totalTime = currentTime;
	t.mm = t.totalTime % 60000;
	t.remMS = currentTime - t.mm;
	t.ss = t.remMS % 1000 - numCollect;
	t.min = to_string(t.mm);
	t.sec = to_string(t.ss);
	t.time = t.min + ":" + t.sec;
}

void display()																	
{	
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	drawBackground();
	//delta time
	float newTime = glutGet(GLUT_ELAPSED_TIME);
	dt = (newTime - oldTime) * 0.75;
	oldTime = newTime;
	
	
	if (levels == 0)
	{
		drawStartScreen();
	}
	if (levels % 2 != 0 && levels != 0) {
		currentTime = glutGet(GLUT_ELAPSED_TIME);
		camera();
		applyCollision();
		level.drawLevel(dt);
		player.drawEntity(dt);
		enemy1.drawEnemy(550, dt);
		enemy2.drawEnemy(420, dt);
		for (MovingPlatform* r_p : movingPlatsRight)
		{
			r_p->drawPlatformRight(dt);
		}
		displayTimer(to_string(currentTime - startTime), camX + 625, camY + 450, 0, 0, 0);
		player.gravity(dt);
	}
	else
	{
		drawScoringScreen();
		//Sleep(2000);
		level.generateLevel(level.updateLevel(levels));
	}
	
	//drawing and updating moving platforms
	//for(MovingPlatform* u_p: movingPlatsUp)
	//{
	//	u_p->drawPlatformUp(dt);
	//}
	
	
	
	

	//displayTimer(to_string(currentTime), camX + 625, camY + 450,0,0,0.5);
	//displayTimer(to_string(startTime), camX + 625, camY + 350,0, 0.5, 0);
	
	
	glFlush();
	glutSwapBuffers();
	
	
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
	startScreen = loadPNG("Assets/StartScreen.png");
	level.generateLevel(levels);
	bg = loadPNG("Assets/background.png");
	tiles = level.getEntityVector();
	platforms = level.getPlatformVector();
	collectables = level.getCollectablesVector();
	spikes = level.getSpikesVector();
	enemies.push_back(&enemy1);
	enemies.push_back(&enemy2);
	leaves = level.getLeavesVector();
	movingPlatsRight.push_back(&pR1);
	movingPlatsRight.push_back(&pR2);
	movingPlatsRight.push_back(&pR3);
	//movingPlatsUp.push_back(&pU1);
	//movingPlatsUp.push_back(&pU2);
	addTextures();
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
	keyStates[13] = false;
	keyStates[10] = false;
	keyStates['r'] = false;
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(screenWidth, screenHeight);
   	glutInitWindowPosition(100,100);
	
	glutCreateWindow("Stagnant Instant");
	
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


