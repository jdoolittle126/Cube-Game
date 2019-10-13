#include "Entity/Entity.h"
#include "Map/WorldMap.h"
#include "Core/Model.h"
#include "Core/Camera.h"
#include <iostream>
#include <fstream>
#include <string>

#define TITLE "hehe"

// --- CONSTANTS --- //

const int	WINDOW_WIDTH = 640,
			WINDOW_HEIGHT = 480;

// --- -------- --- //


GLuint programID;

float x = 0.0f, y = 2.0f, z = 1.0f;

class Game {
	private:
		float delta, ts, _ts;
		GLdouble 	cam_x = 0.0, cam_y = 0.0, cam_z = 0.0,
					cam_focus_x = 0.0, cam_focus_y = 0.0, cam_focus_z = 0.0,
					cam_yaw = 0.0, cam_pitch = 1.0, cam_roll = 0.0;
		bool dragging = false;
		float m_x = 0, m_y = 0, _m_x, _m_y;
		float gravity = -9.81f;

		Camera* camera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT);
		WorldMap* map = new WorldMap();
		Entity* test = new Entity(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, new Model("E:\\Workspaces\\eclipse-workspace-cpp\\Cube Game\\src\\Assets\\Models\\squid.obj")); //new Model("E:\\Workspaces\\eclipse-workspace-cpp\\Cube Game\\src\\Assets\\Models\\squid.obj")
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
			map->update(delta, programID);
			for(auto &obj : object_list) {
			    obj->update(delta, programID);
			}
		}

		void display() {

			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			GLuint proj = glGetUniformLocation(programID, "mat_projection");
			GLuint view = glGetUniformLocation(programID, "mat_view");
			//std::cout << glm::to_string(camera->projection) << "\n";
			glUniformMatrix4fv(proj, 1, GL_FALSE, &camera->projection[0][0]);
			glUniformMatrix4fv(view, 1, GL_FALSE, &camera->view[0][0]);

			map->display(delta, programID);
			for(auto &obj : object_list) {
			    obj->display(delta, programID);
			}
		}

		void build_map() {

			for(int i = 0; i < 5; i++){
				map->create_tile(i, -2.0f+i, -5.0f-i);
				map->create_tile(-i, -2.0f+i, -5.0f-i);
			}

		}

		void keyboard(unsigned char key, int x, int y, bool up, int mod) {
			if(up) {
				//gluLookAt(cam_x, cam_y, cam_z, cam_focus_x, cam_focus_y, cam_focus_z, cam_yaw, cam_pitch, cam_roll);
				switch(key){
					case '1': camera->translate(0, 0, -0.5f); break;
					case '2': camera->translate(0, 0, 0.5f); break;
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

		}

};

Game* game;
float w_x, w_y;

// --- -------- --- //

GLuint setup_shaders() {
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	std::ifstream stream;
	stream.open("src/GLSL/Shaders/Vertex/shader.vertex", std::ios::in);
	std::string line = "", content_vert, content_frag;

	while(!stream.eof()) {
		std::getline(stream, line);
		content_vert.append(line + "\n");
	}

	stream.close();

	stream.open("src/GLSL/Shaders/Fragment/shader.fragment", std::ios::in);

	while(!stream.eof()) {
		std::getline(stream, line);
		content_frag.append(line + "\n");
	}

	stream.close();

    const char *vs = content_vert.c_str();
    const char *fs = content_frag.c_str();

	glShaderSource(VertexShaderID, 1, &vs, NULL);
	glCompileShader(VertexShaderID);

	glShaderSource(FragmentShaderID, 1, &fs, NULL );
	glCompileShader(FragmentShaderID );

	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);


	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}


void reshape(int w, int h) {
	game->reshape(w, h);
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(programID);
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
	programID = setup_shaders();
	game = new Game();
	game->init();
	glutMainLoop();	
	return 0;
}
