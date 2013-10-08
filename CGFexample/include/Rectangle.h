#ifndef _RECTANGLE_H_
#define _RECTANGLEe_H_

#include "CGF\CGFobject.h"

#include <string>
using std::string;

class Rectangle : CGFobject{
	public:
		Rectangle( float x1, float y1, float x2, float y2 );
		~Rectangle();
		void draw();
	private:
		float x1, x2, y1, y2;
};

#endif