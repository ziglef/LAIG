#include "../include/Board.h"

Board::Board(){
	logicalBoard = (int **)malloc(sizeof(int *)*8);	appBoard = (int **)malloc(sizeof(int *)*8);	int i;		for(i=0; i<8; i++)		logicalBoard[i] = (int *)malloc(sizeof(int)*8);	for(i=0; i<8; i++)		appBoard[i] = (int *)malloc(sizeof(int)*8);
	for( int i=0; i<8 ; i++ )
		for( int j=0; j<8 ; j++ ){
			logicalBoard[i][j] = 0;
			appBoard[i][j] = 0;
		}

	for( int i=1; i<8 ; i+=2 ){
		logicalBoard[0][i] = 1;
		logicalBoard[2][i] = 1;
	}

	for( int i=0; i<8 ; i+=2){
		logicalBoard[1][i] = 1;
	}

	for( int i=1; i<8 ; i+=2){
		logicalBoard[5][i] = 2;
		logicalBoard[7][i] = 2;
	}

	for( int i=0; i<8 ; i+=2){
		logicalBoard[6][i] = 2;
	}

	for( int i=0; i<8; i++ ){
		if( i%2 == 0 ){
			for( int j=1; j<8; j+=2 )
				appBoard[i][j] = 1;
		}else{
			for( int j=0; j<8; j+=2 )
				appBoard[i][j] = 1;
		}
	}

	white = new CGFappearance();
	black = new CGFappearance();
	green = new CGFappearance();
	red = new CGFappearance();
	white->setTexture("img/white.png");
	black->setTexture("img/black.png");
	green->setTexture("img/green.png");
	red->setTexture("img/red.png");
	boardPiece = new BoardPiece();
}

Board::~Board(){

}

void Board::draw(){
	Rectangle *rect = new Rectangle(0.0, 0.0, 1.0, 1.0);

	glPushName(-1);
		for( int i=0; i<8; i++ ){
			glPushMatrix();
				glRotatef(-90, 0, 1,0);
				glRotatef(-90, 1, 0,0);
				glTranslatef(0, i , 0);
				glLoadName((i+1));
			for (int c=0; c < 8; c++)
			{
				glPushMatrix();
					glTranslatef(c,0,0);
					glPushName((c+1));

					if( logicalBoard[i][c] == 1 ){
						glPushMatrix();
							white->apply();
							glTranslatef(0.5,0.5,0.0);
							boardPiece->draw();
						glPopMatrix();
					}else
						if( logicalBoard[i][c] == 2 ){
							glPushMatrix();
								black->apply();
								glTranslatef(0.5,0.5,0.0);
								boardPiece->draw();
							glPopMatrix();
						}

					if( appBoard[c][i] == 1 ){
						black->apply();
					}else
						if( appBoard[c][i] == 0 ){
							white->apply();
						}else
							if( appBoard[c][1] == 3 ){
								green->apply();
							}else
								if( appBoard[c][1] == 4 ){
									red->apply();
								}else
									black->apply();

					rect->draw();
					glPopName();
				glPopMatrix();
			}
			glPopMatrix();
		}
}

int** Board::getBoard(){
	return this->logicalBoard;
}

void Board::setBoardAt( int x, int y, int value ){
	this->logicalBoard[x][y] = value;
}

int Board::getBoardAt( int x, int y ){
	return this->logicalBoard[x][y];
}

int** Board::getAppBoard(){
	return this->appBoard;
}

void Board::setAppBoardAt( int x, int y, int value ){
	this->appBoard[x][y] = value;
}

int Board::getAppBoardAt( int x, int y ){
	return this->appBoard[x][y];
}