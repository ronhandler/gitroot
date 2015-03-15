#pragma once

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
	// ostream operator << overloading.
	friend std::ostream& operator<< (std::ostream& os, const Point& obj)
	{
		return os << "(" << obj.x << ", " << obj.y << ")";
	}                 

protected:
	GLfloat x;
	GLfloat y;
};


class Shape
{
public:
	unsigned int getVertexCount(void) { return vertexArray.size(); }
	Point & operator()(const unsigned int i)
	{
		return vertexArray.at(i);
	}
protected:
	std::vector<Point> vertexArray;
};

class Rectangle : public Shape
{
public:
	Rectangle(Point p1, Point p2) : Shape()
	{
		vertexArray.push_back(p1);
		vertexArray.push_back(p2);
	}

};

class Object
{
public:
	void func()
	{
		std::cout << "Called func() !!" << std::endl;
	}
private:
};

