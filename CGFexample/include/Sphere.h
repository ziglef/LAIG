#ifndef _SPHERE_H_
#define _SPHERE_H_

class Sphere{
	public:
		Sphere( float radius, int slices, int stacks );
		~Sphere();
	private:
		float radius;
		int slices;
		int stacks;
};

#endif