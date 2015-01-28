#ifndef ENTITY_HANDLER_H
#define ENTITY_HANDLER_H

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include <iostream>
#include <vector>

#include "shader_handler.h"
#include "path_handler.h"

class Entity {
protected:
	bool Initialized;
	double xpos;
	double ypos;
public:
	virtual ~Entity() { }
	virtual Entity* clone()=0;
	virtual void draw()=0;
	double getPosX() {return xpos;}
	double getPosY() {return ypos;}
	void setPos(double x, double y) { xpos = x; ypos = y; }
};

/* Reference based Singleton class. */
class EntityHandler {
public:
	static EntityHandler& getInstance() {
		static EntityHandler ins;
		return ins;
	}

	int addEntity(Entity *ent) {
		EntityVector.push_back( ent->clone() );
		return EntityVector.size()-1;
	}
	Entity *at(int i) {
		return EntityVector.at(i);
	}

	void drawAll() {
		for (unsigned int i=0; i<EntityVector.size(); ++i) {
			EntityVector.at(i)->draw();
		}
	}
protected:
private:
	std::vector<Entity *> EntityVector;
	EntityHandler() {
		// Construct the path for each of the resources.
		std::string res = PathHandler::getInstance().getResourcePath();
		std::string dvs, dfs, wvs, wfs;
		dvs = res + "/default.vsh";
		dfs = res + "/default.fsh";
		wvs = res + "/widepoint.vsh";
		wfs = res + "/widepoint.fsh";
		// Default shader to use.
		defaultShaderID = ShaderHandler::getInstance().loadShader(dvs.c_str(), dfs.c_str());
		// Load a shader for GL_POINTS.
		pointShaderID = ShaderHandler::getInstance().loadShader(wvs.c_str(), wfs.c_str());
	}
	EntityHandler(EntityHandler const &);
	EntityHandler& operator=(EntityHandler const &);
public:
	GLuint defaultShaderID;
	GLuint pointShaderID;
};

class Dot : public Entity {
protected:
public:
	Dot() { Entity::Initialized=false; }
	Dot(double x, double y)
	{
		Entity::setPos(x, y);
		Entity::Initialized = true;
	}
	~Dot() {}
	virtual void draw() {
		// Do not try to draw an uninitialized shape.
		if (Entity::Initialized == false) {
			return;
		}
		// Load the correct shader program.
		glUseProgram(EntityHandler::getInstance().pointShaderID);
		// draw the dot.
		//glPointSize(6.0);
		glBegin(GL_POINTS);		// Render the Dot.
			glVertex3f(Entity::xpos, Entity::ypos, 0.0);
		glEnd();

	}

	virtual Entity* clone() {
		Dot *c = new Dot();
		*c = *this;
		return c;
	}
};

#endif

