#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "CGF\CGFobject.h"
#include "GL\glut.h"

class Sphere : CGFobject{
	public:
		Sphere( float radius, int slices, int stacks );
		~Sphere();
		void draw();
	private:
		float radius;
		int slices;
		int stacks;
		GLUquadricObj *quadric;
};

#endif