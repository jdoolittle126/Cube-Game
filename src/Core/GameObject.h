#pragma once
#include "Libraries.h"

class GameObject {
	public:
		virtual void update(float delta, GLuint programID) = 0;
		virtual void display(float delta, GLuint programID) = 0;
};
