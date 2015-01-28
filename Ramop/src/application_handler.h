#ifndef APPLICATION_HANDLER_H 
#define APPLICATION_HANDLER_H 

#include <GL/glew.h>
#include <SDL2/SDL.h>
//#include <SDL/SDL_opengl.h>

#include "entity_handler.h"
#include "time_handler.h"

class ApplicationHandler {
private:
	bool upPressed;
	bool downPressed;
	bool leftPressed;
	bool rightPressed;
	double s;
protected:
	SDL_GLContext mainGLContext;
	SDL_Window* mainWindow;

public:
	const std::string APP_NAME() { return "Ramop"; }
	const std::string APP_VERSION() { return "0.1"; }
	double Width, Height;

	ApplicationHandler()
	{
		if (SDL_Init( SDL_INIT_EVERYTHING ) != 0) exit(EXIT_FAILURE);
		if (SDL_GL_LoadLibrary( NULL ) != 0) exit(EXIT_FAILURE);

		Width=300;
		Height=300;
		s=40.0;

		upPressed = false;
		downPressed = false;
		leftPressed = false;
		rightPressed = false;

		changeWindow(Width, Height);

		if (glewInit() != GLEW_OK) exit(EXIT_FAILURE);

		/*
		 * // Print version numbers.
		 *fprintf(stdout, "Versions\n========\nglew:%s\ngl:%s\nvendor:%s\nrenderer:%s\nglsl:%s\n",
		 *        glewGetString(GLEW_VERSION),
		 *        glGetString(GL_VERSION),
		 *        glGetString(GL_VENDOR),
		 *        glGetString(GL_RENDERER),
		 *        glGetString(GL_SHADING_LANGUAGE_VERSION)
		 *        );
		 */

		// Sets flags
		glEnable(GL_POINT_SMOOTH);
		//glEnable(GL_POINT_SPRITE);
		glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
		glClearColor(0.0, 0.0, 0.0, 1.0);

		// Initializes the delta timer.
		TimeHandler::getInstance().initTimer();

		// This temporarily creates two dots.
		EntityHandler::getInstance().addEntity( new Dot(150,50) );
		EntityHandler::getInstance().addEntity( new Dot(50,100) );
	}

	~ApplicationHandler()
	{
		ShaderHandler::getInstance().clearShaders();
		SDL_GL_DeleteContext(mainGLContext);
		SDL_DestroyWindow(mainWindow);
		SDL_Quit();
	}

	int changeWindow(int x, int y) {
		std::string Caption;
		Caption = APP_NAME() + " " + APP_VERSION();

		// Turn on double buffering.
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		
		Uint32 contextFlags;
		contextFlags = SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE;

		// Create the window
		mainWindow = SDL_CreateWindow(Caption.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, x, y, contextFlags);
		mainGLContext = SDL_GL_CreateContext(mainWindow);

		return 1;
	}

	int changeView() {
		// Set the viewport.
		glMatrixMode(GL_PROJECTION|GL_MODELVIEW);
		glLoadIdentity();
		glOrtho(0, Width, Height, 0, 0.0, 1.0);
		//glViewport(0, 0, 640, 480);
		return 1;
	}

