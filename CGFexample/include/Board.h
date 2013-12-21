#ifndef _BOARD_H_
#define _BOARD_H_

#include "CGF\CGFobject.h"
#include "CGF\CGFappearance.h"
#include "Rectangle.h"
#include "BoardPiece.h"
#include <vector>

class Board : public CGFobject{
	public:
		Board();
		~Board();
		void draw();
	private:
		int logicalBoard[8][8];
		int appBoard[8][8];
		CGFappearance *white;
		CGFappearance *black;
		BoardPiece *boardPiece;
		
};

#endif