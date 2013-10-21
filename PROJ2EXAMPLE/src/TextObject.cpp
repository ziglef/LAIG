#include "TextObject.h"
#include <GL/glut.h>

void TextObject::draw()
{
	// Texto 3D, GLUT
	// void glutStrokeCharacter(void *font, int character);	// GLUT_STROKE_ROMAN
	// int glutStrokeWidth(GLUTstrokeFont font, int character);

	// desativa cálculo de iluminação para usar cores diretamente
	glDisable(GL_LIGHTING);

	glPushMatrix();
	glTranslatef(0,0,1);
	glScalef(0.05, 0.05, 0.05);
	glColor3f(0.0,0.0,1.0);		// azul
	glutStrokeCharacter(GLUT_STROKE_ROMAN, 'L');
	glutStrokeCharacter(GLUT_STROKE_ROMAN, 'A');
	glutStrokeCharacter(GLUT_STROKE_ROMAN, 'I');
	glutStrokeCharacter(GLUT_STROKE_ROMAN, 'G');
	glPopMatrix();


	// Texto BitMap, GLUT
	// glRasterPos3f(x,y,z);
	// void glutBitmapCharacter(void *font, int character);	// valores varios...
	// int glutBitmapWidth(GLUTbitmapFont font, int character);

	glPushMatrix();
	glColor3f(1.0,1.0,0.0);		// amarelo
	glRasterPos3f(5,5,5);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'u');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 's');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '!');
	glPopMatrix();

	glEnable(GL_LIGHTING);

}