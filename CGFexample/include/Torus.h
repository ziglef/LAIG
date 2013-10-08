#ifndef _TORUS_H_
#define _TORUS_H_

class Torus{
	public:
		Torus( float inner, float outer, int slices, int loops );
		~Torus();
	private:
		float inner;
		float outer;
		int slices;
		int loops;
};

#endif