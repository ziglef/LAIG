#include "../include/OrthogonalCamera.h"

OrthogonalCamera::~OrthogonalCamera(){

}

std::string OrthogonalCamera::getType(){
	return "orthogonalcamera";
}

std::string OrthogonalCamera::getID(){
	return this->id;
}