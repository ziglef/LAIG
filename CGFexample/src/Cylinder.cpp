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
	drawBase();
	gluCylinder( this->quadric, this->base, this->top, this->height, this->slices, this->stacks );
	drawTop();
}

void Cylinder::drawBase(){
	float _pi = acos(-1.0);
	float angle=2*_pi/this->slices;
	
	glPushMatrix();
	glBegin(GL_TRIANGLE_FAN);

	glNormal3f(0,1,0);
	
	glTexCoord2f(0.5,0.5);
	glVertex3f(0,0,0);

	for(int i=0;i<=this->slices;i++){

		glTexCoord2f(0.5+cos(angle*i)/2,0.5+sin(angle*i)/2);
		glVertex3f(sin(angle*i),0,cos(angle*i));
	}
	
	glEnd();
	glPopMatrix();
}

void Cylinder::drawTop(){
	glPushMatrix();
	glTranslatef(0,this->stacks,0);
	drawBase();
	glPopMatrix();
}