#include "../include/Appearence.h"

Appearence::~Appearence(){

}

string Appearence::getID(){
	return this->id;
}

float * Appearence::getEmissive(){
	return this->emissive;
}