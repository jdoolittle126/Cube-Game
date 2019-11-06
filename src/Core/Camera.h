///////////////////////////////////
//////////// INCLUDES /////////////
///////////////////////////////////

#include "Libraries.h"

///////////////////////////////////
//////////// CLASS ////////////////
///////////////////////////////////

class Camera {

	private:
		glm::vec3 cam_pos, cam_look, cam_head;

		void update_view() {
			view = glm::lookAt(cam_pos, cam_look, cam_head);
		}

		void init(float width, float height) {
			projection = glm::perspective(glm::radians(45.0f),
					float(width) / float(height), 0.1f, 100.0f);
			cam_pos = glm::vec3(0, 0, 1);
			cam_look = glm::vec3(0, 0, 0);
			cam_head = glm::vec3(0, 1, 0);
			update_view();
		}

	public:
		glm::mat4 projection;
		glm::mat4 view;

		Camera(float width, float height) {
			init(width, height);
		}
		Camera(int width, int height) {
			init(width, height);
		}

		void reshape(float width, float height) {
			projection = glm::perspective(glm::radians(45.0f),
					(float) width / (float) height, 0.1f, 100.0f);
		}

		void set_pos(float x, float y, float z) {
			cam_pos = glm::vec3(x, y, z);
			update_view();
		}
		void set_pos(glm::vec3 pos) {
			cam_pos = pos;
			update_view();
		}
		void translate(float x, float y, float z) {
			cam_pos = cam_pos + glm::vec3(x, y, z);
			update_view();
		}
		void translate(glm::vec3 move) {
			cam_pos = cam_pos + move;
			update_view();
		}
		void look_at(float x, float y, float z) {
			cam_look = glm::vec3(x, y, z);
			update_view();
		}
		void look_at(glm::vec3 target) {
			cam_look = target;
			update_view();
		}

};
