#include "../include/Lighting.h"

Lighting::~Lighting(){

}

std::string Lighting::getID(){
	return "";
}

std::string Lighting::getType(){
	return "";
}

int *Lighting::getToogled(){
	return &toogled;
}

void Lighting::setToogled( int toogled ){
	this->toogled = toogled;
}

bool Lighting::getEnabled(){
	return this->enabled;
}

size_t Lighting::count = GL_LIGHT0;