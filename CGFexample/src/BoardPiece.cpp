#include "../include/BoardPiece.h"

BoardPiece::BoardPiece(){
	cylinder = new Cylinder(0.3,0.3,0.2,100,100);
}

void BoardPiece::draw(){
	glPushMatrix();
		this->cylinder->draw();
	glPopMatrix();
}

BoardPiece::~BoardPiece(){

}