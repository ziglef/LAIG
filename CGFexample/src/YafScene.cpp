#include "../include/YafScene.h"
#include "../include/Plane.h"
#include "../include/CGF/CGFappearance.h"

Plane *plane;

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
			if( sg->getDrawmode() == "point" )
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
		if( sg->getCullface() == "back" )
			glCullFace( GL_BACK );
		else
			if( sg->getCullface() == "both" )
				glCullFace( GL_FRONT_AND_BACK );

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


	for( map<string, Camera*>::iterator it = sg->getCameras()->begin(); it != sg->getCameras()->end(); it++ ){	
		this->scene_cameras.push_back( it->second );
	}

	//sg->getLights()->at( sg->getInitialCamera() )->setToogled(1);
	sg->setActualCamera(4);

	// Defines a default normal
	glNormal3f(0,0,1);

	// Animation-related code
	unsigned long updatePeriod=30;
	setUpdatePeriod(updatePeriod);

	glutReshapeWindow( 1024, 768 );

	vector<Appearence*> stack;
	stack.clear();
	initGraph( this->sg->getRootid(), stack );
}

void YafScene::update(unsigned long t){
	map<string, GraphNode*>::iterator iter;

	for(iter= sg->graphNodes->begin(); iter != sg->graphNodes->end(); iter++){
		if( iter->second->hasAnimation() ){
			sg->getAnimations()->at( iter->second->getAnimationRef() )->update(t);
		}
	}
}

void YafScene::initGraph( string rootid, vector<Appearence*> &appstack ){

	bool newApp = false;
	GraphNode *n0 = sg->graphNodes->at( rootid );
	unsigned int maxSize = n0->nodeRefIdVector.size();
	
	if( !n0->hasDL() ){

		if( n0->appRefId != "" ){
			if( sg->getAppearences()->count(n0->getAppRefId()) ){ // Is this really needed? //
				appstack.push_back( sg->getAppearences()->at(n0->getAppRefId()));
				newApp = true;
			}
		}

		if(!appstack.empty()){
			glMaterialfv(GL_FRONT, GL_EMISSION, appstack[appstack.size()-1]->getEmissive() );
			appstack[appstack.size()-1]->apply();
		}

		glMultMatrixf( n0->getTransformationMatrix() );

		if( n0->primitives.size() > 0){
			for(unsigned int i=0; i<n0->primitives.size(); i++){
				n0->primitives[i]->draw();
			}
		}

		if( newApp && !appstack.empty() ) appstack.pop_back();

		for(unsigned int i = 0; i<maxSize; i++){
			glPushMatrix();
			initGraph( n0->nodeRefIdVector[i], appstack );
			glPopMatrix();
		}
	} else {
		if( n0->getDL() == 0 ){		// Node DL isn't yet created
			if( maxSize == 0 ){		// If there aren't any more children
				n0->setDL( glGenLists(1) );
				glNewList( n0->getDL(), GL_COMPILE );
					if( n0->appRefId != "" ){
						if( sg->getAppearences()->count(n0->getAppRefId()) ){ // Is this really needed? //
							appstack.push_back( sg->getAppearences()->at(n0->getAppRefId()));
							newApp = true;
						}
					}

					if(!appstack.empty()){
						glMaterialfv(GL_FRONT, GL_EMISSION, appstack[appstack.size()-1]->getEmissive() );
						appstack[appstack.size()-1]->apply();
					}

					glMultMatrixf( n0->getTransformationMatrix() );

					if( n0->primitives.size() > 0){
						for(unsigned int i=0; i<n0->primitives.size(); i++){
							n0->primitives[i]->draw();
						}
					}

					if( newApp && !appstack.empty() ) appstack.pop_back(); // Checking
				glEndList();
			} else {				// If there are still children
				// Call Children //
				glPushMatrix();
					if( n0->appRefId != "" ){
						if( sg->getAppearences()->count(n0->getAppRefId()) ){ // Is this really needed? //
							appstack.push_back( sg->getAppearences()->at(n0->getAppRefId()));
							newApp = true;
						}
					}

					if(!appstack.empty()){
						glMaterialfv(GL_FRONT, GL_EMISSION, appstack[appstack.size()-1]->getEmissive() );
						appstack[appstack.size()-1]->apply();
					}

					glMultMatrixf( n0->getTransformationMatrix() );

					if( n0->primitives.size() > 0){
						for(unsigned int i=0; i<n0->primitives.size(); i++){
							n0->primitives[i]->draw();
						}
					}

					if( newApp && !appstack.empty() ) appstack.pop_back();

					for(unsigned int i = 0; i<maxSize; i++){
						glPushMatrix();
						initGraph( n0->nodeRefIdVector[i], appstack );
						glPopMatrix();
					}
				glPopMatrix();
				// Create DL //
				n0->setDL( glGenLists(1) );
				glNewList( n0->getDL(), GL_COMPILE );
				// Call Children //
				glPushMatrix();

					if( n0->appRefId != "" ){
						if( sg->getAppearences()->count(n0->getAppRefId()) ){ // Is this really needed? //
							appstack.push_back( sg->getAppearences()->at(n0->getAppRefId()));
							newApp = true;
						}
					}

					if(!appstack.empty()){
						glMaterialfv(GL_FRONT, GL_EMISSION, appstack[appstack.size()-1]->getEmissive() );
						appstack[appstack.size()-1]->apply();
					}

					glMultMatrixf( n0->getTransformationMatrix() );

					if( n0->primitives.size() > 0){
						for(unsigned int i=0; i<n0->primitives.size(); i++){
							n0->primitives[i]->draw();
						}
					}

					if( newApp && !appstack.empty() ) appstack.pop_back();

					for(unsigned int i = 0; i<maxSize; i++){
						glPushMatrix();
						initGraph( n0->nodeRefIdVector[i], appstack );
						glPopMatrix();
					}
				glPopMatrix();
				glEndList();
			}
		} else {					// Node DL is already created
			glCallList( n0->getDL() );
		}
	}

}

