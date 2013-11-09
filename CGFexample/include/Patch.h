#ifndef _PATCH_H_
#define _PATCH_H_

#include "CGF\CGFobject.h"

#include <string>
using std::string;

class Patch : public CGFobject{
	public:
		Patch( int order, int partsU, int partsV, string compute, int ctrlPoints, float **originalMatrix );
		~Patch();
		void draw();
	private:
		int order;
		int partsU;
		int partsV;
		string compute;
		int ctrlPoints; 
};

#endif