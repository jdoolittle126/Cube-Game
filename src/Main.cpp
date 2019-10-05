#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>
#include <windef.h>
#include <GL/freeglut.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <list>
#include <iterator>
#include <algorithm>
#include <windows.h>
#include <vector>
#include <math.h>

#define PI 3.14159265
#define TITLE "hehe"

/*
 * TODO
 * Could probably clean up all the getter/setters with vectors (x, y, z) but eh
 * This game will be one mega file don't change my mind
 */

using namespace std;

// --- CONSTANTS --- //

const int	WINDOW_WIDTH = 640,
			WINDOW_HEIGHT = 480;

const float colors[12][3] = {
			{1.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 1.0f},
			{1.0f, 1.0f, 0.0f},
			{1.0f, 0.0f, 1.0f},
			{0.0f, 1.0f, 1.0f},
			{1.0f, 1.0f, 1.0f},
			{0.9f, 0.9f, 0.9f},
			{0.8f, 0.8f, 0.8f},
			{0.7f, 0.7f, 0.7f},
			{0.6f, 0.6f, 0.6f},
			{0.0f, 0.0f, 0.0f}};



class GameObject {
	public:
		virtual void update(float delta) = 0;
		virtual void display(float delta) = 0;
};

class Entity : public GameObject {
	private:
		float 		size,
					bound_x_right = 1.0f,
					bound_y_top = 1.0f,
					bound_z_close = 0.0f,
					bound_x_left = -1.0f,
					bound_y_bottom = -1.0f,
					bound_z_far = -10.0f,
					pos_x,
					pos_y,
					pos_z,
					pos_pitch,
					pos_yaw,
					pos_roll,
					vel_x,
					vel_y,
					vel_z,
					vel_yaw,
					vel_pitch,
					vel_roll,
					accel_x,
					accel_y,
					accel_z,
					accel_yaw,
					accel_pitch,
					accel_roll,
					_pos_x,
					_pos_y,
					_pos_z,
					_pitch,
					_yaw,
					_roll;

		list<glm::vec4*>
					verts;

		glm::vec4 	vert0,
					vert1,
					vert2,
					vert3,
					vert4,
					vert5,
					vert6,
					vert7,
					_vert0,
					_vert1,
					_vert2,
					_vert3,
					_vert4,
					_vert5,
					_vert6,
					_vert7;

		glm::mat4x4 mat_transform,
					_mat_transform,
					mat_translate,
					mat_scale,
					mat_rot;

		bool redraw = true;

	public:
		Entity(float i_size, float i_x, float i_y, float i_z, float i_yaw, float i_pitch, float i_roll){
			size = i_size / 2.0f;
			pos_x = i_x;
			pos_y = i_y;
			pos_z = i_z;
			pos_yaw = i_yaw;
			pos_pitch = i_pitch;
			pos_roll = i_roll;
			vert0 = glm::vec4(-size, size, size, 1.0f);
			vert1 = glm::vec4(-size, size, -size, 1.0f);
			vert2 = glm::vec4(size, size, -size, 1.0f);
			vert3 = glm::vec4(size, size, size, 1.0f);
			vert4 = glm::vec4(-size, -size, size, 1.0f);
			vert5 = glm::vec4(-size, -size, -size, 1.0f);
			vert6 = glm::vec4(size, -size, -size, 1.0f);
			vert7 = glm::vec4(size, -size, size, 1.0f);
			init();
		}

		void update(float delta);
		void display(float delta);
		void init();
		float get_pos_x();
		float get_pos_y();
		float get_pos_z();
		float get_roll();
		float get_yaw();
		float get_pitch();
		void set_pos_x(float n);
		void set_pos_y(float n);
		void set_pos_z(float n);
		void set_pos_roll(float n);
		void set_pos_yaw(float n);
		void set_pos_pitch(float n);
		float get_vel_x();
		float get_vel_y();
		float get_vel_z();
		float get_vel_roll();
		float get_vel_yaw();
		float get_vel_pitch();
		void set_vel_x(float n);
		void set_vel_y(float n);
		void set_vel_z(float n);
		void set_vel_roll(float n);
		void set_vel_yaw(float n);
		void set_vel_pitch(float n);
		float get_accel_x();
		float get_accel_y();
		float get_accel_z();
		float get_accel_roll();
		float get_accel_yaw();
		float get_accel_pitch();
		void set_accel_x(float n);
		void set_accel_y(float n);
		void set_accel_z(float n);
		void set_accel_roll(float n);
		void set_accel_yaw(float n);
		void set_accel_pitch(float n);

