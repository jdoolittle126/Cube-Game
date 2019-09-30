#include "Libs.h"
#include "Entity.cpp"

#define TITLE "Bouncing Square in a Tractor Trailer Truck"

using namespace std;


#include "Game.h"


// --- CONSTANTS --- //

const int	WINDOW_WIDTH = 640,
			WINDOW_HEIGHT = 480,
			WINDOW_START_POS_X = 50,
			WINDOW_START_POS_Y = 50;

/*
const char*
			TITLE = "Bouncing Square in a Tractor Trailer Truck";
*/

float delta, ts, _ts;

list<Entity> entity_list;

void update_delta() {
	ts = glutGet(GLUT_ELAPSED_TIME);
	delta = ts - _ts;
	_ts = ts;
}

void init(){
	glClearColor(0.0, 0.0, 0.0, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_FLAT);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

}

void update(){
	update_delta();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutSwapBuffers();
	glutPostRedisplay();
}

void display(){

	update();

}

void reshape(GLsizei width, GLsizei height) {
	if (height == 0) height++;
	GLfloat aspect = (GLfloat) width / (GLfloat) height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(WINDOW_START_POS_X, WINDOW_START_POS_Y);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow(TITLE);
	init();
	glutIdleFunc(update);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();

	return 0;
}

void build_window(){
	glutInit();
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(WINDOW_START_POS_X, WINDOW_START_POS_Y);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow(TITLE);
	init();
	glutIdleFunc(update);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}


