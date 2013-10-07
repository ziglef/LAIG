#include "../include/Texture.h"

Texture::Texture( char *id, char *file ){
	this->id = new string( id );
	this->file = new string( file );
}

Texture::~Texture(){

}