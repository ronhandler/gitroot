#include "main.h"

int main(void)
{
	std::cout << "hello world" << std::endl;

	Rectangle rect(Point(-1,-1), Point(1,1));
	std::cout << "The rectangle's number of Points is: " <<
		rect.getVertexCount() << std::endl;
	for (unsigned int i=0; i<rect.getVertexCount(); ++i) {
		std::cout << "Point " << i << " is: " << rect(i) << std::endl;
	}

	GraphicsEngine &eng = GraphicsEngine::getInst();
	eng.registerKey('W', [](void) { std::cerr << "Up\n"; });
	eng.registerKey('A', [](void) { std::cerr << "Left\n"; });
	eng.registerKey('S', [](void) { std::cerr << "Down\n"; });
	eng.registerKey('D', [](void) { std::cerr << "Right\n"; });
	eng.start();

	return 0;
}

