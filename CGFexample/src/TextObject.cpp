#include "TextObject.h"
#include <string.h>
#include <GL/glut.h>

void TextObject::renderBitmapString(float x, float y, void *font,const char *string){
    const char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
} 

void TextObject::resetPerspectiveProjection() {
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}


void TextObject::setOrthographicProjection() {

	int w = 512;
	int h = 512;

	// switch to projection mode
	glMatrixMode(GL_PROJECTION);

	// save previous matrix which contains the 
	//settings for the perspective projection
	glPushMatrix();

	// reset matrix
	glLoadIdentity();
	//int w = 15; int h = 10;
	// set a 2D orthographic projection
	gluOrtho2D(0, w, 0, h);

	// invert the y axis, down is positive
	glScalef(1, -1, 1);

	// mover the origin from the bottom left corner
	// to the upper left corner
	glTranslatef(0, -h, 0);

	// switch back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void TextObject::draw( char * text )
{
	// Texto 3D, GLUT
	// void glutStrokeCharacter(void *font, int character);	// GLUT_STROKE_ROMAN
	// int glutStrokeWidth(GLUTstrokeFont font, int character);

	// desativa cálculo de iluminação para usar cores diretamente
	glDisable(GL_LIGHTING);

	/*glPushMatrix();
	glTranslatef(0,0,1);
	glScalef(0.05, 0.05, 0.05);
	glColor3f(0.0,0.0,1.0);		// azul
	for( int i=0; i<len; i++ ){
		glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
	}
	glPopMatrix();*/


	// Texto BitMap, GLUT
	// glRasterPos3f(x,y,z);
	// void glutBitmapCharacter(void *font, int character);	// valores varios...
	// int glutBitmapWidth(GLUTbitmapFont font, int character);

	glPushMatrix();
	glColor3f(1.0,1.0,0.0);		// amarelo
	glRasterPos3f(5,5,5);
	for( int i=0; i<strlen(text); i++ ){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);;
	}
	glPopMatrix();

	glEnable(GL_LIGHTING);

}