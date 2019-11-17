#pragma once

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>
//#include <windef.h>

#include <list>
#include <iterator>
#include <algorithm>
#include <vector>
#include <math.h>
#include <fstream>
#include <map>

//#include <Windows.h>
#include <GL/glew.h>
//#include <GL/wglew.h>
#include <GL/freeglut.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "../Utils/cute_png.h"


#define PI 3.14159265
#define DEFAULT_CUBE_SIZE 0.5

const int	WINDOW_WIDTH = 640,
			WINDOW_HEIGHT = 480;

struct cube_bound {
	float 	x1, x2,
			y1, y2,
			z1, z2;
};

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

enum RenderType {RENDER_CUBE, RENDER_MODEL};

GLuint build_texture(std::string path, GLenum type);

