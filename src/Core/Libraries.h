#pragma once

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