		void build_translate(float x, float y, float z);
		void build_scale(float sx, float sy, float sz);
		void build_rot(float _rx, float _ry, float _rz);
		void update_color(int a);
		void draw_face(glm::vec4 a, glm::vec4 b, glm::vec4 c, glm::vec4 d);
		void pos_update(float delta);
		void pos_step_back();
		bool check_collide();
		bool check_collide_x();
		bool check_collide_y();
		bool check_collide_z();

};

void Entity::init() {
	verts.push_back(&_vert0);
	verts.push_back(&_vert1);
	verts.push_back(&_vert2);
	verts.push_back(&_vert3);
	verts.push_back(&_vert4);
	verts.push_back(&_vert5);
	verts.push_back(&_vert6);
	verts.push_back(&_vert7);
}

float Entity::get_pos_x(){
	return pos_x;
}

float Entity::get_pos_y(){
	return pos_y;
}

float Entity::get_pos_z(){
	return pos_z;
}

float Entity::get_yaw(){
	return pos_yaw;
}

float Entity::get_pitch(){
	return pos_pitch;
}

float Entity::get_roll(){
	return pos_roll;
}

void Entity::set_pos_x(float n){
	pos_x = n;
}

void Entity::set_pos_y(float n){
	pos_y = n;
}

void Entity::set_pos_z(float n){
	pos_z = n;
}

void Entity::set_pos_yaw(float n){
	pos_yaw = n;
}

void Entity::set_pos_pitch(float n){
	pos_pitch = n;
}

void Entity::set_pos_roll(float n){
	pos_roll = n;
}

//

float Entity::get_vel_x(){
	return vel_x;
}

float Entity::get_vel_y(){
	return vel_y;
}

float Entity::get_vel_z(){
	return vel_z;
}

float Entity::get_vel_yaw(){
	return vel_yaw;
}

float Entity::get_vel_pitch(){
	return vel_pitch;
}

float Entity::get_vel_roll(){
	return vel_roll;
}

void Entity::set_vel_x(float n){
	vel_x = n;
}

void Entity::set_vel_y(float n){
	vel_y = n;
}

void Entity::set_vel_z(float n){
	vel_z = n;
}

void Entity::set_vel_yaw(float n){
	vel_yaw = n;
}

void Entity::set_vel_pitch(float n){
	vel_pitch = n;
}

void Entity::set_vel_roll(float n){
	vel_roll = n;
}

//

float Entity::get_accel_x(){
	return accel_x;
}

float Entity::get_accel_y(){
	return accel_y;
}

float Entity::get_accel_z(){
	return accel_z;
}

float Entity::get_accel_yaw(){
	return accel_yaw;
}

float Entity::get_accel_pitch(){
	return accel_pitch;
}

float Entity::get_accel_roll(){
	return accel_roll;
}

void Entity::set_accel_x(float n){
	accel_x = n;
}

void Entity::set_accel_y(float n){
	accel_y = n;
}

void Entity::set_accel_z(float n){
	accel_z = n;
}

void Entity::set_accel_yaw(float n){
	accel_yaw = n;
}

void Entity::set_accel_pitch(float n){
	accel_pitch = n;
}

void Entity::set_accel_roll(float n){
	accel_roll = n;
}

void Entity::build_translate(float x, float y, float z) {
	float m[16] = { 1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z, 0, 0, 0, 1 };
	mat_translate = glm::make_mat4x4(m);

}

void Entity::build_scale(float sx, float sy, float sz) {
	float m[16] = { sx, 0, 0, 0, 0, sy, 0, 0, 0, 0, sz, 0, 0, 0, 0, 1 };
	mat_scale = glm::make_mat4x4(m);
}

void Entity::build_rot(float _rx, float _ry, float _rz) {
	float rx = _rx * (PI / 180.0f);
	float ry = _ry * (PI / 180.0f);
	float rz = _rz * (PI / 180.0f);

	float m[16] = { cos(ry) * cos(rz), -cos(ry) * sin(rz), sin(ry), 0, (cos(rx)
			* sin(rz)) + (sin(rx) * sin(ry) * cos(rz)), (cos(rx) * cos(rz))
			- (sin(rx) * sin(ry) * sin(rz)), -sin(rx) * cos(ry), 0, (sin(rx)
			* sin(rz)) - (cos(rx) * sin(ry) * cos(rz)), (sin(rx) * cos(rz))
			+ (cos(rx) * sin(ry) * sin(rz)), cos(rx) * cos(ry), 0, 0, 0, 0, 1 };

	mat_rot = glm::make_mat4x4(m);
}

