#include "../include/LinearAnimation.h"
#include <GL/glut.h>

LinearAnimation::LinearAnimation( int animationCp, float **originalMatrix, float totalDuration ){

	float totalDistance, pointsDistance, pointDuration;

	for(int i=0; i<animationCp; ++i){
			AnimationPoint *point;
			point = new AnimationPoint( originalMatrix[i][0], originalMatrix[i][1], originalMatrix[i][2] );
			ctrlPoints.push_back( point );
	}

	for(int i=1; i<animationCp; ++i ){
		pointsDistance = sqrt( pow(( ctrlPoints.at(i)->getX()-ctrlPoints.at(i-1)->getX() ), 2 ) + pow(( ctrlPoints.at(i)->getZ()-ctrlPoints.at(i-1)->getZ() ), 2) );
		totalDistance += pointsDistance;
		ctrlPoints.at(i-1)->setDistance( pointsDistance );
	}

	ctrlPoints.at( ctrlPoints.size()-1 )->setDistance(0);

	for(int i=0; i<animationCp; ++i ){
		pointDuration = (totalDuration * ctrlPoints.at(i)->getDistance())/totalDistance;
		ctrlPoints.at(i)->setDuration(pointDuration);
	}
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

void LinearAnimation::update( unsigned long t ){
	if (doReset){
		init(t);
	}else{

	}
}

void LinearAnimation::draw(){
	glPushMatrix();

	glPopMatrix();
}