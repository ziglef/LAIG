#include "../include/Patch.h"
#include <GL/glut.h>

GLfloat **cpMatrix = NULL;

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

	cpMatrix = (GLfloat **)realloc(cpMatrix, sizeof(GLfloat *) * ctrlPoints);
	for(int i=0; i<ctrlPoints; ++i){
		cpMatrix[i] = (GLfloat *)malloc(sizeof(GLfloat) * 3);
	}
 
	for(int i=0; i<ctrlPoints; ++i){
		for(int j=0; j<3; ++j){
			cpMatrix[i][j] = originalMatrix[i][j];
		}
}
}

void Patch::draw(){
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, partsU,  0.0, 1.0, partsU*2, partsV,  *cpMatrix);
	glMap2f(GL_MAP2_COLOR_4,  0.0, 1.0, 4, 2,  0.0, 1.0, 8, 2,  &patchColorpoints[0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2,  0.0, 1.0, 2, 2,  0.0, 1.0, 4, 2,  &patchTextpoints[0][0]);

	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_MAP2_COLOR_4);
	glEnable(GL_MAP2_TEXTURE_COORD_2);

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);

	glMapGrid2f(this->ctrlPoints, 0.0,1.0, this->ctrlPoints, 0.0,1.0); 
	if( strcmp( "fill", this->compute.c_str() ) == 0 )
		glEvalMesh2(GL_FILL, 0,partsU, 0,partsU);
	else
		if( strcmp( "line", this->compute.c_str() ) == 0 )
			glEvalMesh2(GL_LINE, 0,partsU, 0,partsU);
		else
			if( strcmp( "point", this->compute.c_str() ) == 0 )
				glEvalMesh2(GL_POINT, 0,partsU, 0,partsU);

	glColor3f(1.0, 1.0, 0.0);
}

Patch::~Patch(){

}