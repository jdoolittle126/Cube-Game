#pragma once

class GameObject {
	public:
		virtual void update(float delta) = 0;
		virtual void display(float delta) = 0;
};
