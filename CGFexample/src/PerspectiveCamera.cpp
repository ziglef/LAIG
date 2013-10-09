#include "../include/PerspectiveCamera.h"

PerspectiveCamera::~PerspectiveCamera(){

}

std::string PerspectiveCamera::getType(){
	return "perspectivecamera";
}

std::string PerspectiveCamera::getID(){
	return this->id;
}