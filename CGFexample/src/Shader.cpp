#include <GL/glew.h>
#include "../include/Shader.h"

Shader::Shader( char *heightmap, char *texturemap, char *fragmentshader, char *vertexshader ){

	this->heightmap = heightmap;
	this->texturemap = texturemap;
	this->fragmentshader = fragmentshader;
	this->vertexshader = vertexshader;

	this->t = 0.0;
	this->plane = new Plane( 10 );

	init(this->vertexshader.c_str(), this->fragmentshader.c_str());

	CGFshader::bind();

	baseTexture=new CGFtexture(this->texturemap.c_str());
	secTexture=new CGFtexture(this->heightmap.c_str());

	// get the uniform location for the sampler
	baseImageLoc = glGetUniformLocation(id(), "tImage");

	// set the texture id for that sampler to match the GL_TEXTUREn that you 
	// will use later e.g. if using GL_TEXTURE0, set the uniform to 0
	glUniform1i(baseImageLoc, 0);

	// repeat if you use more textures in your shader(s)
	secImageLoc = glGetUniformLocation(id(), "hImage");
	glUniform1i(secImageLoc, 1);
}

Shader::~Shader(){
	delete(baseTexture);
}

void Shader::bind(){
	CGFshader::bind();

	this->t+=0.003;

	update(t);

	// update uniforms
	//glUniform1f(scaleLoc, normScale);

	// make sure the correct texture unit is active
	glActiveTexture(GL_TEXTURE0);

	// apply/activate the texture you want, so that it is bound to GL_TEXTURE0
	baseTexture->apply();

	// do the same for other textures
	glActiveTexture(GL_TEXTURE1);

	secTexture->apply();

	glActiveTexture(GL_TEXTURE0);

	plane->draw();
	this->unbind();
}

void Shader::draw(){
	this->bind();
}