void Entity:: update_color(int a) {
	glColor3f(colors[a][0], colors[a][1], colors[a][2]);
}

void Entity::draw_face(glm::vec4 a, glm::vec4 b, glm::vec4 c, glm::vec4 d) {
	glVertex3f(a.x, a.y, a.z);
	glVertex3f(b.x, b.y, b.z);
	glVertex3f(c.x, c.y, c.z);
	glVertex3f(d.x, d.y, d.z);
}

void Entity::pos_update(float delta) {
	float d = static_cast<float> (delta) / 1000;

	_mat_transform = mat_transform;
	_pos_x = pos_x;
	_pos_y = pos_y;
	_pos_z = pos_z;
	_pitch = pos_pitch;
	_yaw = pos_yaw;
	_roll = pos_roll;

	vel_x += accel_x * d;
	vel_y += accel_y * d;
	vel_z += accel_z * d;
	vel_pitch += accel_pitch * d;
	vel_yaw += accel_yaw * d;
	vel_roll += accel_roll * d;

	pos_x += vel_x * d;
	pos_y += vel_y * d;
	pos_z += vel_z * d;
	pos_pitch += vel_pitch * d;
	pos_yaw += vel_yaw * d;
	pos_roll += vel_roll * d;

	if (pos_pitch > 360.0f)
		pos_pitch -= 360.0f;
	else if (pos_pitch < 0.0f)
		pos_pitch += 360.0f;
	if (pos_yaw > 360.0f)
		pos_yaw -= 360.0f;
	else if (pos_yaw < 0.0f)
		pos_yaw += 360.0f;
	if (pos_roll > 360.0f)
		pos_roll -= 360.0f;
	else if (pos_roll < 0.0f)
		pos_roll += 360.0f;

}

bool Entity::check_collide(){
	bool d_x = true, d_y = true, d_z = true;
	for(list<glm::vec4*>::iterator iterator = verts.begin(); iterator != verts.end(); iterator++){
		glm::vec4* t = *iterator;
		if((t->x >= bound_x_right || t->x <= bound_x_left) && d_x){
			d_x = false;
		}

		if((t->y >= bound_y_top || t->y <= bound_y_bottom) && d_y){
			d_y = false;
		}

		if((t->z >= bound_z_close || t->z <= bound_z_far) && d_z){
			d_z = false;
		}

	}
	return (!d_x || !d_y || !d_z);
}

bool Entity::check_collide_x(){
	for(list<glm::vec4*>::iterator iterator = verts.begin(); iterator != verts.end(); iterator++){
		glm::vec4* t = *iterator;
		if((t->x >= bound_x_right || t->x <= bound_x_left)){
			return true;
		}
	}
	return false;
}

bool Entity::check_collide_y(){
	for(list<glm::vec4*>::iterator iterator = verts.begin(); iterator != verts.end(); iterator++){
		glm::vec4* t = *iterator;
		if((t->y >= bound_y_top || t->y <= bound_y_bottom)){
			return true;
		}
	}
	return false;
}

bool Entity::check_collide_z(){
	for(list<glm::vec4*>::iterator iterator = verts.begin(); iterator != verts.end(); iterator++){
		glm::vec4* t = *iterator;
		if((t->z >= bound_z_close || t->z <= bound_z_far)){
			return true;
		}
	}
	return false;
}

void Entity::pos_step_back(){
	build_translate(pos_x, pos_y, pos_z);
	build_rot(pos_pitch, pos_yaw, pos_roll);
	build_scale(1.0f, 1.0f, 1.0f);
	mat_transform = mat_rot * mat_translate * mat_scale;
	//mat_transform = _mat_transform;
	_vert0 = vert0 * mat_transform,
	_vert1 = vert1 * mat_transform,
	_vert2 = vert2 * mat_transform,
	_vert3 = vert3 * mat_transform,
	_vert4 = vert4 * mat_transform,
	_vert5 = vert5 * mat_transform,
	_vert6 = vert6 * mat_transform,
	_vert7 = vert7 * mat_transform;
}

