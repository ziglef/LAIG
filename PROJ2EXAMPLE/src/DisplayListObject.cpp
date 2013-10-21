#include "DisplayListObject.h"

#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>

DisplayListObject::DisplayListObject(unsigned int nTriangles, int useDL)
{
	usingDL=useDL;
	nTri=nTriangles;

	dl=glGenLists(1);
	glNewList(dl,GL_COMPILE);
		generateGeometry();
	glEndList();
}

void DisplayListObject::draw()
{
	if (usingDL)
		glCallList(dl);
	else
		generateGeometry();
}

DisplayListObject::~DisplayListObject(void)
{
	glDeleteLists(dl, 1);
}

void myPolyNormal(float* nx, float* ny, float* nz,
				int n, float x[], float y[], float z[])
{
	int i, j;						// esta função destina-se a calcular a normal de um
	float length;					// polígono de n lados, pelo método de Newell
	*nx=0; *ny=0; *nz=0;
	for (i=0; i<n; i++)
	{
		if (i<(n-1)) j=i+1; else j=0;
		*nx+=(z[i]+z[j])*(y[i]-y[j]);
		*ny+=(x[i]+x[j])*(z[i]-z[j]);
		*nz+=(y[i]+y[j])*(x[i]-x[j]);
	}
		length  = sqrt(*nx * *nx + *ny * *ny + *nz * *nz);
		*nx /= length; *ny /= length; *nz /= length;
}


float myRand()
{
	// esta função devolve um número aleatório
	// entre 0 e 1
	return ((float) rand())/RAND_MAX;
}


void DisplayListObject::generateGeometry()
{
	float xxx[3], yyy[3], zzz[3], normalx, normaly, normalz;
	int i;
									// esta função desenha nn triângulos com texturas
	glEnable(GL_COLOR_MATERIAL);

	srand(1);

	for (i=1; i<=nTri; i++)
	{
		glPushMatrix();
		glTranslatef(8.0*myRand(),8.0*myRand(),8.0*myRand());
		glScalef(3.0, 3.0, 3.0);

		glColor3f(myRand(), myRand(), myRand());
		
		glBegin(GL_POLYGON);
			xxx[0] = myRand(); yyy[0] = myRand(); zzz[0] = myRand();
			xxx[1] = myRand(); yyy[1] = myRand(); zzz[1] = myRand();
			xxx[2] = myRand(); yyy[2] = myRand(); zzz[2] = myRand();

			myPolyNormal(&normalx, &normaly, &normalz, 3, xxx, yyy, zzz);
			glNormal3d(normalx, normaly, normalz);

			glTexCoord2f(0.0,0.0); glVertex3f(xxx[0], yyy[0], zzz[0]);
			glTexCoord2f(1.0,0.0); glVertex3f(xxx[1], yyy[1], zzz[1]);
			glTexCoord2f(0.5,0.5); glVertex3f(xxx[2], yyy[2], zzz[2]);
		glEnd();

		glPopMatrix();
	}
}

