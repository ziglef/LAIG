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
	glRectf( this->x1, this->y1, this->x2, this->y2 );
}