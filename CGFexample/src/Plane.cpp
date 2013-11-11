#include "../include/Plane.h"
#include <GL/glut.h>

GLfloat ctrlpoints[4][3] = {	{  -0.5, 0.0, -0.5},
								{  0.5, 0.0, -0.5}, 
								{ -0.5, 0.0, 0.5},
								{ 0.5, 0.0, 0.5}};

GLfloat nrmlcompon[4][3] = {	{  0.0, 0.0, 1.0},
								{  0.0, 0.0, 1.0}, 
								{  0.0, 0.0, 1.0},
								{  0.0, 0.0, 1.0} };

GLfloat colorpoints[4][4] = {	{ 0.0, 0.7, 0.7, 0},
								{ 0.0, 0.0, 0.7, 0}, 
								{ 0.0, 0.7, 0.0, 0},
								{ 0.7, 0.0, 0.0, 0} };

GLfloat textpoints[4][2] = {	{ 0.0, 0.0},
								{ 0.0, 1.0}, 
								{ 1.0, 0.0},
								{ 1.0, 1.0} };

Plane::Plane( int parts ){
	this->parts = parts;
}

Plane::~Plane(){

}

void Plane::draw(){

	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_NORMAL);
	glEnable(GL_MAP2_TEXTURE_COORD_2);
	glEnable(GL_TEXTURE_2D);
	GLint currentCullFace;
	glGetIntegerv( GL_CULL_FACE_MODE, &currentCullFace );

	glEnable(GL_CCW);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 2,  0.0, 1.0, 6, 2,  &ctrlpoints[0][0]);
	glEnable(GL_CW);
	glEnable(GL_AUTO_NORMAL);
	glMap2f(GL_MAP2_TEXTURE_COORD_2,  0.0, 1.0, 2, 2,  0.0, 1.0, 4, 2,  &textpoints[0][0]);

	glMapGrid2f(this->parts, 0.0,1.0, this->parts, 0.0,1.0); 
	glEvalMesh2(GL_FILL, 0,this->parts, 0,this->parts);

	glEnable(currentCullFace);
	glDisable(GL_MAP2_VERTEX_3);
	glDisable(GL_MAP2_NORMAL);
	glDisable(GL_MAP2_TEXTURE_COORD_2);
}