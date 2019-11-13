#include "Entity/Entity.h"
#include "Map/WorldMap.h"
#include "Core/Model.h"
#include "Core/Camera.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Core/ShaderManager.h"

#define TITLE "hehe"

// --- CONSTANTS --- //

const int	WINDOW_WIDTH = 640,
			WINDOW_HEIGHT = 480;

// --- -------- --- //

/*
 * Inf Worlds
 * Models and Model List
 * Squid eating and size increase
 * Dryness factor ?
 * Smooth Camera
 * Simple Animations (CPU or GPU sided) (More models, or calculated submodel movements?)
 * Texturing
 * Lighting
 * Memory Leaks!
 */

void initGlut();
void initGL();
void initLights();

ShaderManager shader_manager;

int honk = 0;
int nbFrames = 0;
float delta_ag = 0;

class Game {
	private:
		float delta, ts, _ts = 0.0f;
		GLdouble 	cam_x = 0.0, cam_y = 0.0, cam_z = 0.0,
					cam_focus_x = 0.0, cam_focus_y = 0.0, cam_focus_z = 0.0,
					cam_yaw = 0.0, cam_pitch = 1.0, cam_roll = 0.0;
		bool dragging = false;
		float m_x = 0, m_y = 0, _m_x, _m_y;
		float gravity = -9.81f;

		Camera* camera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT);
		GLuint textureId = build_texture("src\\Assets\\Road.bmp", GL_TEXTURE_2D);
		WorldMap* map = new WorldMap(textureId);
		//std::vector<Model*> yeehaw = {new Model("src\\Assets\\Models\\squid_2.obj"), new Model("src\\Assets\\Models\\squid_1.obj"), new Model("src\\Assets\\Models\\squid_3.obj"), new Model("src\\Assets\\Models\\squid_1.obj")};
		Entity* test = new Entity(1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, new Model("src\\Assets\\Models\\squid.obj", "src\\Assets\\Models\\UV.bmp"));
		//Entity* test = new Entity(1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, new Model("src\\Assets\\Models\\untitled.obj", "src\\Assets\\Models\\Grass.bmp"));
		//WorldObject* car = new WorldObject(0.05f, -6.5f, 0.0f, -25.0f, 0.0f, 0.0f, 0.0f, new Model("src\\Assets\\Models\\building.obj"));
		std::vector<GameObject*> object_list;

	public:
		bool running = true;

		void update_delta() {
			ts = glutGet(GLUT_ELAPSED_TIME);
			delta = (ts - _ts) / 1000.0f;
			_ts = ts;

			nbFrames++;
			delta_ag += delta;
			if (delta_ag >= 1.0f ){ // If last prinf() was more than 1sec ago
				printf("%f ms/frame\n", 1000.0/double(nbFrames));
				printf("%i FPS\n", nbFrames);
				nbFrames = 0;
				delta_ag -= 1.0f;
			}

		}

		void update() {
			update_delta();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			map->update(delta);
			for(auto &obj : object_list) {
			    obj->update(delta);
			}
		}

		void display() {
			camera->set_pos(test->get_pos_x(), test->get_pos_y()+(2.0f*test->get_scale_y()), test->get_pos_z()+(4.0f*test->get_scale_z()));
			camera->look_at(test->get_pos_x(), test->get_pos_y(), test->get_pos_z());

		    for (std::map<std::string, GLuint>::iterator i = shader_manager.get_shaders().begin(); i != shader_manager.get_shaders().end(); ++i) {
		    	glUseProgram(i->second);
				glUniformMatrix4fv(glGetUniformLocation(i->second, "mat_projection"), 1, GL_FALSE, &camera->projection[0][0]);
				glUniformMatrix4fv(glGetUniformLocation(i->second, "mat_view"), 1, GL_FALSE, &camera->view[0][0]);
		    }

			map->display(delta, shader_manager);
			for(auto &obj : object_list) {
			    obj->display(delta, shader_manager);
			}
		}

		void build_map() {

			for(int i = -5; i < 5; i++){
				for(int j = -5; j < 5; j++){
					map->create_tile(i, -1.0f, -j, i+6, j+6);
				}
			}

		}

		void keyboard(unsigned char key, int x, int y, bool up, int mod) {
			if(up) {
				switch(key){
					case '1': honk = 0; break;
					case '2': honk = 1; break;
					case 'a': test->set_vel_x(-3.0f); break;
					case 'd': test->set_vel_x(3.0f); break;
					case 's': test->set_vel_z(3.0f); break;
					case 'w': test->set_vel_z(-3.0f); break;
					case 'q': test->set_vel_yaw(-5.0f); break;
					case 'e': test->set_vel_yaw(5.0f); break;
					case 'r': test->allow_accels(true); break;
					case 'o': build_map();break;
					case 32: test->set_vel_y(5.0f); break;
					case 'x': exit(0);
				}
			} else {
				switch(key){
					case 'a': test->set_vel_x(0.0f); break;
					case 'd': test->set_vel_x(0.0f); break;
					case 's': test->set_vel_z(0.0f); break;
					case 'w': test->set_vel_z(0.0f); break;
					case 'q': test->set_vel_yaw(0.0f); break;
					case 'e': test->set_vel_yaw(0.0f); break;
				}
			}
		}

		void keyboard_special(int key, int x, int y, bool up, int mod) {

		}

		void mouse(int button, int state, int x, int y) {
			switch(button) {
				case GLUT_LEFT_BUTTON: {
					 if(state == GLUT_DOWN) {
						 dragging = true;
					     _m_x = x;
					     _m_y = y;
					 } else {
						 dragging = false;
					}
				}
			}
		}

		void mouse_move(int x, int y) {

		}

		void reshape(GLsizei width, GLsizei height) {
			if (height == 0) height++;
			camera->reshape((GLfloat) width, (GLfloat) height);

		}

		void keyboard(){

		}

		Game(){
			test->set_world_map(map);
			object_list.push_back(test);
			//object_list.push_back(car);

		}

};

Game* game;
float w_x, w_y;

// --- -------- --- //

void setup_shaders() {
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

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	int pos_x = (glutGet(GLUT_SCREEN_WIDTH)>>1)-(WINDOW_WIDTH>>1);
	int pos_y = (glutGet(GLUT_SCREEN_HEIGHT)>>1)-(WINDOW_HEIGHT>>1);
	
	glutInitWindowPosition(pos_x,pos_y);
	glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
	glutCreateWindow(TITLE);

	if (GLEW_OK != glewInit())
	{
		std::cout << "no worky worky" << std::endl;
	}

	w_x = static_cast<float>(glutGet(GLUT_SCREEN_WIDTH) / 2.0f); //(WINDOW_WIDTH / 2.0f)
	w_y = static_cast<float>(glutGet(GLUT_SCREEN_HEIGHT) / 2.0f); //WINDOW_HEIGHT / 2.0f)

	//glutFullScreen();
	//Make the default cursor disappear
	//glutSetCursor(GLUT_CURSOR_NONE);

	initGlut();
	initGL();

	setup_shaders();
	game = new Game();
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


