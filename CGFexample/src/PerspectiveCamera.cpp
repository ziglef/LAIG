#include "../include/PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera( char *id, float near, float far, float angle, char *pos, float posX, float posY, float posZ, char *target, float targetX, float targetY, float targetZ ):Camera(id,near,far)
{
	this->angle = angle;
	this->posX = posX;
	this->posY = posY;
	this->posZ = posZ;
	this->targetX = targetX;
	this->targetY = targetY;
	this->targetZ = targetZ;
}

PerspectiveCamera::~PerspectiveCamera(){

}

std::string PerspectiveCamera::getType(){
	return "perspectivecamera";
}

std::string PerspectiveCamera::getID(){
	return this->id;
}