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
		void movePiece( int x1, int y1, int x2, int y2 );
		int **logicalBoard;
		int **appBoard;

		void setWhitePieceApp( CGFappearance *whitePiece );
		void setBlackPieceApp( CGFappearance *blackPiece );

		CGFappearance* getWhitePieceApp();
		CGFappearance* getBlackPieceApp();

		CGFappearance* getWhitePieceApp1();
		CGFappearance* getBlackPieceApp1();

		CGFappearance* getWhitePieceApp2();
		CGFappearance* getBlackPieceApp2();

	private:
		CGFappearance *white;
		CGFappearance *black;

		CGFappearance *actualBlackPiece;
		CGFappearance *actualWhitePiece;
		CGFappearance *blackPiece;
		CGFappearance *whitePiece;
		CGFappearance *blackPiece1;
		CGFappearance *whitePiece1;
		CGFappearance *blackPiece2;
		CGFappearance *whitePiece2;

		CGFappearance *green;
		CGFappearance *red;
		BoardPiece *boardPiece;
		
};

#endif