	int logicLoop()
	{
		static int UorD;
		static int LorR;

		double tempx = EntityHandler::getInstance().at(0)->getPosX();
		double tempy = EntityHandler::getInstance().at(0)->getPosY();

		double temp1x = EntityHandler::getInstance().at(1)->getPosX();
		double temp1y = EntityHandler::getInstance().at(1)->getPosY();

		if (temp1x >= Width - s)
			LorR = 1;
		if (temp1x <= s)
			LorR = 0;
		if(!LorR)
			temp1x = temp1x + 0.1 * TimeHandler::getInstance().getDelta();
		if(LorR)
			temp1x = temp1x - 0.1 * TimeHandler::getInstance().getDelta();

		if (temp1y >= Height - s)
			UorD = 1;
		if (temp1y <= s)
			UorD = 0;
		if(!UorD)
			temp1y = temp1y + 0.12 * TimeHandler::getInstance().getDelta();
		if(UorD)
			temp1y = temp1y - 0.1 * TimeHandler::getInstance().getDelta();


		if (downPressed==true) {
			tempy = tempy + 0.1 * TimeHandler::getInstance().getDelta();
			if (tempy >= Height-s)
				tempy = s;
		}
		if (upPressed==true) {
			tempy = tempy - 0.1 * TimeHandler::getInstance().getDelta();
			if (tempy <= s)
				tempy = Height - s;
		}
		if (leftPressed==true) {
			tempx = tempx - 0.1 * TimeHandler::getInstance().getDelta();
			if (tempx <= s)
				tempx = Width - s;
		}
		if (rightPressed==true) {
			tempx = tempx + 0.1 * TimeHandler::getInstance().getDelta();
			if (tempx >= Width - s)
				tempx = s;
		}

		EntityHandler::getInstance().at(1)->setPos(temp1x, temp1y);
		EntityHandler::getInstance().at(0)->setPos(tempx, tempy);

		return 1;
	}

	int drawLoop()
	{
		// Set viewport.
		changeView();

		// Clear the screen.
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw a frame.
		glUseProgram(EntityHandler::getInstance().defaultShaderID);
		glBegin(GL_LINE_STRIP);
			glColor3f(1.0, 1.0, 1.0);
			glVertex3f(s, s, 0.0);
			glVertex3f(s, Width-s, 0.0);
			glVertex3f(Height-s, Width-s, 0.0);
			glVertex3f(Height-s, s, 0.0);
			glVertex3f(s, s, 0.0);
		glEnd();

		// Draw all entities.
		EntityHandler::getInstance().drawAll();

		// Swap the window/buffer to display the result.
        //SDL_GL_SwapBuffers();
		SDL_GL_SwapWindow(mainWindow);

		return 1;
	}

	int keyEventLoop()
	{
		SDL_Event event; 

        /* Poll for events */
        while( SDL_PollEvent( &event ) ){

            switch( event.type ){
                /* Keyboard event */
                /* Pass the event data onto PrintKeyInfo() */
                case SDL_KEYDOWN:
                    /* Check the SDLKey values and move change the coords */
                    switch( event.key.keysym.sym ){
						case SDLK_ESCAPE:
							return 0;
							break;
                        case SDLK_LEFT:
                        	leftPressed=true;
                            break;
                        case SDLK_RIGHT:
                        	rightPressed=true;
                            break;
                        case SDLK_UP:
                        	upPressed=true;
                            break;
                        case SDLK_DOWN:
                        	downPressed=true;
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch( event.key.keysym.sym ){
                        case SDLK_LEFT:
                        	leftPressed=false;
                            break;
                        case SDLK_RIGHT:
                        	rightPressed=false;
                            break;
                        case SDLK_UP:
                        	upPressed=false;
                            break;
                        case SDLK_DOWN:
                        	downPressed=false;
                            break;
                        default:
                            break;
                    }
                    break;
                /* SDL_QUIT event (window close) */
                case SDL_QUIT:
                    return 0;
                    break;

                default:
                    break;
            }

        }
		return 1;
	}

	int mainLoop() {

		// Main loop.
		while(1) {

			// Handler key events.
			if (0 == keyEventLoop())
				break;

			// Calculate the delta between two iterations.
			TimeHandler::getInstance().calcDelta();

			// Logic loop.
			logicLoop();

			// This is a temporary idle function. Needed to reduce cpu load.
			if (TimeHandler::getInstance().getDelta() < 10.0)
				SDL_Delay(10.0 - TimeHandler::getInstance().getDelta() );

			// Draw loop.
			drawLoop();
		} 
		return 1;
	}

private:
	GLuint shaderProgramID;
};

#endif

