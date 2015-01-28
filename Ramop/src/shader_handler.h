#ifndef SHADER_HANDLER_H
#define SHADER_HANDLER_H

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include <stdio.h>
#include <vector>

/* Reference based Singleton class. */
class ShaderHandler {
public:
	static ShaderHandler& getInstance() {
		static ShaderHandler ins;
		return ins;
	}

	static char *readFile(const char *filename) {
		FILE *fp = fopen (filename, "r");
		if (fp == NULL)
			printf("Error loading file %s.\n", filename);

		fseek(fp, 0, SEEK_END);
		long file_length = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		char *contents = new char[file_length+1];
		for (int i=0; i<file_length+1; ++i)
			contents[i]=0;
		fread(contents, 1, file_length, fp);
		contents[file_length+1] = '\0';
		fclose(fp);
		//printf("Script:\n%s\n", contents);
		return contents;
	}
	GLuint makeVertexShader(char *shaderSource) {
		GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderID, 1, (const GLchar **) &shaderSource, NULL);
		glCompileShader(vertexShaderID);
		return vertexShaderID;
	}
	GLuint makeFragmentShader(char *shaderSource) {
		GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderID, 1, (const GLchar **) &shaderSource, NULL);
		glCompileShader(fragmentShaderID);
		return fragmentShaderID;
	}
	GLuint makeShaderProgram(GLuint vsID, GLuint fsID) {
		GLuint shaderID = glCreateProgram();
		glAttachShader(shaderID, vsID);
		glAttachShader(shaderID, fsID);
		glLinkProgram(shaderID);
		return shaderID;
	}

	// This function uses the helper functions to read vertex shader and
	// fragment shader from files, create a shader out of them, and lastly
	// return the program ID of the program compiled with these shaders.
	GLuint loadShader(const char *vertexShaderFilename, const char *fragmentShaderFilename) {
		char *vShaderSource = readFile(vertexShaderFilename);
		char *fShaderSource = readFile(fragmentShaderFilename);
		GLuint vShaderID = makeVertexShader(vShaderSource);
		GLuint fShaderID = makeFragmentShader(fShaderSource);
		GLuint shaderProgramID = makeShaderProgram(vShaderID, fShaderID);

		// Free memory used for holding the content of the files.
		delete vShaderSource;
		delete fShaderSource;

		shaderVector.push_back( shaderProgramID );

		return shaderProgramID;
	}

	void clearShaders() {
		for (unsigned int i=0; i<shaderVector.size(); ++i) {
			glDeleteProgram( shaderVector.at(i) );
		}
	}

protected:
private:
	std::vector<GLuint> shaderVector;
	ShaderHandler() { /* TODO: Add some code... */ }
	ShaderHandler(ShaderHandler const &);
	ShaderHandler& operator=(ShaderHandler const &);
};

#endif

