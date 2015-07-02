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
	eng.registerGameloop( [newobj](void) {
		//double delta = GraphicsEngine::getInst().getDelta();
		newobj->updateLocation();
		newobj->frictionSlowdown();
	});

	static float offset = 0.5;
	eng.registerKey('W', [newobj](void) {
		std::cerr << "Up\n"; 
		newobj->speed(0, -offset*GraphicsEngine::getInst().getDelta());
	});
	eng.registerKey('A', [newobj](void) {
		std::cerr << "Left\n"; 
		newobj->speed(offset*GraphicsEngine::getInst().getDelta(), 0);
	});
	eng.registerKey('S', [newobj](void) {
		std::cerr << "Down\n"; 
		newobj->speed(0, offset*GraphicsEngine::getInst().getDelta());
	});
	eng.registerKey('D', [newobj](void) {
		std::cerr << "Right\n"; 
		newobj->speed(-offset*GraphicsEngine::getInst().getDelta(), 0);
	});

	eng.start();

	return 0;
}

