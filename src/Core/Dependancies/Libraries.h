#pragma once

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include "GameStrings.h"
#include "Errors.h"
#include "Constants.h"

#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>

#include <list>
#include <iterator>
#include <algorithm>
#include <vector>
#include <math.h>
#include <fstream>
#include <map>

#include <GL/glew.h>
#include <GL/freeglut.h>

#ifdef _WIN32
#include <windef.h>
#include <Windows.h>
#include <GL/wglew.h>
#endif

#include <cmath>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

struct cube_bound {
	float x1, x2, y1, y2, z1, z2;
};

enum RenderType {RENDER_CUBE, RENDER_MODEL};


void log_error(std::string error);
void log_error(std::string error, char log[ERROR_LOG_SIZE]);

GLuint build_texture(std::string path, GLenum type);


