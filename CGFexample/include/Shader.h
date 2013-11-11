#ifndef _SHADER_H_
#define _SHADER_H_

#include "CGFshader.h"
#include "CGFtexture.h"
#include "Plane.h"
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include "CGF\CGFobject.h"

class Shader : public CGFobject, public CGFshader{
	public:
		Shader( char *heightmap, char *texturemap, char *fragmentshader, char *vertexshader );
		virtual void bind(void);
		~Shader(void);
		void setScale(float s);
		void draw();
		float normScale;
	private:
		CGFtexture * baseTexture;
		CGFtexture * secTexture;

		GLint baseImageLoc;
		GLint secImageLoc;

		GLint scaleLoc;

		string heightmap;
		string texturemap;
		string fragmentshader;
		string vertexshader;
		Plane *plane;
		float t;
};

#endif