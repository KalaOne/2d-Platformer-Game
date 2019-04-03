//includes areas for keyboard control, mouse control, resizing the window
//and draws a spinning rectangle

#include "Entity.h"
#include "Level.h"


using namespace std;

int screenWidth=720, screenHeight=480;
bool* keyStates = new bool[256];
float grav = 0;
float camX = 0, camY = 0;
int oldStartTime = 0;
int deltaTime;


//OPENGL FUNCTION PROTOTYPES
void display();				//called in winmain to draw everything to the screen
void reshape(int width, int height);				//called when the window is resized
void init();				//called in winmain when the program starts.
void keyfunction(unsigned char key, int x, int y);
void update();				//called in winmain to update variables



Entity player(0,0);
Level level1;


void Level::collision()
{
	int left_tile = player.posX / 50;
	int right_tile = player.posX + 50 / 50;
	int top_tile = player.posY + 50 / 50;
	int bottom_tile = player.posY / 50;

	if (left_tile < 0)
		left_tile = 0;
	if (right_tile > levelWidth)
		right_tile = levelWidth;
	if (top_tile > levelHeight)
		top_tile = levelHeight;
	if (bottom_tile < 0)
		bottom_tile = 0;
	colliding = false;
	for (int i = left_tile; i <= right_tile; i++)
	{
		for (int j = bottom_tile; j <= top_tile; j++)
		{
			char tile = getTile(i, j);
			if (tile == '#')
			{
				colliding = true;
				//cout << "Colliding." << endl;
			}
			colliding = false;
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
	level1.drawLevel();
	glPointSize(10.0);
	glColor3f(0, 1, 0);
	player.drawEntity(deltaTime); //draw player polygon
	//collision();

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


