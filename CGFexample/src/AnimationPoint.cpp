#include "../include/AnimationPoint.h"

AnimationPoint::AnimationPoint( float x, float y, float z ){
	this->x = x;
	this->x = y;
	this->x = z;
}

AnimationPoint::~AnimationPoint(){

}

void AnimationPoint::setDistance( float distance ){
	this->distance = distance;
}

float AnimationPoint::getDistance(){
	return this->distance;
}

void AnimationPoint::setDuration( float duration ){
	this->duration = duration;
}

float AnimationPoint::getDuration(){
	return this->duration;
}

float AnimationPoint::getX(){
	return this->x;
}

float AnimationPoint::getY(){
	return this->y;
}

float AnimationPoint::getZ(){
	return this->z;
}