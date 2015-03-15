#include "main.h"

int main(void)
{
	std::cout << "hello world" << std::endl;


	Object *newobj = new Object();
	newobj->registerShape(new Rectangle(
				Point(-0.25,-0.25),
				Point(0.25,-0.25),
				Point(0.25,0.25),
				Point(-0.25,0.25)));

	GraphicsEngine &eng = GraphicsEngine::getInst();

	/* This is a renderer function. */
	eng.registerRenderer( [newobj](void) {
		newobj->draw();
	});

	static float offset = 0.025;
	eng.registerKey('W', [newobj](void) {
		std::cerr << "Up\n"; 
		newobj->move(0, offset);
	});
	eng.registerKey('A', [newobj](void) {
		std::cerr << "Left\n"; 
		newobj->move(-offset, 0);
	});
	eng.registerKey('S', [newobj](void) {
		std::cerr << "Down\n"; 
		newobj->move(0, -offset);
	});
	eng.registerKey('D', [newobj](void) {
		std::cerr << "Right\n"; 
		newobj->move(offset, 0);
	});

	eng.start();

	return 0;
}

