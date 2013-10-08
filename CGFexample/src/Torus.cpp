#include "../include/Torus.h"

Torus::Torus( float inner, float outer, int slices, int loops ){
	this->inner = inner;
	this->outer = outer;
	this->slices = slices;
	this->loops = loops;
}

Torus::~Torus(){
}

void Torus::draw(){
	glutSolidTorus( this->inner, this->outer, this->slices, this->loops );
	//glutWireTorus( this->inner, this->outer, this->slices, this->loops );
}