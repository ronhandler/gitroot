#ifndef APP_H
#define APP_H

#include <iostream>
#include <GL/glew.h>
#include <SDL.h>

class App
{
	protected:
		int Height, Width;
		SDL_Window* mainWindow;
		SDL_GLContext mainGLContext;
		SDL_TimerID timer;
		bool done;
	
	public:
		// Constructor and destructor.
		App(void);
		virtual ~App(void);

		void setWindowSize(int width, int height);
		// Initialization functions.
		void InitApp(void);
		void InitializeSDL(int width, int height, int flags);
		void CreateOrthographicProjection(GLfloat width, GLfloat height);
		void InstallTimer(void);
		static Uint32 GameLoopTimer(Uint32 interval, void* param);
		
		// Cleanup functions.
		void Cleanup(void);
		
		// Event-related functions.
		void EventLoop(void);
		void HandleUserEvents(SDL_Event* event);
		
		// Game related functions.
		void GameLoop(void);
		void RenderFrame(void);
		
};

typedef App* AppPtr;
typedef App** AppHandle;

const int RUN_GAME_LOOP = 1;

#endif

