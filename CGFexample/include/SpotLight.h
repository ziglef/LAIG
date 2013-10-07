#ifndef _SPOTLIGHT_H
#define _SPOTLIGHT_H

#include "Lighting.h"

class SpotLight : public Lighting{
	public:
		SpotLight( char *id, char *enabled, char *location, char *diffuse, float diffuseX, float diffuseY, float diffuseZ, float diffuseAlfa, char *ambient, float ambientX, float ambientY, float ambientZ, float ambientAlfa, char *specular, float specularX, float specularY, float specularZ, float specularAlfa, float angle, float exponent, char *direction, float directionX, float directionY, float directionZ );
		~SpotLight();
		string getType();

	protected:
		float angle;
		float exponent;
		string *direction;
		float directionX, directionY, directionZ;
};

#endif