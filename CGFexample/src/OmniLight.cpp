#include "../include/OmniLight.h"

OmniLight::OmniLight( char *id, char *enabled, char *location, char *diffuse, float diffuseX, float diffuseY, float diffuseZ, float diffuseAlfa, char *ambient, float ambientX, float ambientY, float ambientZ, float ambientAlfa, char *specular, float specularX, float specularY, float specularZ, float specularAlfa ){
	this->diffuseX = diffuseX;
	this->diffuseY = diffuseY;
	this->diffuseZ = diffuseZ;
	this->diffuseAlfa = diffuseAlfa;
	this->ambientX = ambientX;
	this->ambientY = ambientY;
	this->ambientZ = ambientZ;
	this->ambientAlfa = ambientAlfa;
	this->specularX = specularX;
	this->specularY = specularY;
	this->specularZ = specularZ;
	this->specularAlfa = specularAlfa;

	this->id = id ;
	this->enabled = enabled;
	this->location = location;
	this->diffuse = diffuse;
	this->ambient = ambient;
	this->specular = specular;
}

OmniLight::~OmniLight(){

}

std::string OmniLight::getType(){
	return "omnilight";
}

std::string OmniLight::getID(){
	return this->id;
}