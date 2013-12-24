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
		int** getBoard();
		void setBoardAt( int x, int y, int value );
		int getBoardAt( int x, int y );
		int** getAppBoard();
		void setAppBoardAt( int x, int y, int value );
		int getAppBoardAt( int x, int y );
		void draw();
	private:
		int **logicalBoard;
		int **appBoard;
		CGFappearance *white;
		CGFappearance *black;
		CGFappearance *green;
		BoardPiece *boardPiece;
		
};

#endif