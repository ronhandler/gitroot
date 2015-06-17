#pragma once

#include <iostream>
#include <functional>
#include <map>
#include <GLFW/glfw3.h>

#include "object.h"

class GraphicsEngine /* Singleton. */
{

public:

	/* public member functions. */
	/* ************************ */

	static GraphicsEngine & getInst() {
		static GraphicsEngine instance;
		return instance;
	}

	int registerRenderer(std::function<void()> func) {
		rendererFunc = func;
		return 0;
	}
	int registerGameloop(std::function<void()> func) {
		gameloopFunc = func;
		return 0;
	}
	int registerKey(int key, std::function<void()> func) {
		mapKeyFunction[key] = func;
		return 0;
	}

	int start()
	{
		if (!glfwInit())
			return 1;
		window = glfwCreateWindow(
			width, height,
			"Simple example",
			NULL, NULL);
		if (!window) {
			glfwTerminate();
			return 1;
		}
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);
		glfwSetKeyCallback(window, key_callback);

		while (!glfwWindowShouldClose(window)) {
			int w, h;
			glfwGetFramebufferSize(window, &w, &h);
			glViewport(0, 0, width, height);
			glClear(GL_COLOR_BUFFER_BIT);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-width/height, width/height, -1, 1, 1, -1);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			gameloopFunc();
			rendererFunc();

			/*
			 *glBegin(GL_QUADS);
			 *    glColor3f(1.f, 1.f, 1.f);
			 *    glVertex3f(-.5f, -.5f, 0.f);
			 *    glVertex3f(.5f, -.5f, 0.f);
			 *    glVertex3f(.5f, .5f, 0.f);
			 *    glVertex3f(-.5f, .5f, 0.f);
			 *glEnd();
			 */

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		return 0;
	}

	~GraphicsEngine()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

private:

	/* Private member variables. */
	/* ************************* */

	constexpr static const float width=640;
	constexpr static const float height=480;

	GLFWwindow* window;
	std::map< int, std::function<void()> > mapKeyFunction;
	std::function<void()> rendererFunc;
	std::function<void()> gameloopFunc;

	/* Private member functions. */
	/* ************************* */

	// Key handler.
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		// Go over all the registered key-function pairs in the map, and
		// execute their function if the keys match.
		if (action == GLFW_PRESS) {
			for(auto it = getInst().mapKeyFunction.begin(); it!=getInst().mapKeyFunction.end(); it++) {
				if (key == it->first) {
					it->second();
					return;
				}
			}
		}
		// Default actions.
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
	}

protected:

	/* Protected member functions. */
	/* *************************** */

   GraphicsEngine() {}
   GraphicsEngine(const GraphicsEngine &) = delete;
   GraphicsEngine& operator=(const GraphicsEngine &) = delete;
};

