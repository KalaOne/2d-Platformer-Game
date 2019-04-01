//includes areas for keyboard control, mouse control, resizing the window
//and draws a spinning rectangle

#include "GL\freeglut.h"
#include <math.h>
#include <iostream>
#include <chrono>
#include <string>


using namespace std;

int screenWidth=720, screenHeight=480;
bool* keyStates = new bool[256];
float grav = 0;
float camX = 0, camY = 0;
string levelTexture = "";
int levelWidth = 50, levelHeight = 20;
int oldStartTime = 0;
int deltaTime;

//OPENGL FUNCTION PROTOTYPES
void display();				//called in winmain to draw everything to the screen
void reshape(int width, int height);				//called when the window is resized
void init();				//called in winmain when the program starts.
void keyfunction(unsigned char key, int x, int y);
void update();				//called in winmain to update variables


class Entity {
public:
	float posX = 0, posY = 0, velX = 0, velY = 0;
	bool grounded = true;
	bool lPressed = false;
	bool rPressed = false;
	float newPosX, newPosY;

	//Updating position of the entity
	void updatePos() {
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

	//Constructor for positioning the entity
	Entity() {
		posX = 0;
		posY = 0;
	}

	Entity(float x, float y) {
		posX = x;
		posY = y;
	}

	//Draws entity
	void drawEntity() {
		updatePos();
		//add texture to the polygon here.
		glBegin(GL_POLYGON);
		glVertex2d(posX, posY);	 //bottom left
		glVertex2d(posX + 50, posY); //bottom right
		glVertex2d(posX + 50, posY + 50); //top right
		glVertex2d(posX, posY + 50);//top left
		glEnd();
	}
};
Entity player(0,0);

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
	int tileWidth = 50;
	int tileHeight = 50;
	
	levelTexture += "@-----------------=--=-=-=-===--=-=--------------@";
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
	levelTexture += "@----=-------=----------------------=------------@";
	levelTexture += "@---=---------=---------------------=------====--@";
	levelTexture += "@---=----------==-------------------=------=--=--@";//20
	//try inversing the loop to get the right area. GEE GEE
	for (int x = 0; x < levelWidth; x++) {
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
void gravity() {
	if (player.posY > 0) {//if player is in the air, reduce velocity
		player.velY -= 0.025;
	}
	if (player.posY <= 0) { //if player is on the ground, set ground to false
		player.grounded = true;
		player.posY = 0; //dont allow player to fall below ground
		player.velY = 0;
	}
}

void camera() {
	//call camera on the centre of playerPos
	camX = player.posX - (screenWidth / 2);
	camY = player.posY - (screenHeight / 2);
	//clamping camera
	if (camX <= 0) camX = 0;
	if (camY <= 0) camY = 0;
//these dont look right.
	/*if (camX >= screenWidth) {
		camX = screenWidth / 2 - player.posX;
	}
	if (camY >= screenHeight) {
		camY = screenHeight / 2 - player.posY;
	}*/

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
	if (keyStates['w']) {
		if (player.grounded) {
			player.velY += 3;
			player.grounded = false;
		}
	}
	if (keyStates['s']) {
		player.velY -= 0.5;
	}

	if (keyStates['a']) {
		player.velX -= 0.5;
	}

	if (keyStates['d']) {
		player.velX += 0.5;
	}
}

void display()																	
{	
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	//delta time
	int startTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = startTime - oldStartTime;
	oldStartTime = startTime;

	
	camera();
	keyOperations();
	drawLevel();
	glPointSize(10.0);
	glColor3f(0, 1, 0);
	player.drawEntity(); //draw player polygon

	glFlush();
	glutSwapBuffers();
	gravity();
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
	//glClear(GL_COLOR_BUFFER_BIT) in the display function
	//will clear the buffer to this colour.
}




void update()
{

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


