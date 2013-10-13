#ifndef _APPEARENCE_H_
#define _APPEARENCE_H_

#include "CGF\CGFappearance.h"
#include <string>
using std::string;

class Appearence : public CGFappearance{
	public:
		Appearence( 
			char *id,
			float *emissive,
			float *ambient,
			float *diffuse,
			float *specular,
			float shininess,
			CGFtexture *texture,
			int sWrap,
			int tWrap) :
		  CGFappearance( ambient, diffuse, specular, shininess ){
			  this->id = id;
			  
			  for(int i=0; i<4; i++)
		  		  this->emissive[i] = emissive[i];

				if(texture != NULL){
					this->setTexture(texture);
					this->setTextureWrap(sWrap, tWrap);
				}

		  }


		Appearence( 
			char *id,
			float *emissive,
			float *ambient,
			float *diffuse,
			float *specular,
			float shininess) :
		  CGFappearance( ambient, diffuse, specular, shininess ){
			  this->id = id;
			  
			  for(int i=0; i<4; i++)
		  		  this->emissive[i] = emissive[i];
		  }

		~Appearence();

		string getID();
		float *getEmissive();
		string getTexture();

	protected:
		string id;
		float emissive[4];
};

#endif