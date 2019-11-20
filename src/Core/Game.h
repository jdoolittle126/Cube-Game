#pragma once

#include "../Core/Dependancies/Libraries.h"
#include "../Managers/GameManager.h"
#include "../Map/WorldMap.h"
#include "../Rendering/Model.h"
#include "../Rendering/Camera.h"
#include "../Object/Entity.h"

int frame_aggragator = 0;
float delta_aggragator = 0;

class Game {
	//TODO Clean!
	private:
		GLfloat gravity = -9.81f; //TEMP

		bool dragging;

		GLdouble delta, ts, _ts,
				cam_x, cam_y, cam_z,
				cam_focus_x, cam_focus_y, cam_focus_z,
				cam_yaw, cam_pitch, cam_roll;

		GLfloat m_x, m_y, _m_x, _m_y;

		GLuint textureId; //RENAME

		GameManager manager;
		Camera * camera;
		WorldMap * map;
		Entity * test; //TEMP
		std::vector<GameObject*> object_list;

	public:

		Game(GameManager & i_manager){
			delta = ts = _ts = 0.0;
			cam_x = cam_y = cam_z = 0.0;
			cam_focus_x = cam_focus_y = cam_focus_z = cam_yaw = cam_roll = 0.0;
			cam_pitch = 1.0;
			dragging = false;
			m_x = m_y = _m_x =_m_y = 0.0f;
			camera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT);
			textureId = manager.getTextureManager()->test_load_texture("src\\Assets\\Road.bmp", true);
			map = new WorldMap(textureId);
			test = new Entity(1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, new Model("src\\Assets\\Models\\squid.obj", manager.getTextureManager()->test_load_texture("src\\Assets\\Models\\UV.bmp", false)));
			manager = i_manager;
			test->set_world_map(map);
			object_list.push_back(test);
		}
		~Game() {
			delete camera;
			delete map;
			delete test;
			while(!object_list.empty()) delete object_list.back(), object_list.pop_back();
		}


		bool running = true;

		void update_delta() {
			ts = glutGet(GLUT_ELAPSED_TIME);
			delta = (ts - _ts) / 1000.0f;
			_ts = ts;
			//TODO Optional!
			frame_aggragator++;
			delta_aggragator += delta;
			if (delta_aggragator >= 1.0f ) {
				printf("%f ms/frame\n", 1000.0/double(frame_aggragator));
				std::cout << "FPS: " << frame_aggragator << std::endl;
				frame_aggragator = 0;
				delta_aggragator -= 1.0f;
			}

		}

		void update() {
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable( GL_BLEND );
			update_delta();
			map->update(delta);
			for(auto &obj : object_list) {
			    obj->update(delta);
			}
		}

		void display() {
			camera->set_pos(test->get_pos_x(), test->get_pos_y()+(3.0f*test->get_scale_y()), test->get_pos_z()+(4.0f*test->get_scale_z()));
			camera->look_at(test->get_pos_x(), test->get_pos_y(), test->get_pos_z());

		    for (std::map<std::string, GLuint>::iterator i = manager.getShaderManager()->get_shaders().begin(); i != manager.getShaderManager()->get_shaders().end(); ++i) {
		    	glUseProgram(i->second);
				glUniformMatrix4fv(glGetUniformLocation(i->second, "mat_projection"), 1, GL_FALSE, &camera->projection[0][0]);
				glUniformMatrix4fv(glGetUniformLocation(i->second, "mat_view"), 1, GL_FALSE, &camera->view[0][0]);
		    }

			map->display(delta, manager);

			for(auto &obj : object_list) {
			    obj->display(delta, manager);
			}
		}

		void draw_hud() {

		}

		void create_intersection(int x, int y) {
			for(int i = 0; i <= 7; i++){
				for(int j = 0; j <= 7; j++){
					map->create_tile(i+x, -1.0f, -j+y, (i+2)%12, (j+2)%12);
				}
			}
		}

		void road_horz(int x, int y) {
			for(int i = 0; i <= 7; i++){
					map->create_tile(i+x, -1.0f, y, (i+2)%12, 1);
			}
		}

		void road_vert(int x, int y) {
			for(int i = 0; i <= 7; i++){
					map->create_tile(x, -1.0f, -i+y, 1, (i+2)%12);
			}
		}

		void build_map() {
			//80 x 274 w 13 units
			create_intersection(0, 0);
			road_horz(0, 1);
			road_vert(8, 0);


		}

		void keyboard(unsigned char key, int x, int y, bool up, int mod) {
			if(up) {
				switch(key){
					case '1': break;
					case '2': break;
					case 'a': test->set_vel_x(-3.0f); break;
					case 'd': test->set_vel_x(3.0f); break;
					case 's': test->set_vel_z(3.0f); break;
					case 'w': test->set_vel_z(-3.0f); break;
					case 'q': test->set_vel_yaw(5.0f); break;
					case 'e': test->set_vel_yaw(-5.0f); break;
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

};
