#include "../include/Triangle.h"

Triangle::Triangle( float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3 ){
	this->x1 = x1;
	this->y1 = y1;
	this->z1 = z1;
	this->x2 = x2;
	this->y2 = y2;
	this->z2 = z2;
	this->x3 = x3;
	this->y3 = y3;
	this->z3 = z3;
}

// Triangle Destructor
Triangle::~Triangle(){
}

void Triangle::draw(){
	glBegin( GL_TRIANGLES );
		glTexCoord2f(0, 0);
		glVertex3f( x1, y1, z1 );
		 glTexCoord2f(1, 0);
		glVertex3f( x2, y2, z2 );
		 glTexCoord2f(0, 1);
		glVertex3f( x3, y3, z3 );
	glEnd();
}