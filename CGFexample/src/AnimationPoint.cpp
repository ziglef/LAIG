#include "../include/AnimationPoint.h"

AnimationPoint::AnimationPoint( float x, float y, float z ){
	this->x = x;
	this->y = y;
	this->z = z;

	this->iterations = 0;
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
	this->maxIterations = (int)((duration*30) + 0.5 );
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

void AnimationPoint::setIterations( int iterations ){
	this->iterations = iterations;
}

int AnimationPoint::getIterations(){
	return this->iterations;
}

void AnimationPoint::setMaxIterations( int maxIterations ){
	this->maxIterations = maxIterations;
}

int AnimationPoint::getMaxIterations(){
	return this->maxIterations;
}