void YafScene::display(){

	// ---- BEGIN Background, camera and axis setup

	// Clear image and depth buffer everytime we update the scene
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// Initialize Model-View matrix as identity (no transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Drawmode //
	if( *(sg->getDrawModeChoice()) == 0 )
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	else
		if( *(sg->getDrawModeChoice()) == 1 )
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		else
			if( *(sg->getDrawModeChoice()) == 2 )
				glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );

	// Apply transformations corresponding to the camera position relative to the origin
	//activeCamera->applyView();

	/*for( map<string, Camera*>::iterator it = sg->getCameras()->begin(); it != sg->getCameras()->end(); it++ ){      
			if( distance(sg->getCameras()->begin(), it) == *(sg->getActualCamera()))
					this->activateCamera( *(sg->getActualCamera()) + 3 );
	}*/

	switch(*(sg->getActualCamera())){
		case 0 : activeCamera->applyView(); // Free Camera //
				 break;
		case 1 : gluLookAt (0.0, 7.5, 12.5, 12.5, 3.0, 12.5, 0.0, 1.0, 0.0); // White Player //
				 break;
		case 2 : gluLookAt (25.0, 7.5, 12.5, 12.5, 3.0, 12.5, 0.0, 1.0, 0.0); // Black Player //
				 break;
		case 3 : gluLookAt (12.5, 7.5, 0.0, 12.5, 3.0, 12.5, 0.0, 1.0, 0.0); // Sideview //
				 break;
		case 4 : gluLookAt (0.0, 15.0, 0.0, 12.5, 5.0, 12.5, 0.0, 1.0, 0.0); // OverView //
				 break;

	}

	//activeCamera->applyView();

	// Draw (and update) light
	for( map<string, Lighting*>::iterator it = sg->getLights()->begin(); it != sg->getLights()->end(); it++ ){	
		if( *(it->second->getToogled()) ){
			it->second->enable();
		}
		else
			it->second->disable();

		it->second->update();
		it->second->draw();
	}
	
	// Draw axis
	//axis.draw();


	// ---- END Background, camera and axis setup


	// ---- END feature demos
	vector<Appearence*> stack;
	stack.clear();
	processGraph( this->sg->getRootid(), stack );
	if( sg->gameOver ){
		char *gameOverMsg = (char *)malloc(sizeof(char) * 256 );
		char *gameOverMsgAux = (char *)malloc(sizeof(char) * 65 );
		
		strcpy(gameOverMsg, "GAME OVER ! ");
		if( sg->p1points > sg->p2points ){
			strcat(gameOverMsg, "Player ");
			itoa(1, gameOverMsgAux, 10);
			strcat(gameOverMsg, gameOverMsgAux);
			strcat(gameOverMsg, " Wins!");
		} else if( sg->p2points > sg->p1points ){
			strcat(gameOverMsg, "Player ");
			itoa(2, gameOverMsgAux, 10);
			strcat(gameOverMsg, gameOverMsgAux);
			strcat(gameOverMsg, " Wins!");
		} else {
			strcat(gameOverMsg, "It's a draw!");
		}

		sg->getPainter()->draw(gameOverMsg, 100, 100);


		char *gameTime = (char *)malloc(sizeof(char)*512);
		char *gameTimeAux = (char *)malloc(sizeof(char)*65);

		strcpy(gameTime, "The game took ");
		itoa((sg->endTime-sg->startTime)/1000.0, gameTimeAux, 10);
		strcat(gameTime, gameTimeAux);
		strcat(gameTime, " seconds!");

		sg->getPainter()->draw(gameTime, 100, 120);
	}

	char *p1score = (char *)malloc(sizeof(char) *256);
	char *p2score = (char *)malloc(sizeof(char) *256);
	char *p1aux = (char *)malloc(sizeof(char)*65);
	char *p2aux = (char *)malloc(sizeof(char)*65);

	strcat(p1score, "Player 1: ");
	strcat(p2score, "Player 2: ");

	itoa(sg->p1points, p1aux, 10);
	strcat(p1score, p1aux);
	itoa(sg->p2points, p2aux, 10);
	strcat(p2score, p2aux);

	strcat(p1score, " points!");
	strcat(p2score, " points!");
	sg->getPainter()->draw(p1score, 100, 140);
	sg->getPainter()->draw(p2score, 100, 160);

	if( sg->getPlayingMovie() == true ) {

		if( movieIndex == 0 ){
			sg->setCurrentLogical( sg->getLogicalBoard() );
			sg->setCurrentAppearence( sg->getAppearenceBoard() );
			this->sg->setBothBoards( sg->pStack[movieIndex], sg->pStack[movieIndex+1] );
			movieIndex += 2;
			timeElapsed = glutGet(GLUT_ELAPSED_TIME);
		}

		if((glutGet(GLUT_ELAPSED_TIME) - timeElapsed > 1000 ) && (movieIndex < sg->pStack.size())){
			this->sg->setBothBoards( sg->pStack[movieIndex], sg->pStack[movieIndex+1] );
			movieIndex += 2;
			timeElapsed = glutGet(GLUT_ELAPSED_TIME);
		}

		if((movieIndex >= sg->pStack.size()) && (glutGet(GLUT_ELAPSED_TIME) - timeElapsed > 1000 )){
			this->sg->setBothBoards( sg->getCurrentLogical(), sg->getCurrentAppearence() );
			sg->setPlayingMovie( false );
			movieIndex = 0;
			timeElapsed = 0;
		}
	}

	glPushMatrix();
		glTranslatef(8.5 ,0.5, 8.5);
		this->sg->getBoard()->draw();
	glPopMatrix();
	//this->sg->getText()->draw("FAIL");
	// We have been drawing in a memory area that is not visible - the back buffer, 
	// while the graphics card is showing the contents of another buffer - the front buffer
	// glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
	glutSwapBuffers();

}

