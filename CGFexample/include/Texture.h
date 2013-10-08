#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "CGF\CGFtexture.h"
#include <string>
using std::string;

class Texture : public CGFtexture{
	public:
		Texture( char *id, char *file ) : CGFtexture( file ){
			this->id = id;
		}
		~Texture();
		string getID();

	protected:
		string id;
};

#endif