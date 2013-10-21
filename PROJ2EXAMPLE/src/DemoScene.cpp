#include "DemoScene.h"
#include "CGFaxis.h"
#include "CGFapplication.h"

#include <math.h>

#include "CGFappearance.h"

#include "DemoShader.h"


void DemoScene::init() 
{
	// Ouptut example information
	printf("-------------------------\n");
	printf("This scene highlights some importante features, using individual classes:\n");
	printf("\n");

	printf(" - DemoShader shows a shader with parameters changed in real time.\n");
	printf("\n");
	printf(" - EvaluatorObject shows how to build an evaluator.\n");
	printf("\n");
	printf(" - DisplayListObject uses a display list to store a set of GL commands.\n");
	printf("\n");

	printf(" - IncrementAnimatedObject shows an animation based on pre-computed increments.\n");
	printf(" - AnimatedObject shows a better animation, based on real time between updates.\n");
	printf("\n");
	
	printf(" - TextObject renders example vector and bitmap text.\n");
	printf("\n");

	printf("Make sure you consult the DemoScene and DemoInterface classes to see how everything is put together.\n");
	printf("\n");


	printf("-------------------------\n");


	// Enables lighting computations
	glEnable(GL_LIGHTING);

	// Sets up some lighting parameters
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, CGFlight::background_ambient);  // Define ambient light

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);	

	// Declares and enables a light
	float light0_pos[4] = {4.0, 6.0, 0.0, 1.0};
	float light0_diff[4] = {1.0,1.0,1.0, 1.0};
	light0 = new CGFlight(GL_LIGHT0, light0_pos);
	light0->setDiffuse(light0_diff);
	light0->enable();

	// Defines a default normal
	glNormal3f(0,0,1);

	wireframe=0;

	demoshader=new DemoShader();

	// text

	myTextObj=new TextObject();

	// Display List

	myDLObj=new DisplayListObject(1000, 1);

	// Animation-related code
	unsigned long updatePeriod=50;
	setUpdatePeriod(updatePeriod);

	myIncAnimObj=new IncrementAnimatedObject(updatePeriod);
	myTimeAnimObj=new AnimatedObject();

	myEvalObj=new EvaluatorObject();

}

void DemoScene::update(unsigned long t)
{
	myIncAnimObj->update(t);
	myTimeAnimObj->update(t);
}


void DemoScene::display() 
{

	// ---- BEGIN Background, camera and axis setup
	
	// Clear image and depth buffer everytime we update the scene
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


	// Initialize Model-View matrix as identity (no transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Apply transformations corresponding to the camera position relative to the origin
	CGFscene::activeCamera->applyView();

	// Draw (and update) light
	light0->draw();

	// Draw axis
	axis.draw();

	if (wireframe)
		glPolygonMode(GL_FRONT, GL_LINE);
	else
		glPolygonMode(GL_FRONT, GL_FILL);



	// ---- END Background, camera and axis setup


	// ---- BEGIN feature demos

	// parameterized shader

	glPushMatrix();

	glTranslatef(5,0,5);

	demoshader->bind();

	glFrontFace(GL_CW);	// front faces of teapot are specified in CW order
	glutSolidTeapot(3);
	glFrontFace(GL_CCW);
	
	demoshader->unbind();

	glPopMatrix();


	// Animated Object
	glDisable(GL_LIGHTING);

	glPushMatrix();

	glColor3f(1,0,0);
	myIncAnimObj->draw();

	//glTranslatef(0,0.5,0);

	glColor3f(0,1,0);
	myTimeAnimObj->draw();

	glPopMatrix();

	glEnable(GL_LIGHTING);
	// Text Object

	myTextObj->draw();

	// Display List Object
	glPushMatrix();

	glTranslatef(-15,0,0);
	myDLObj->draw();
	
	glPopMatrix();

	// Evaluator object

	glPushMatrix();

	glTranslatef(0,0,-5);

	myEvalObj->draw();

	glPopMatrix();
	// ---- END feature demos

	// We have been drawing in a memory area that is not visible - the back buffer, 
	// while the graphics card is showing the contents of another buffer - the front buffer
	// glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
	glutSwapBuffers();
}

DemoScene::~DemoScene()
{
	delete(demoshader);
	delete(light0);

	delete(myIncAnimObj);
	delete(myTimeAnimObj);

	delete(myTextObj);

	delete(myDLObj);

	delete(myEvalObj);
}
