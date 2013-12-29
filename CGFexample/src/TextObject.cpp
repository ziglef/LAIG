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

void TextObject::draw( char * text, int x, int y ){
	this->setOrthographicProjection();
	glPushMatrix();
		glLoadIdentity();
		this->renderBitmapString(x, y ,GLUT_BITMAP_9_BY_15, text);
	glPopMatrix();
	this->resetPerspectiveProjection();

}