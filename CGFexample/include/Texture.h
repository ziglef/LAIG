#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <string>
using std::string;

class Texture{
	public:
		Texture( char *id, char *file );
		~Texture();

	protected:
		string *id;
		string *file;
};

#endif