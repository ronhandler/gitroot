#include "application_handler.h"
#include "path_handler.h"
#include <iostream>

int main(int argc, char* argv[])
{
	// This gets the executable path.
	PathHandler::getInstance().Init(argc, argv);
	// Create the application.
	ApplicationHandler app;
	// Run application's main loop.
	app.mainLoop();
	return 0;
}

