#include "App.h"

// Constructor.
App::App(void)
{
	done=false;
	Height=480;
	Width=640;
}

// Destructor.
App::~App(void)
{
	Cleanup();
}


void App::setWindowSize(int width, int height)
{
	Height=height; Width=width;
}

// Initialization functions.
void App::InitApp(void)
{
	int contextFlags;
	contextFlags = SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE;
	
	// Create a window.
	InitializeSDL(Width, Height, contextFlags);
	CreateOrthographicProjection(4.0, 3.0);
	InstallTimer();
	
}

void App::InitializeSDL(int width, int height, int flags)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	// Turn on double buffering.
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	// Save the height and width of the windows.
	Height=height;
	Width=width;

	// Create the window.
	mainWindow = SDL_CreateWindow("Proj", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
	mainGLContext = SDL_GL_CreateContext(mainWindow);


	if (glewInit() != GLEW_OK) exit(EXIT_FAILURE);

	
	// Print version numbers.
	fprintf(stdout,
			"Versions\n========\nglew:%s\ngl:%s\nvendor:%s\nrenderer:%s\nglsl:%s\n",
	        glewGetString(GLEW_VERSION),
	        glGetString(GL_VERSION),
	        glGetString(GL_VENDOR),
	        glGetString(GL_RENDERER),
	        glGetString(GL_SHADING_LANGUAGE_VERSION)
	        );

}

void App::CreateOrthographicProjection(GLfloat width, GLfloat height)
{
	// The projection function.
	glOrtho(0.0, width, 0.0, height, -1.0, 1.0);
}

void App::InstallTimer(void)
{
	timer = SDL_AddTimer(30, GameLoopTimer, this);
}

Uint32 App::GameLoopTimer(Uint32 interval, void* param)
{
	// Create a user event to call the game loop.
	SDL_Event event;
	
	event.type = SDL_USEREVENT;
	event.user.code = RUN_GAME_LOOP;
	event.user.data1 = 0;
	event.user.data2 = 0;
	
	SDL_PushEvent(&event);
	
	return interval;
}


// Cleanup functions.
void App::Cleanup(void)
{
	SDL_RemoveTimer(timer);
	
	SDL_GL_DeleteContext(mainGLContext);
	SDL_DestroyWindow(mainWindow);
	SDL_Quit();
}


// Event-related functions.
void App::EventLoop(void)
{
	SDL_Event event;
	
	while((!done) && (SDL_WaitEvent(&event))) {
		switch(event.type) {
			case SDL_USEREVENT:
				HandleUserEvents(&event);
				break;
			case SDL_KEYDOWN:
				switch( event.key.keysym.sym ){
					case SDLK_ESCAPE:
						// Quit when user presses the Escape key.
						done = true;
						break;
					default:
						// Other keys.
						break;
				}
				break;
			case SDL_QUIT:
				done = true;
				break;
			default:
				break;
		}
	}
}

void App::HandleUserEvents(SDL_Event* event)
{
	switch (event->user.code) {
		case RUN_GAME_LOOP:
			GameLoop();
			break;
		default:
			break;
	}
}


// Game related functions.
void App::GameLoop(void)
{
	RenderFrame();	  
}

void App::RenderFrame(void) 
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glRectf(1.0, 1.0, 3.0, 2.0);
	SDL_GL_SwapWindow(mainWindow);
}