void YafScene::processGraph( string rootid, vector<Appearence*> &appstack ){
	GraphNode *n0 = sg->graphNodes->at( rootid );
	sg->updateTheme();

	bool newApp = false;

	unsigned int maxSize = n0->nodeRefIdVector.size();

	if( n0->hasDL() ){
		glCallList( n0->getDL() );	
	}else{
		if( n0->appRefId != "" ){
			if( sg->getAppearences()->count(n0->getAppRefId()) ){ // Is this really needed? //
				appstack.push_back( sg->getAppearences()->at(n0->getAppRefId()));
				newApp = true;
			}
		}

		if(!appstack.empty()){
			glMaterialfv(GL_FRONT, GL_EMISSION, appstack[appstack.size()-1]->getEmissive() );
			appstack[appstack.size()-1]->apply();
		}
		
		glMultMatrixf( n0->getTransformationMatrix() );

		if( n0->hasAnimation() )
			sg->getAnimations()->at( n0->getAnimationRef() )->apply( n0->getTransformationMatrix()[12], n0->getTransformationMatrix()[13], n0->getTransformationMatrix()[14] );

		if( n0->primitives.size() > 0){
			for(unsigned int i=0; i<n0->primitives.size(); i++){
				n0->primitives[i]->draw();
			}
		}

		if( newApp && !appstack.empty() ) appstack.pop_back();

		for(unsigned int i = 0; i<maxSize; i++){
			glPushMatrix();
			processGraph( n0->nodeRefIdVector[i], appstack );
			glPopMatrix();
		}
	}

}

vector<CGFcamera*>  *YafScene::getSceneCameras(){
	return &scene_cameras;
}

void YafScene::activateCamera( int i )
{
	if( i < scene_cameras.size() )
	{
		activeCamera = scene_cameras.at( i );
		CGFapplication::activeApp->forceRefresh();
	}
}

YafScene::~YafScene(){

}