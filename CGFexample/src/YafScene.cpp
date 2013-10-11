#include "../include/YafScene.h"

#include "../include/Rectangle.h"
#include "../include/CGF/CGFappearance.h"

void YafScene::init(){

	// Globals //

	// Background color //
	glClearColor( sg->getbgx(), sg->getbgy(), sg->getbgz(), sg->getbga() );

	// Drawmode //
	if( sg->getDrawmode() == "fill" )
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	else
		if( sg->getDrawmode() == "line" )
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		else
			if( sg->getDrawmode() == "both" )
				glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );

	// Shading //
	if( sg->getShading() == "flat" )
		glShadeModel( GL_FLAT );
	else
		glShadeModel( GL_SMOOTH );

	// Cullface //
	if( sg->getCullface() == "front" )
		glCullFace( GL_FRONT );
	else
		glCullFace( GL_BACK );

	// Cullorder //
	if( sg->getCullorder() == "CW" )
		glFrontFace( GL_CW );
	else
		glFrontFace( GL_CCW );

	// Lighting //

	// Doublesided //
	if( sg->getDoublesided() == "true" )
		glLightModelf( GL_LIGHT_MODEL_TWO_SIDE, 1 );
	else
		glLightModelf( GL_LIGHT_MODEL_TWO_SIDE, 0 );

	// Local //
	if( sg->getLocal() == "true" )
		glLightModelf( GL_LIGHT_MODEL_LOCAL_VIEWER, 1 );
	else
		glLightModelf( GL_LIGHT_MODEL_LOCAL_VIEWER, 0 );

	// Enabled //
	if( sg->getLightingEnabled() == "true" )
		glEnable(GL_LIGHTING);

	// Ambient //
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, sg->getLightingAmbientValues() );

	for( map<string, Lighting*>::iterator it = sg->getLights()->begin(); it != sg->getLights()->end(); it++){
			it->second->enable();
	}	

	// Defines a default normal
	glNormal3f(0,0,1);
}

void YafScene::display(){

	// ---- BEGIN Background, camera and axis setup

	// Clear image and depth buffer everytime we update the scene
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// Initialize Model-View matrix as identity (no transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Apply transformations corresponding to the camera position relative to the origin
	sg->getCameras()->at( sg->getInitialCamera() )->applyView();
	//CGFscene::activeCamera->applyView();

	// Draw (and update) light
	for( map<string, Lighting*>::iterator it = sg->getLights()->begin(); it != sg->getLights()->end(); it++ ){	
		it->second->draw();
	}

	// Draw axis
	axis.draw();


	// ---- END Background, camera and axis setup


	// ---- END feature demos
	processGraph( this->sg->getRootid() );
	
	// We have been drawing in a memory area that is not visible - the back buffer, 
	// while the graphics card is showing the contents of another buffer - the front buffer
	// glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
	glutSwapBuffers();

}

void YafScene::processGraph( string rootid ){
	GraphNode *n0 = sg->graphNodes->at( rootid );
	unsigned int maxSize = n0->nodeRefIdVector.size();

	if( n0->appRefId != "" ) sg->appearences->at( n0->appRefId )->apply();
	glMultMatrixf( n0->getTransformationMatrix() );

	if( n0->primitives.size() > 0){
		for(unsigned int i=0; i<n0->primitives.size(); i++){
			n0->primitives[i]->draw();
		}
	}

	for(unsigned int i = 0; i<maxSize; i++){
		glPushMatrix();
		processGraph( n0->nodeRefIdVector[i] );
		glPopMatrix();
	}

}

YafScene::~YafScene(){

}