#include "../include/LinearAnimation.h"
#include <GL/glut.h>

LinearAnimation::LinearAnimation(  char *id, int animationCp, float **originalMatrix, float totalDuration ){

	float totalDistance=0.0;
	float pointsDistance, pointDuration;
	this->id = id;

	for(int i=0; i<animationCp; i++){
		AnimationPoint *point;
		point = new AnimationPoint( originalMatrix[i][0], originalMatrix[i][1], originalMatrix[i][2] );
		ctrlPoints.push_back( point );
	}

	for(int i=1; i<animationCp; i++ ){
		pointsDistance = sqrt( pow(( ctrlPoints.at(i)->getX()-ctrlPoints.at(i-1)->getX() ), 2 ) + pow(( ctrlPoints.at(i)->getY()-ctrlPoints.at(i-1)->getY() ), 2 ) + pow(( ctrlPoints.at(i)->getZ()-ctrlPoints.at(i-1)->getZ() ), 2) );
		totalDistance += pointsDistance;
		ctrlPoints.at(i-1)->setDistance( pointsDistance );
	}

	ctrlPoints.at( ctrlPoints.size()-1 )->setDistance(0);

	for(int i=0; i<animationCp; ++i ){
		pointDuration = (totalDuration * ctrlPoints.at(i)->getDistance())/totalDistance;
		ctrlPoints.at(i)->setDuration(pointDuration);
	}

	this->x = ctrlPoints.at(0)->getX();
	this->y = ctrlPoints.at(0)->getY();
	this->z = ctrlPoints.at(0)->getZ();

	this->pointNumber=0;
	this->rotationAngle=0;
}

LinearAnimation::~LinearAnimation(){

}

void LinearAnimation::init( unsigned long t ){
	startTime=t;
	doReset=false;
}

void LinearAnimation::reset(){
	doReset=true;
}

void LinearAnimation::update( unsigned long t ){/*
	printf("this->pointNumber: %d\n", this->pointNumber);
	printf("this->ctrlPoints.size(): %d\n", this->ctrlPoints.size());*/
	if (doReset){
		init(t);
	}else{
		if( this->pointNumber < (this->ctrlPoints.size()-1) ){

			if( ctrlPoints.at(this->pointNumber)->getIterations() == 0 ){
				this->rotationAngle = acos( ( ctrlPoints.at(this->pointNumber+1)->getZ()-ctrlPoints.at(this->pointNumber)->getZ() ) / ( sqrt( pow( ctrlPoints.at(this->pointNumber+1)->getX()-ctrlPoints.at(this->pointNumber)->getX(),2 ) + pow( ctrlPoints.at(this->pointNumber+1)->getY()-ctrlPoints.at(this->pointNumber)->getY(),2 ) + pow( ctrlPoints.at(this->pointNumber+1)->getZ()-ctrlPoints.at(this->pointNumber)->getZ(),2 ) ) ) );
				this->rotationAngle = this->rotationAngle*(180.0/3.141592653589793);
			}

			this->x += ( ctrlPoints.at(this->pointNumber+1)->getX() -  ctrlPoints.at(this->pointNumber)->getX() )/( ctrlPoints.at(this->pointNumber)->getDuration() * 30 );
			this->y += ( ctrlPoints.at(this->pointNumber+1)->getY() -  ctrlPoints.at(this->pointNumber)->getY() )/( ctrlPoints.at(this->pointNumber)->getDuration() * 30 );
			this->z += ( ctrlPoints.at(this->pointNumber+1)->getZ() -  ctrlPoints.at(this->pointNumber)->getZ() )/( ctrlPoints.at(this->pointNumber)->getDuration() * 30 );

			ctrlPoints.at(this->pointNumber)->setIterations(ctrlPoints.at(this->pointNumber)->getIterations()+1);
			if( ctrlPoints.at(this->pointNumber)->getIterations() == ctrlPoints.at(this->pointNumber)->getMaxIterations() )
				this->pointNumber++;
		}
	}
}

void LinearAnimation::apply( float xx, float yy, float zz ){
	if( this->pointNumber < ctrlPoints.size() ){
		glTranslatef( this->x, this->y, this->z );
		glRotatef( this->rotationAngle, 0.0, 1.0, 0.0 );
	}	
}

string LinearAnimation::getID(){
	return this->id;
}