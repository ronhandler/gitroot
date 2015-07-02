#pragma once

#include <math.h>
#include <iostream>
#include <vector>
#include <GL/gl.h>


class Point
{
public:
	Point(): x(0.0), y(0.0) {}
	Point(GLfloat i, GLfloat j): x(i), y(j) {}
	void setX(GLfloat i) { x=i; }
	void setY(GLfloat i) { y=i; }
	void set(GLfloat i, GLfloat j) { x=i; y=j; }
	GLfloat getX(void) { return x; }
	GLfloat getY(void) { return y; }
	/* ostream operator << overloading. */
	friend std::ostream& operator<< (std::ostream& os, const Point& obj)
	{
		return os << "(" << obj.x << ", " << obj.y << ")";
	}                 

protected:
	GLfloat x;
	GLfloat y;
};

class Vector
{
public:
	Point start;
	Point end;
};

class Shape
{
public:
	unsigned int getVertexCount(void) { return vertexArray.size(); }
	void move(GLfloat xoffset, GLfloat yoffset)
	{
		for (unsigned int i=0; i<vertexArray.size(); ++i) {
			vertexArray.at(i).setX(vertexArray.at(i).getX() + xoffset);
			vertexArray.at(i).setY(vertexArray.at(i).getY() + yoffset);
		}
	}
	void speed(GLfloat xoffset, GLfloat yoffset)
	{
		movementVector.end.setX(movementVector.end.getX() + xoffset);
		movementVector.end.setY(movementVector.end.getY() + yoffset);
	}
	void updateLocation()
	{
		GLfloat xoffset, yoffset;
		xoffset = movementVector.start.getX() - movementVector.end.getX();
		yoffset = movementVector.start.getY() - movementVector.end.getY();
		move(xoffset, yoffset);
	}
	void frictionSlowdown()
	{
		double friction = 0.01;
		double directionX = (movementVector.start.getX() > movementVector.end.getX()) ? 1 : -1;
		double directionY = (movementVector.start.getY() > movementVector.end.getY()) ? 1 : -1;
		// Stabilize to a stand-still, if vector is too weak.
		/*
		 *if ((abs(movementVector.start.getX() - movementVector.end.getX())<=friction) && (abs(movementVector.start.getY() - movementVector.end.getY())<=friction)) {
		 *    movementVector.end.setX(movementVector.start.getX());
		 *    movementVector.end.setY(movementVector.start.getY());
		 *    return;
		 *}
		 */
		if (movementVector.start.getX() > movementVector.end.getX())
			directionX=directionX * -1;
		if (movementVector.start.getY() > movementVector.end.getY())
			directionY=directionY * -1;
		movementVector.end.setX(movementVector.start.getX()+ directionX*(movementVector.start.getX()-movementVector.end.getX())*(1-friction) );
		movementVector.end.setY(movementVector.start.getY()+ directionY*(movementVector.start.getY()-movementVector.end.getY())*(1-friction) );
	}

	Point & operator()(const unsigned int i)
	{
		return vertexArray.at(i);
	}
	Shape *clone() { return new Shape(*this); }
	void draw()
	{
		glBegin(GL_QUADS);
			glColor3f(1.f, 1.f, 1.f);
			for (unsigned int i=0; i<vertexArray.size(); ++i) {
				GLfloat x, y;
				x = vertexArray.at(i).getX();
				y = vertexArray.at(i).getY();
				glVertex3f(x, y, 0.0f);
			}
		glEnd();
	}
protected:
	Vector movementVector;
	std::vector<Point> vertexArray;
};

class Rectangle : public Shape
{
public:
	Rectangle(Point p1, Point p2, Point p3, Point p4) : Shape()
	{
		vertexArray.push_back(p1);
		vertexArray.push_back(p2);
		vertexArray.push_back(p3);
		vertexArray.push_back(p4);
		movementVector.start = p1;
		movementVector.end = p1;
	}
};

class Object
{
public:
	void draw()
	{
		for (unsigned int i=0; i<shapesArray.size(); ++i)
			shapesArray.at(i)->draw();;
	}
	void registerShape(Shape *s)
	{
		shapesArray.push_back(s->clone());
	}
	Object *clone() { return new Object(*this); }
	/* This is the copy constructor. We copy the vector elements one by one. */
	Object(const Object& other)
	{
		for (unsigned int i=0; i<other.shapesArray.size(); ++i) {
			shapesArray.push_back(other.shapesArray.at(i));
		}
	}
	void move(GLfloat xoffset, GLfloat yoffset)
	{
		for (unsigned int i=0; i<shapesArray.size(); ++i) {
			shapesArray.at(i)->move(xoffset, yoffset);
		}
	}
	void speed(GLfloat xoffset, GLfloat yoffset)
	{
		for (unsigned int i=0; i<shapesArray.size(); ++i) {
			shapesArray.at(i)->speed(xoffset, yoffset);
		}
	}
	void updateLocation()
	{
		for (unsigned int i=0; i<shapesArray.size(); ++i) {
			shapesArray.at(i)->updateLocation();
		}
	}
	void frictionSlowdown()
	{
		for (unsigned int i=0; i<shapesArray.size(); ++i) {
			shapesArray.at(i)->frictionSlowdown();
		}
	}
	Object() {}
	~Object()
	{
		for (unsigned int i=0; i<shapesArray.size(); ++i) {
			/* Not sure if this is needed, but just to be on the safe side.
			 * So basically, we are deleting the data the vector points to. */
			delete shapesArray.at(i);
		}
	}
protected:
	std::vector<Shape *> shapesArray;
};

