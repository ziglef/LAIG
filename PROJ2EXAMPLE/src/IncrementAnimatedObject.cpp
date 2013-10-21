#include "IncrementAnimatedObject.h"
#include <GL/glut.h>
#include <stdio.h>

// declarações para animacao
#define RADIUS_SPEED  0.5  // unidades de comprimento por segundo
#define ANGULAR_SPEED 0.5  // rotacoes por segundo
#define START_RADIUS  0.5  // raio inicial
#define START_ANGLE   0    // ângulo inicial


IncrementAnimatedObject::IncrementAnimatedObject(unsigned long mili_secs)
{
	// Using pre-computed deltas will result in dependence of the actual update frequency
	delta_rotate = (double) mili_secs/1000.0 * ANGULAR_SPEED *360.0;
	delta_radius = (double) mili_secs/1000.0 * RADIUS_SPEED;

	reset();
}

void IncrementAnimatedObject::reset()
{
	doReset=true;
}

void IncrementAnimatedObject::init()
{
	obj_rotate = START_ANGLE;
	obj_radius = START_RADIUS;
	doReset=false;
}


void IncrementAnimatedObject::update(unsigned long t)
{
	if (doReset)
		init();
	else
	{
		obj_rotate += delta_rotate;
		obj_radius += delta_radius;
	}
}

void IncrementAnimatedObject::draw()
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

