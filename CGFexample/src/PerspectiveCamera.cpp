#include "../include/PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera( char *id, float near, float far, float angle, char *pos, float posX, float posY, float posZ, char *target, float targetX, float targetY, float targetZ ){
	this->near = near;
	this->far = far;
	this->angle = angle;
	this->posX = posX;
	this->posY = posY;
	this->posZ = posZ;
	this->targetX = targetX;
	this->targetY = targetY;
	this->targetZ = targetZ;

	this->id = new string( id );
	this->pos = new string( pos );
	this->target = new string( target );
}

PerspectiveCamera::~PerspectiveCamera(){

}

std::string PerspectiveCamera::getType(){
	return "perspectivecamera";
}