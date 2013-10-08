#include "../include/SpotLight.h"

SpotLight::~SpotLight(){

}

std::string SpotLight::getType(){
	return "spotlight";
}

std::string SpotLight::getID(){
	return this->ref;
}