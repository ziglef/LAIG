#include "../include/OrthogonalCamera.h"

OrthogonalCamera::OrthogonalCamera( char *id, float near, float far, float left, float right, float up, float bottom ):Camera(id,near,far)
{
	this->left = left;
	this->right = right;
	this->top = top;
	this->bottom = bottom;
}

OrthogonalCamera::~OrthogonalCamera(){

}

std::string OrthogonalCamera::getType(){
	return "orthogonalcamera";
}

std::string OrthogonalCamera::getID(){
	return this->id;
}