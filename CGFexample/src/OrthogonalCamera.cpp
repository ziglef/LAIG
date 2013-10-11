#include "../include/OrthogonalCamera.h"

OrthogonalCamera::~OrthogonalCamera(){

}

std::string OrthogonalCamera::getType(){
	return "orthogonalcamera";
}

std::string OrthogonalCamera::getID(){
	return this->id;
}

void OrthogonalCamera::applyView(){
		gluLookAt(0,0,20.0,0.0,0.0,0.0,0.0,0.0,0.0);

}

void OrthogonalCamera::updateProjectMatrix( int width, int height ){
	float aspect= (float)width / (float)height;
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( left, right, bottom, top, near, far );
}