#include "../include/OrthogonalCamera.h"

OrthogonalCamera::OrthogonalCamera( char *id, float near, float far, float left, float right, float up, float bottom ){
	this->near = near;
	this->far = far;
	this->left = left;
	this->right = right;
	this->top = top;
	this->bottom = bottom;
	
	this->id = new string( id );
}

OrthogonalCamera::~OrthogonalCamera(){

}

std::string OrthogonalCamera::getType(){
	return "orthogonalcamera";
}