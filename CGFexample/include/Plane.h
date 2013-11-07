#ifndef _PLANE_H_
#define _PLANE_h_

#include "Rectangle.h"

class Plane{
	public:
		Plane( int parts );
		~Plane();
		void draw();
	private:
		int parts;
};

#endif