void Entity::update(float delta) {
	pos_update(delta);

	build_translate(pos_x, pos_y, pos_z);
	build_rot(pos_pitch, pos_yaw, pos_roll);
	build_scale(1.0f, 1.0f, 1.0f);
	mat_transform = mat_rot * mat_translate * mat_scale;

	_vert0 = vert0 * mat_transform,
	_vert1 = vert1 * mat_transform,
	_vert2 = vert2 * mat_transform,
	_vert3 = vert3 * mat_transform,
	_vert4 = vert4 * mat_transform,
	_vert5 = vert5 * mat_transform,
	_vert6 = vert6 * mat_transform,
	_vert7 = vert7 * mat_transform;

	if(check_collide()) {
		if(check_collide_x()) {
			pos_x = _pos_x;
			vel_x = 0;
		}
		if(check_collide_y()){
			pos_y = _pos_y;
			vel_y = 0;
		} else {
		}
		if(check_collide_z()){
			pos_z = _pos_z;
			vel_z = 0;
		}

		pos_step_back();

	}

}

void Entity::display(float delta) {

		glBegin(GL_QUADS);
			//TOP (a, b, c, d)
			update_color(0);
			draw_face(_vert0, _vert1, _vert2, _vert3);

			//BOTTOM (e, f, g, h)
			update_color(1);
			draw_face(_vert4, _vert5, _vert6, _vert7);

			//FRONT (a, d, h, e)
			update_color(2);
			draw_face(_vert0, _vert3, _vert7, _vert4);

			//BACK (b, c, f, g)
			update_color(3);
			draw_face(_vert1, _vert2, _vert6, _vert5);

			//LEFT (a, b, e, f)
			update_color(4);
			draw_face(_vert0, _vert1, _vert5, _vert4);

			//RIGHT (d, c, h, g)
			update_color(5);
			draw_face(_vert3, _vert2, _vert6, _vert7);

			update_color(6);
				draw_face(glm::vec4(bound_x_left, bound_y_bottom, 0.0f, 1.0f), glm::vec4(bound_x_left, bound_y_bottom, bound_z_far, 1.0f),
						glm::vec4(bound_x_left, bound_y_top, bound_z_far, 1.0f), glm::vec4(bound_x_left, bound_y_top, 0.0f, 1.0f));

				//RIGHT
				update_color(8);
				draw_face(glm::vec4(bound_x_right, bound_y_bottom, 0.0f, 1.0f), glm::vec4(bound_x_right, bound_y_bottom, bound_z_far, 1.0f),
						glm::vec4(bound_x_right, bound_y_top, bound_z_far, 1.0f), glm::vec4(bound_x_right, bound_y_top, 0.0f, 1.0f));

				//CEIL
				update_color(9);
				draw_face(glm::vec4(bound_x_left, bound_y_top, 0.0f, 1.0f), glm::vec4(bound_x_left, bound_y_top, bound_z_far, 1.0f),
						glm::vec4(bound_x_right, bound_y_top, bound_z_far, 1.0f), glm::vec4(bound_x_right, bound_y_top, 0.0f, 1.0f));

				//FLOOR
				update_color(7);
				draw_face(glm::vec4(bound_x_left, bound_y_bottom, 0.0f, 1.0f), glm::vec4(bound_x_left, bound_y_bottom, bound_z_far, 1.0f),
						glm::vec4(bound_x_right, bound_y_bottom, bound_z_far, 1.0f), glm::vec4(bound_x_right, bound_y_bottom, 0.0f, 1.0f));

		glEnd();

}

class Game {
	private:
		float delta, ts, _ts;
		GLdouble 	cam_x = 0.0, cam_y = 0.0, cam_z = 0.0,
					cam_focus_x = 0.0, cam_focus_y = 0.0, cam_focus_z = 0.0,
					cam_yaw = 0.0, cam_pitch = 1.0, cam_roll = 0.0;
		bool dragging = false;
		float m_x = 0, m_y = 0, _m_x, _m_y;
		float gravity = -9.81f;

		Entity* test = new Entity(0.5f, 0.0f, 0.0f, -7.0f, 0.0f, 0.0f, 0.0f);
		vector<GameObject*> object_list;

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
			for(auto &obj : object_list) {
			    obj -> update(delta);
			}
		}

		void display() {
			for(auto &obj : object_list) {
			    obj -> display(delta);
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
					case 'r': test->set_accel_y(gravity); break;
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
