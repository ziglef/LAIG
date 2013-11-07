#include "../include/Plane.h"
#include <GL/glut.h>

GLfloat ctrlpoints[4][3] = {	{  -0.5, 0.0, -0.5},
								{  0.5, 0.0, -0.5}, 
								{ -0.5, 0.0, 0.5},
								{ 0.5, 0.0, 0.5} };

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
	float counter1, counter2;

	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 2,  0.0, 1.0, 6, 2,  &ctrlpoints[0][0]);
	glMap2f(GL_MAP2_COLOR_4,  0.0, 1.0, 4, 2,  0.0, 1.0, 8, 2,  &colorpoints[0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2,  0.0, 1.0, 2, 2,  0.0, 1.0, 4, 2,  &textpoints[0][0]);

	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_MAP2_COLOR_4);
	glEnable(GL_MAP2_TEXTURE_COORD_2);

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);

	glMapGrid2f(this->parts, 0.0,1.0, this->parts, 0.0,1.0); 
	glEvalMesh2(GL_FILL, 0,this->parts, 0,this->parts);

	glColor3f(1.0, 1.0, 0.0);
	/*glBegin(GL_POINTS);
	for( counter1=-0.5; counter1 <= 0.5; counter1+=1.0/(float)parts){
		for( counter2=-0.5; counter2 <= 0.5; counter2+=1.0/(float)parts ){
				glVertex3f( counter1, 0.0, counter2 );
		} 
	}
	glEnd();*/

}