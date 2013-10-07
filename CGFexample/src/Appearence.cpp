#include "../include/Appearence.h"

Appearence::Appearence( char *id, char *emissive, float emissiveX, float emissiveY, float emissiveZ, float emissiveAlfa, char *diffuse, float diffuseX, float diffuseY, float diffuseZ, float diffuseAlfa, char *ambient, float ambientX, float ambientY, float ambientZ, float ambientAlfa, char *specular, float specularX, float specularY, float specularZ, float specularAlfa, float shininess, char *textureref, float texlength_s, float texlength_t ){
	this->emissiveX = emissiveX;
	this->emissiveY = emissiveY;
	this->emissiveZ = emissiveZ;
	this->emissiveAlfa = emissiveAlfa;
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
	this->shininess = shininess;
	this->texlength_s = texlength_s;
	this->texlength_t = texlength_t;

	this->id = new string( id );
	this->emissive = new string( emissive );
	this->diffuse = new string( diffuse );
	this->ambient = new string( ambient );
	this->specular = new string( specular );
	this->textureref = new string( textureref );
}

Appearence::~Appearence(){

}