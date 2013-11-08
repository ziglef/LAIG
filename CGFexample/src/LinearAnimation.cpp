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


	this->x = ctrlPoints.at(0)->getX();
	this->y = ctrlPoints.at(0)->getY();
	this->z = ctrlPoints.at(0)->getZ();

	pointNumber=0;
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
		if( pointNumber < ctrlPoints.size() ){

			if( ctrlPoints.at(pointNumber)->getIterations() == 0 )
				//calcular rotação

			this->x += ( ctrlPoints.at(pointNumber+1)->getX() -  ctrlPoints.at(pointNumber)->getX() )/( ctrlPoints.at(pointNumber)->getDuration() * 30 );
			this->y += ( ctrlPoints.at(pointNumber+1)->getY() -  ctrlPoints.at(pointNumber)->getY() )/( ctrlPoints.at(pointNumber)->getDuration() * 30 );
			this->z += ( ctrlPoints.at(pointNumber+1)->getZ() -  ctrlPoints.at(pointNumber)->getZ() )/( ctrlPoints.at(pointNumber)->getDuration() * 30 );

			ctrlPoints.at(pointNumber)->setIterations(ctrlPoints.at(pointNumber)->getIterations()+1);
			if( ctrlPoints.at(pointNumber)->getIterations() == ctrlPoints.at(pointNumber)->getMaxIterations() )
				pointNumber++;
		}
	}
}

void LinearAnimation::draw(){
	glPushMatrix();
		glTranslatef( this->x, this->y, this->z );
	glPopMatrix();
}