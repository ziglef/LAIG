#include "../include/Patch.h"
#include <GL/glut.h>

GLfloat *cpMatrix = NULL;

GLfloat patchColorpoints[4][4] = {	{ 0.0, 0.7, 0.7, 0},
								{ 0.0, 0.0, 0.7, 0}, 
								{ 0.0, 0.7, 0.0, 0},
								{ 0.7, 0.0, 0.0, 0} };

GLfloat patchTextpoints[4][2] = {	{ 0.0, 0.0},
								{ 0.0, 1.0}, 
								{ 1.0, 0.0},
								{ 1.0, 1.0} };


Patch::Patch( int order, int partsU, int partsV, string compute, int ctrlPoints, GLfloat **originalMatrix ){
	this->order = order;
	this->partsU = partsU;
	this->partsV = partsV;
	this->compute = compute;
	this->ctrlPoints = ctrlPoints;

	cpMatrix = (GLfloat*)malloc(ctrlPoints*sizeof(GLfloat)*3);
 
	for(int i=0; i<ctrlPoints; ++i){
		cpMatrix[3*i+0] = originalMatrix[i][0];
		cpMatrix[3*i+1] = originalMatrix[i][1];
		cpMatrix[3*i+2] = originalMatrix[i][2];
	}
}

void Patch::draw(){
	
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_NORMAL);
	glEnable(GL_MAP2_TEXTURE_COORD_2);
	glEnable(GL_TEXTURE_2D);
	
	GLint currentCullFace;
	glGetIntegerv( GL_CULL_FACE_MODE, &currentCullFace );

	glEnable(GL_CCW);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, this->order,  0.0, 1.0, this->order*3, this->order, cpMatrix);
	glEnable(GL_CW);
	glEnable(GL_AUTO_NORMAL);
	glMap2f(GL_MAP2_TEXTURE_COORD_2,  0.0, 1.0, 2, 2,  0.0, 1.0, 4, 2,  &patchTextpoints[0][0]);

	glMapGrid2f(this->partsU, 0.0,1.0, this->partsV, 0.0,1.0); 
	if( strcmp( "fill", this->compute.c_str() ) == 0 )
		glEvalMesh2(GL_FILL, 0,partsU, 0,partsV);
	else
		if( strcmp( "line", this->compute.c_str() ) == 0 )
			glEvalMesh2(GL_LINE, 0,partsU, 0,partsV);
		else
			if( strcmp( "point", this->compute.c_str() ) == 0 )
				glEvalMesh2(GL_POINT, 0,partsU, 0,partsV);

	glEnable(currentCullFace);
	
	glDisable(GL_MAP2_VERTEX_3);
	glDisable(GL_MAP2_NORMAL);
	glDisable(GL_MAP2_TEXTURE_COORD_2);
	glDisable(GL_TEXTURE_2D);
}

Patch::~Patch(){
}