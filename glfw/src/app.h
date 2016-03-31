#pragma once

#include <iostream>
#include <cstring>
#include <sstream>

#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include "texture.h"

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
			cleanup();
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

			GLfloat vertices[] = {
				-1, -1, -1,   -1, -1,  1,   -1,  1,  1,   -1,  1, -1,
				1, -1, -1,    1, -1,  1,    1,  1,  1,    1,  1, -1,
				-1, -1, -1,   -1, -1,  1,    1, -1,  1,    1, -1, -1,
				-1,  1, -1,   -1,  1,  1,    1,  1,  1,    1,  1, -1,
				-1, -1, -1,   -1,  1, -1,    1,  1, -1,    1, -1, -1,
				-1, -1,  1,   -1,  1,  1,    1,  1,  1,    1, -1,  1
			};

			GLfloat colors[] = {
				0, 0, 0,   0, 0, 1,   0, 1, 1,   0, 1, 0,
				1, 0, 0,   1, 0, 1,   1, 1, 1,   1, 1, 0,
				0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,
				0, 1, 0,   0, 1, 1,   1, 1, 1,   1, 1, 0,
				0, 0, 0,   0, 1, 0,   1, 1, 0,   1, 0, 0,
				0, 0, 1,   0, 1, 1,   1, 1, 1,   1, 0, 1
			};

			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);

			glVertexPointer(3, GL_FLOAT, 0, vertices);
			glColorPointer(3, GL_FLOAT, 0, colors);

			while (!glfwWindowShouldClose(window)) {

				// Render here
				glClearColor (0.0f, 0.0f, 0.0f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				//glBindTexture(GL_TEXTURE_2D, tex.getId());
				glDrawArrays(GL_QUADS, 0, 24);

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

			glEnable(GL_TEXTURE_2D);

			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LEQUAL);
			glDisable(GL_CULL_FACE);
			glCullFace(GL_BACK);

			glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing

			initialized = true;
			return 0;
		}
		void cleanup() {
			glDisableClientState(GL_COLOR_ARRAY);
			glDisableClientState(GL_VERTEX_ARRAY);
			glfwTerminate();
		}
};

