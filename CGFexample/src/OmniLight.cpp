#include "../include/OmniLight.h"

OmniLight::~OmniLight(){

}

std::string OmniLight::getType(){
	return "omnilight";
}

std::string OmniLight::getID(){
	return this->ref;
}