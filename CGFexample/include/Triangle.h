#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <string>
using std::string;

class Triangle{
	public:
		Triangle();
		~Triangle();
	private:
		string xyz1;
		string xyz2;
		string xyz3;
		float x1, y1, z1;
		float x2, y2, z2;
		float x3, y3, z3;
};

#endif