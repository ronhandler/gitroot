
#include "App.h"

int main(int argc, char *argv[])
{
	App gameInstance;
	gameInstance.setWindowSize(600, 600);
	gameInstance.InitApp();
	gameInstance.EventLoop();
	gameInstance.Cleanup();
	return 0;
}

