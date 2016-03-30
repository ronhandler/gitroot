#pragma once

#include <iostream>
#include <cstring>
#include <sstream>

#include <GLFW/glfw3.h>

class App {
	public:

	private:
		bool initialized;
		GLFWwindow* window;

	public:
		App() {
			window = NULL;
			initialized = false;
		}
		~App() {
			glfwTerminate();
		}
		// Removing copy constructor and assignment operator.
		App(App const &) = delete;
		void operator=(App const &) = delete;
		// Get the instance of this singleton class.
		static App &getInstance() {
			static App instance;
			return instance;
		}

		void start() {
			if (initialized == false)
				init();

			glEnable(GL_TEXTURE_2D);

			unsigned char image[] =
			{
				0x00, 0x00, 0x00, 0xFF,
				0x00, 0xFF, 0x00, 0xFF,
				0xFF, 0x00, 0x00, 0xFF,
				0xFF, 0xFF, 0x00, 0xFF
			};
			int width=2;
			int height=2;
			GLuint tex;
			glGenTextures(1, &tex);
			glBindTexture(GL_TEXTURE_2D, tex);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			while (!glfwWindowShouldClose(window)) {
				/* Render here */
				glClearColor (0.0f, 0.0f, 0.0f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				glBindTexture(GL_TEXTURE_2D, tex);
				glBegin(GL_QUADS);
				{
					//glColor3f(1.0, 0.0, 0.0);
					glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.5f,  0.5f); 
					glTexCoord2f(1.0f, 0.0f); glVertex2f( 0.5f,  0.5f); 
					glTexCoord2f(1.0f, 1.0f); glVertex2f( 0.5f, -0.5f); 
					glTexCoord2f(0.0f, 1.0f); glVertex2f(-0.5f, -0.5f); 
				}
				glEnd();

				glfwSwapBuffers(window);
				glfwPollEvents();
			}
		}

	private:

		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (action == GLFW_PRESS) {
				switch (key) {
				case GLFW_KEY_Q:
				case GLFW_KEY_ESCAPE:
					glfwSetWindowShouldClose(window, true);
					break;
				}
			}
		}

		int init() {
			if (!glfwInit()) {
				return -1;
			}
			window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

			if (!window) {
				glfwTerminate();
				return -1;
			}
			glfwMakeContextCurrent(window);

			glfwSetKeyCallback(window, key_callback);

			initialized = true;
			return 0;
		}
};

