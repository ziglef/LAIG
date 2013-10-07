#ifndef _RECTANGLE_H_
#define _RECTANGLEe_H_

#include <string>
using std::string;

class Rectangle{
	public:
		Rectangle();
		~Rectangle();
	private:
		string xy1;
		string xy2;
		float x1, x2, y1, y2;
};

#endif