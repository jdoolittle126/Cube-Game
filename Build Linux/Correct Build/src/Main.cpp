#include "Game.h"

#define TITLE "hehe"

/*
 * Technical:
 * Move Strings to a defines header
 * Orginize libraries
 *
 *
 * Inf Worlds
 * Models and Model List
 * Squid eating and size increase
 * Dryness factor ?
 * Smooth Camera
 * Simple Animations (CPU or GPU sided) (More models, or calculated submodel movements?)
 * Texturing
 * Lighting
 * Memory Leaks!
 * Create NO new GL objects on a by-frame basis!
 * Fix Icon!
 * Culling?
 */

void initGlut();
void initGL();
void setup_shaders();
void reshape(int w, int h);
void render();
void keyboard(unsigned char key, int x, int y);
void keyboard_up(unsigned char key, int x, int y);
void keyboard_special_keys(int key, int x, int y);
void keyboard_special_keys_up(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void mouse_move(int x, int y);
void tick();

static ShaderManager shader_manager;

static Game * game;

// --- -------- --- //

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	int pos_x = (glutGet(GLUT_SCREEN_WIDTH)>>1)-(WINDOW_WIDTH>>1);
	int pos_y = (glutGet(GLUT_SCREEN_HEIGHT)>>1)-(WINDOW_HEIGHT>>1);
	glutInitContextVersion(3,3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	
	glutInitWindowPosition(pos_x,pos_y);
	glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
	glutCreateWindow(TITLE);
	//glutSetIconTitle("src/Assets/Icons/squid.ico");

	if (GLEW_OK != glewInit()) std::cout << "no worky worky" << std::endl;

	//glutFullScreen();
	//Make the default cursor disappear
	//glutSetCursor(GLUT_CURSOR_NONE);

	initGlut();
	initGL();
	setup_shaders();
	game = new Game(shader_manager);
	glutMainLoop();

	return 0;
}
void initGlut() {

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

void initGL() {
    glShadeModel(GL_SMOOTH);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glClearColor(0, 0, 0, 0);
    glClearStencil(0);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);

}

void setup_shaders() {
	std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	shader_manager.create_shader("Debug", "src/GLSL/Shaders/Fragment/debug.fragment", "src/GLSL/Shaders/Vertex/debug.vertex");
	shader_manager.create_shader("WorldObj", "src/GLSL/Shaders/Fragment/world_obj.fragment", "src/GLSL/Shaders/Vertex/world_obj.vertex");
	shader_manager.create_shader("Tile", "src/GLSL/Shaders/Fragment/tile.fragment", "src/GLSL/Shaders/Vertex/tile.vertex");
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



