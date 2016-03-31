#pragma once

#include <GLFW/glfw3.h>

class Texture {
public:
	Texture(unsigned char *buff, unsigned int width, unsigned int height) {

		w = width;
		h = height;

		texid = 0;

		glGenTextures(1, &texid);
		glBindTexture(GL_TEXTURE_2D, texid);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, buff);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	~Texture() {
		glDeleteTextures(1, &texid);
	}

	int getId() { return texid; }
	int getWidth() { return w; }
	int getHeight() { return h; }
private:
	GLuint texid;
	int w;
	int h;
};

