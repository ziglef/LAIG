#include "../include/SpotLight.h"

SpotLight::SpotLight( char *id, char *enabled, char *location, char *diffuse, float diffuseX, float diffuseY, float diffuseZ, float diffuseAlfa, char *ambient, float ambientX, float ambientY, float ambientZ, float ambientAlfa, char *specular, float specularX, float specularY, float specularZ, float specularAlfa, float angle, float exponent, char *direction, float directionX, float directionY, float directionZ ){
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
	this->angle = angle;
	this->exponent = exponent;
	this->directionX = directionX;
	this->directionY = directionY;
	this->directionZ = directionZ;

	this->id = new string( id );
	this->enabled = new string( enabled );
	this->location = new string( location );
	this->diffuse = new string( diffuse );
	this->ambient = new string( ambient );
	this->specular = new string( specular );
	this->direction = new string( direction );
}

SpotLight::~SpotLight(){

}

std::string SpotLight::getType(){
	return "spotlight";
}