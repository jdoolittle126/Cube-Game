#include "Core/Game.h"

/*
 * Inf Worlds
 * Models and Model List
 * Squid eating and size increase
 * Dryness factor ?
 * Smooth Camera
 * Simple Animations (CPU or GPU sided) (More models, or calculated submodel movements?)
 * Texturing
 * Shader Compile Errors
 * Lighting
 * Create NO new GL objects on a by-frame basis!
 * Fix Icon!
 * Culling?
 *
 * CURRENT:
 * Finish Managers and impl
 * Move Unique Tile thing into managers
 *
 * Finish this, then HUD
 */

void initGlut(int argc, char** argv);
void initGlew();
void initFreeType();
void initGL();
void reshape(int w, int h);
void render();
void keyboard(unsigned char key, int x, int y);
void keyboard_up(unsigned char key, int x, int y);
void keyboard_special_keys(int key, int x, int y);
void keyboard_special_keys_up(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void mouse_move(int x, int y);
void tick();
void unload_program();

static GameManager * game_manager;
static Game * game;

// --- -------- --- //

int main(int argc, char** argv) {
	initGlut(argc, argv);
	initGlew();
	initFreeType();
	initGL();
	game_manager = new GameManager();
	game = new Game(*game_manager);
	glutMainLoop();

	unload_program();
	return 0;
}

void initGlut(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	int pos_x = (glutGet(GLUT_SCREEN_WIDTH)>>1)-(WINDOW_WIDTH>>1);
	int pos_y = (glutGet(GLUT_SCREEN_HEIGHT)>>1)-(WINDOW_HEIGHT>>1);
	glutInitWindowPosition(pos_x,pos_y);
	glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
	glutCreateWindow(WINDOW_TITLE);
	//glutSetIconTitle("src/Assets/Icons/squid.ico");
	//glutFullScreen();
	//glutSetCursor(GLUT_CURSOR_NONE);
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
}

void initGlew() {
	if (GLEW_OK != glewInit()) log_error(ERROR_GLEW_INIT_FAIL);
}

void initFreeType() {

}

void initGL() {
    glShadeModel(GL_SMOOTH);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0, 0, 0, 0);
    glClearStencil(0);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);

}


void reshape(int w, int h) {
	game->reshape(w, h);
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	game->update();
	game->display();
	glutSwapBuffers();
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	int mod = glutGetModifiers();
	game->keyboard(key, x, y, true, mod);
}

void keyboard_up(unsigned char key, int x, int y) {
	game->keyboard(key, x, y, false, 0);
}

void keyboard_special_keys(int key, int x, int y) {
	int mod = glutGetModifiers();
	game->keyboard_special(key, x, y, true, mod);
}

void keyboard_special_keys_up(int key, int x, int y) {
	game->keyboard_special(key, x, y, false, 0);
}

void mouse(int button, int state, int x, int y) {
	game->mouse(button, state, x, y);
}

void mouse_move(int x, int y) {
	game->mouse_move(x, y);
}

void tick() {
	//glutWarpPointer(w_x, w_y);
}

void unload_program() {
	delete game;
}


