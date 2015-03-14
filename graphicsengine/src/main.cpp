#include "main.h"

int main(void)
{
	std::cout << "hello world" << std::endl;
	GraphicsEngine &eng = GraphicsEngine::getInst();
	eng.registerKey('W', [](void) { std::cerr << "Up\n"; });
	eng.registerKey('A', [](void) { std::cerr << "Left\n"; });
	eng.registerKey('S', [](void) { std::cerr << "Down\n"; });
	eng.registerKey('D', [](void) { std::cerr << "Right\n"; });

	eng.start();

	return 0;
}

