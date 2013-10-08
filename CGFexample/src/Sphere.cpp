#include "../include/Sphere.h"

Sphere::Sphere( float radius, int slices, int stacks ){
	this->radius = radius;
	this->slices = slices;
	this->stacks = stacks;
}

Sphere::~Sphere(){
}

void Sphere::draw(){
	this->quadric = gluNewQuadric();
	gluSphere( this->quadric, this->radius, this->slices, this->stacks );
}