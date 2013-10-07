#ifndef _OMNILIGHT_H
#define _OMNILIGHT_H

#include "Lightning.h"

class OmniLight : public Lightning{
	public:
		OmniLight( char *id, char *enabled, char *location, char *diffuse, float diffuseX, float diffuseY, float diffuseZ, float diffuseAlfa, char *ambient, float ambientX, float ambientY, float ambientZ, float ambientAlfa, char *specular, float specularX, float specularY, float specularZ, float specularAlfa );
		~OmniLight();
		string getType();
		string getID();
};

#endif