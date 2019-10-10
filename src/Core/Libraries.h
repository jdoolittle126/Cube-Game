#pragma once

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>
#include <windef.h>

#include <list>
#include <iterator>
#include <algorithm>
#include <vector>
#include <math.h>
#include <fstream>

#include <Windows.h>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/freeglut.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>




#define PI 3.14159265

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

