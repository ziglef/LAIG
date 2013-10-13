#ifndef _CYLINDER_H_
#define _CYLINDER_H_

#include "math.h"
#include "CGF\CGFobject.h"
#include "GL\glut.h"

class Cylinder : public CGFobject{
	public:
		Cylinder( float base, float top, float height, int slices, int stacks );
		~Cylinder();
		void draw();
		void drawBase();
		void drawTop();
	private:
		float base;
		float top;
		float height;
		int slices;
		int stacks;
		GLUquadricObj *quadric;
};

#endif