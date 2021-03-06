#include "../include/Cylinder.h"

Cylinder::Cylinder( float base, float top, float height, int slices, int stacks ){
	this->base = base;
	this->top = top;
	this->height = height;
	this->slices = slices;
	this->stacks = stacks;
}

Cylinder::~Cylinder(){
}

void Cylinder::draw(){
	this->quadric = gluNewQuadric();
	gluQuadricNormals( quadric, GLU_SMOOTH );
	gluQuadricTexture( quadric, GL_TRUE );
	gluCylinder( this->quadric, this->base, this->top, this->height, this->slices, this->stacks );
	gluDisk( this->quadric, 0, this->base,this->slices, 1 );
	glPushMatrix();
		glTranslatef(0,0,this->height);
		gluDisk( this->quadric, 0, this->base,this->slices, 1 );
	glPopMatrix();
}  
