#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <string>
using std::string;

class Triangle{
	public:
		Triangle( float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3 );
		~Triangle();
	private:
		float x1, y1, z1;
		float x2, y2, z2;
		float x3, y3, z3;
};

#endif