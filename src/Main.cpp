
#include "cGame.h"

//Delete console
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

cGame Game;

void reshape(int w, int h)
{
	Game.Reshape(w,h);
}
void render()
{
	Game.Render();
}
void keyboard(unsigned char key, int x, int y)
{
	Game.ReadKeyboard(key,x,y,true);
}
void keyboard_up(unsigned char key, int x, int y)
{
	Game.ReadKeyboard(key,x,y,false);
}
void keyboard_special_keys(int key, int x, int y)
{
	Game.ReadSpecialKeyboard(key,x,y,true);
}
void keyboard_special_keys_up(int key, int x, int y)
{
	Game.ReadSpecialKeyboard(key,x,y,false);
}
void mouse(int button, int state, int x, int y)
{
	Game.ReadMouse(button,state,x,y);
}
void mouse_move(int x, int y)
{
	Game.ReadMouseMotion(x,y);
}
void tick()
{
	if(!Game.Loop()) exit(0);
}

void main(int argc, char** argv)
{
	int RES_WIDTH,RES_HEIGHT,pos_x,pos_y;

	// --- INIT --- //
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	//Create centered window
	RES_WIDTH = glutGet(GLUT_SCREEN_WIDTH);
	RES_HEIGHT = glutGet(GLUT_SCREEN_HEIGHT);
	pos_x = (RES_WIDTH>>1)-(SCREEN_WIDTH>>1);
	pos_y = (RES_HEIGHT>>1)-(SCREEN_HEIGHT>>1);
	
	glutInitWindowPosition(pos_x,pos_y);
	glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);
	glutCreateWindow("The Ballenger");
	glutFullScreen();

	//Make the default cursor disappear
	glutSetCursor(GLUT_CURSOR_NONE);

	//Register callback functions
	glutReshapeFunc(reshape);
	glutDisplayFunc(render);			
	glutKeyboardFunc(keyboard);		
	glutKeyboardUpFunc(keyboard_up);	
	glutSpecialFunc(keyboard_special_keys);	
	glutSpecialUpFunc(keyboard_special_keys_up);
	glutMouseFunc(mouse);
    glutMotionFunc(mouse_move);
    glutPassiveMotionFunc(mouse_move);
	glutIdleFunc(tick);

	//GLEW initialization
	GLint GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult)
	{
		printf("ERROR: %s\n",glewGetErrorString(GlewInitResult));
		exit(EXIT_FAILURE);
	}

	//Game initializations
	Game.Init(1);

	//Application loop
	glutMainLoop();	
}
