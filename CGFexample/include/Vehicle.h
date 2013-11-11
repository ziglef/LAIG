#ifndef _VEHICLE_H_
#define _VEHICLE_H_

#include "CGF\CGFobject.h"
#include "Patch.h"
#include <vector>

class Vehicle : public CGFobject{
	public:
		Vehicle();
		~Vehicle();
		void draw();
	private:
		std::vector<Patch *> patch;
};

#endif