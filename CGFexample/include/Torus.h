#ifndef _TORUS_H_
#define _TORUS_H_

class Torus{
	public:
		Torus();
		~Torus();
	private:
		float inner;
		float outer;
		int slices;
		int loops;
};

#endif