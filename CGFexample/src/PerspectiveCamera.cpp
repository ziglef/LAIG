#include "../include/PerspectiveCamera.h"

PerspectiveCamera::~PerspectiveCamera(){

}

std::string PerspectiveCamera::getType(){
	return "perspectivecamera";
}

std::string PerspectiveCamera::getID(){
	return this->id;
}

void PerspectiveCamera::applyView(){
	gluLookAt( position[0], position[1], position[2], target[0], target[1], target[2], 0.0, 1.0, 0.0 );
}

void PerspectiveCamera::updateProjectMatrix( int width, int height ){
	float aspect= (float)width / (float)height;
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( angle, aspect, near, far );	
}
