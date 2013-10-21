#include "AnimatedObject.h"
#include "CGFApplication.h"
#include <stdio.h>

// declarações para animacao
#define RADIUS_SPEED  0.5  // unidades de comprimento por segundo
#define ANGULAR_SPEED 0.5  // rotacoes por segundo
#define START_RADIUS  0.5  // raio inicial
#define START_ANGLE   0    // ângulo inicial


AnimatedObject::AnimatedObject()
{
	rotate_speed_ms= ANGULAR_SPEED *360.0/1000.0;
	radius_speed_ms= RADIUS_SPEED /1000.0;

	reset();
}

void AnimatedObject::init(unsigned long t)
{
	startTime=t;
	doReset=false;
}

void AnimatedObject::reset()
{
	doReset=true;
}


void AnimatedObject::update(unsigned long t)
{
	if (doReset)
		init(t);
	else
	{
		unsigned long animT=t-startTime;
		obj_rotate= START_ANGLE + animT* rotate_speed_ms;
		obj_radius= START_RADIUS + animT* radius_speed_ms;
	}
}

void AnimatedObject::draw()
{
	glPushMatrix();

	glRotated(obj_rotate, 0,1,0);
	glTranslated(obj_radius,0.0,0.0);
	
	glTranslated(2.0, 0.0, 3.0);
	glRotated(-90.0, 1,0,0);
	glTranslated(0.0, 2.0, 0.0);
	glNormal3d(0.0,0.0,1.0);
	glRectd(-1.0,-2.0, 1.0,2.0);
	glBegin(GL_TRIANGLES);
		glVertex2d( 2.0, 2.0);
		glVertex2d( 0.0, 3.0);
		glVertex2d(-2.0, 2.0);
	glEnd();
	glPopMatrix();
}

