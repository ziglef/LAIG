#include "../include/Rectangle.h"

Rectangle::Rectangle( float x1, float y1, float x2, float y2 ){
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
}

Rectangle::~Rectangle(){
}

void Rectangle::draw(){
	glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2d(0,0);
		glVertex3f(x1, y1, 0.0);
		glTexCoord2d(1,0);
		glVertex3f(x2, y1, 0.0);
		glTexCoord2d(1,1);
		glVertex3f(x2,y2, 0.0);
		glTexCoord2d(0,1);
		glVertex3f(x1,y2, 0.0);
	glEnd();
}