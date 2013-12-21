#ifndef _BOARDPIECE_H_
#define _BOARDPIECE_H_

#include "Cylinder.h"

class BoardPiece{
	public:
		BoardPiece();
		~BoardPiece();
		void draw();
	private:
		Cylinder *cylinder;
};

#endif