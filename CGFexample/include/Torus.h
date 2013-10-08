#ifndef _TORUS_H_
#define _TORUS_H_

#include "CGF\CGFobject.h"
#include "GL\glut.h"

class Torus : CGFobject{
	public:
		Torus( float inner, float outer, int slices, int loops );
		~Torus();
		void draw();
	private:
		float inner;
		float outer;
		int slices;
		int loops;
};

#endif