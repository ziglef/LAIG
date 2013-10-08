#ifndef _CYLINDER_H_
#define _CYLINDER_H_

class Cylinder{
	public:
		Cylinder( float base, float top, float height, int slices, int stacks );
		~Cylinder();
	private:
		float base;
		float top;
		float height;
		int slices;
		int stacks;
};

#endif