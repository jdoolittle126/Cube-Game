#include <list>

class Entity {

	public:
		long id;
		void init();
		void update(float delta);
		void display(float delta);

	Entity(){
		init();
	}

	Entity(long id){
		id = id;
		init();
	}

};
