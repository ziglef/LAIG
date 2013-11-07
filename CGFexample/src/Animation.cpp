#include "../include/Animation.h"

#define RADIUS_SPEED  0.5  // unidades de comprimento por segundo
#define ANGULAR_SPEED 0.5  // rotacoes por segundo
#define START_RADIUS  0.5  // raio inicial
#define START_ANGLE   0    // ângulo inicial

Animation::Animation(){
	rotate_speed_ms= ANGULAR_SPEED *360.0/1000.0;
	radius_speed_ms= RADIUS_SPEED /1000.0;

	reset();
}

Animation::~Animation(){

}

void Animation::init( unsigned long t ){
	startTime=t;
	doReset=false;
}

void Animation::reset(){
	doReset = true;
}

void Animation::update( unsigned long t ){
	if (doReset)
		init(t);
	else
	{
		unsigned long animT=t-startTime;
		obj_rotate= START_ANGLE + animT* rotate_speed_ms;
		obj_radius= START_RADIUS + animT* radius_speed_ms;
	}
}

void Animation::draw(){

}