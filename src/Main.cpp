#include "Entity/Entity.h"
#include "Map/WorldMap.h"

#define TITLE "hehe"

// --- CONSTANTS --- //

const int	WINDOW_WIDTH = 640,
			WINDOW_HEIGHT = 480;


// --- -------- --- //

class Game {
	private:
		float delta, ts, _ts;
		GLdouble 	cam_x = 0.0, cam_y = 0.0, cam_z = 0.0,
					cam_focus_x = 0.0, cam_focus_y = 0.0, cam_focus_z = 0.0,
					cam_yaw = 0.0, cam_pitch = 1.0, cam_roll = 0.0;
		bool dragging = false;
		float m_x = 0, m_y = 0, _m_x, _m_y;
		float gravity = -9.81f;

		WorldMap* map = new WorldMap();
		Entity* test = new Entity(0.5f, 0.0f, 0.0f, -2.0f, 0.0f, 0.0f, 0.0f);
		std::vector<GameObject*> object_list;

	public:
		bool running = true;

		void update_delta() {
			ts = glutGet(GLUT_ELAPSED_TIME);
			delta = ts - _ts;
			_ts = ts;
		}

		void init() {
			glClearColor(0.0, 0.0, 0.0, 1.0f);
			glClearDepth(1.0f);
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LEQUAL);
			glShadeModel(GL_FLAT);
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
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
			map->display(delta);
			for(auto &obj : object_list) {
			    obj->display(delta);
			}
		}

		void keyboard(unsigned char key, int x, int y, bool up, int mod) {
			if(up) {
				//gluLookAt(cam_x, cam_y, cam_z, cam_focus_x, cam_focus_y, cam_focus_z, cam_yaw, cam_pitch, cam_roll);
				switch(key){
					case 'a': test->set_vel_x(-3.0f); break;
					case 'd': test->set_vel_x(3.0f); break;
					case 's': test->set_vel_z(3.0f); break;
					case 'w': test->set_vel_z(-3.0f); break;
					case 'q': test->set_vel_yaw(-45.0f); break;
					case 'e': test->set_vel_yaw(45.0f); break;
					case 'r': test->allow_accels(true); break;
					case 'o': map->create_tile(0.0f, -1.0f, -2.0f); break;
					case 'p': map->create_tile(-1.0f, 0.0f, -2.0f); break;
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
			/*
			if(dragging) {
				cam_focus_x += (x - _m_x)*0.0001f;
				cam_focus_y += (y - _m_y)*-0.0001f;
			    _m_x = x;
			    _m_y = y;
			} else {
				cam_focus_x = 0;
				cam_focus_y = 0;
			}
			*/
		}

		void reshape(GLsizei width, GLsizei height) {
			if (height == 0) height++;
			GLfloat aspect = (GLfloat) width / (GLfloat) height;
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glViewport(0, 0, width, height);
			gluPerspective(45.0f, aspect, 0.1f, 100.0f);
		}

		void keyboard(){

		}

		Game(){
			test->set_world_map(map);
			object_list.push_back(test);

		}

};



Game* game = new Game();
float w_x, w_y;

void reshape(int w, int h) {
	game->reshape(w, h);
}

void render() {
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

	w_x = static_cast<float>(glutGet(GLUT_SCREEN_WIDTH) / 2.0f); //(WINDOW_WIDTH / 2.0f)
	w_y = static_cast<float>(glutGet(GLUT_SCREEN_HEIGHT) / 2.0f); //WINDOW_HEIGHT / 2.0f)

	//glutFullScreen();
	//Make the default cursor disappear
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

	game->init();
	glutMainLoop();	
	return 0;
}
