#ifndef _LIGHTING_H
#define _LIGHTING_H

#include <string>
using std::string;

class Lighting{
	public:
		Lighting();
		~Lighting();
		virtual string getType()=0;

	protected:
		string *id;
		string *enabled;
		string *location;
		string *diffuse;
		float diffuseX, diffuseY, diffuseZ, diffuseAlfa;
		string *ambient;
		float ambientX, ambientY, ambientZ, ambientAlfa;
		string *specular;
		float specularX, specularY, specularZ, specularAlfa;
};

#endif