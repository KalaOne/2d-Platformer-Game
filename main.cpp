//includes areas for keyboard control, mouse control, resizing the window
//and draws a spinning rectangle

//#include "Platform.h"
#include "Image_Loading/nvImage.h"
#include <vector>
#include "Entity.h"
#include "Level.h"
#include "Platform.h"
#include "Player.h"



using namespace std;

int screenWidth=720, screenHeight=480;
bool* keyStates = new bool[256];
float grav = 0;
float camX = 0, camY = 0;
float oldTime = 0.0;
float dt;
int levels = 1;


//OPENGL FUNCTION PROTOTYPES
void display();				//called in winmain to draw everything to the screen
void reshape(int width, int height);				//called when the window is resized
void init();				//called in winmain when the program starts.
void keyfunction(unsigned char key, int x, int y);
void update();				//called in winmain to update variables


Level level;
Player player(50,0, 49, 49); // keep in mind each field/tile size is 50. x=1;
Entity enemy1(300, 0, 25, 25);
Platform plat1(500, 50, 150, 20);
Platform plat2(250, 25, 100, 30);
vector<Entity> allEntities;
vector<Platform> platforms;

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
		cout << "Failed to load texture. End of the world" << endl;;

	return myTextureID;
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
	
	//plat1.drawPlatform(1500, 1, 0, dt);
	//plat2.drawPlatform(2000, 0, 1, dt);

	level.drawLevel(1, dt);
	player.drawEntity(0,dt);
	enemy1.drawEntity(1,dt);

	//player collides with everything else.
	for(Entity ent : allEntities)
	{
		player.AABB(ent);
	}
	for(Platform p : platforms)
	{
		player.platformAABB(p);
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
	player.activeSprite = loadPNG("Assets/platform_gfx/hero/idle.png");
	enemy1.activeSprite = loadPNG("Assets/platform_gfx/baddies/Totem_stand.png");

	//glEnable(GL_BLEND);
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

	level.generateLevel(1);
	allEntities = level.getEntityVector();
	platforms = level.getPlatformVector();

	glutMainLoop();
	
	return 0;
}


