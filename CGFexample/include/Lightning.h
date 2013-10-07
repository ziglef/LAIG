#ifndef _LIGHTNING_H
#define _LIGHTNING_H

#include <string>
using std::string;

class Lightning{
	public:
		Lightning();
		~Lightning();
		virtual string getType();
		virtual string getID();

	protected:
		string id;
		string enabled;
		string location;
		string diffuse;
		float diffuseX, diffuseY, diffuseZ, diffuseAlfa;
		string ambient;
		float ambientX, ambientY, ambientZ, ambientAlfa;
		string specular;
		float specularX, specularY, specularZ, specularAlfa;
};

#endif