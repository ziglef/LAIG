#ifndef _APPEARENCE_H_
#define _APPEARENCE_H_

#include <string>
using std::string;

class Appearence{
	public:
		Appearence( char *id, char *emissive, float emissiveX, float emissiveY, float emissiveZ, float emissiveAlfa, char *diffuse, float diffuseX, float diffuseY, float diffuseZ, float diffuseAlfa, char *ambient, float ambientX, float ambientY, float ambientZ, float ambientAlfa, char *specular, float specularX, float specularY, float specularZ, float specularAlfa, float shininess, char *textureref, float texlength_s, float texlength_t );
		~Appearence();

	protected:
		string *id;
		string *emissive;
		float emissiveX, emissiveY, emissiveZ, emissiveAlfa;
		string *diffuse;
		float diffuseX, diffuseY, diffuseZ, diffuseAlfa;
		string *ambient;
		float ambientX, ambientY, ambientZ, ambientAlfa;
		string *specular;
		float specularX, specularY, specularZ, specularAlfa;
		float shininess;
		string *textureref;
		float texlength_s;
		float texlength_t;
};

#endif