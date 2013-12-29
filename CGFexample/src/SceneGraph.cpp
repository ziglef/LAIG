#include "../include/SceneGraph.h"

SceneGraph::SceneGraph( float bgX, float bgY, float bgZ, float bgA, char *drawmode, char *shading, char *cullface, char *cullorder ){
	this->bgX = bgX;
	this->bgY = bgY;
	this->bgZ = bgZ;
	this->bgA = bgA;

	this->drawmode = drawmode;
	this->shading = shading;
	this->cullface = cullface;
	this->cullorder = cullorder;

	this->cameras = new map<string, Camera*>;
	this->lights = new map<string, Lighting*>;
	this->textures = new map<string, Texture*>;
	this->appearences = new map<string, Appearence*>;
	this->graphNodes = new map<string, GraphNode*>;
	this->animations = new map<string, LinearAnimation*>;
	this->text = new TextObject();
	this->actualTheme = 1;
}

void SceneGraph::setInitialCamera( char *initCamera){
	this->initialCamera = initCamera;
}

void SceneGraph::addCamera( Camera *camera ){
	this->cameras->insert( std::pair<string, Camera*>(camera->getID(), camera) );
}

void SceneGraph::addLight( Lighting *light ){
	this->lights->insert( std::pair<string, Lighting*>(light->getID(), light) );
}

void SceneGraph::addLightingValues( char *doublesided, char *local, char *LightingEnabled, float *LightingAmbientV ){
	for(int i=0; i<4; i++) this->LightingAmbientV[i] = LightingAmbientV[i];
	
	this->doublesided = doublesided;
	this->local = local;
	this->LightingEnabled = LightingEnabled;
}

void SceneGraph::addTexture( Texture *texture ){
	this->textures->insert( std::pair<string, Texture *>(texture->getID(), texture) );
}

void SceneGraph::addAnimation( LinearAnimation *animation ){
	this->animations->insert( std::pair<string, LinearAnimation *>(animation->getID(), animation) );
}

void SceneGraph::addAppearence( Appearence *appearence ){
	this->appearences->insert( std::pair<string, Appearence*>(appearence->getID(), appearence) );
}

void SceneGraph::setRootId( char *rootId ){
	this->rootid = rootId;
}

void SceneGraph::addGraphNode( GraphNode *graphNode ){
	this->graphNodes->insert( std::pair<string, GraphNode*>(graphNode->getID(), graphNode) );
}

float SceneGraph::getbgx(){
	return this->bgX;
}

float SceneGraph::getbgy(){
	return this->bgY;
}

float SceneGraph::getbgz(){
	return this->bgZ;
}

float SceneGraph::getbga(){
	return this->bgA;
}

string SceneGraph::getDrawmode(){
	return this->drawmode;
}

string SceneGraph::getShading(){
	return this->shading;
}

string SceneGraph::getCullface(){
	return this->cullface;
}

string SceneGraph::getCullorder(){
	return this->cullorder;
}

string SceneGraph::getInitialCamera(){
	return this->initialCamera;
}

map<string, Camera*>* SceneGraph::getCameras(){
	return this->cameras;
}

string SceneGraph::getDoublesided(){
	return this->doublesided;
}

string SceneGraph::getLocal(){
	return this->local;
}

string SceneGraph::getLightingEnabled(){
	return this->LightingEnabled;
}

float* SceneGraph::getLightingAmbientValues(){
	return this->LightingAmbientV;
}

map<string, Lighting*>* SceneGraph::getLights(){
	return this->lights;
}

map<string, Texture*>* SceneGraph::getTextures(){
	return this->textures;
}

map<string, LinearAnimation*>* SceneGraph::getAnimations(){
	return this->animations;
}

map<string, Appearence*>* SceneGraph::getAppearences(){
	return this->appearences;
}

string SceneGraph::getRootid(){
	return this->rootid;
}

map<string, GraphNode*>* SceneGraph::getGraphnodes(){
	return this->graphNodes;
}

int *SceneGraph::getDrawModeChoice(){
	return &drawModeChoice;
}

int *SceneGraph::getActualCamera(){
	return &actualCamera;
}

void SceneGraph::setActualCamera( int num ){
	this->actualCamera = num;
}

void SceneGraph::createBoard(){
	this->board = new Board();
}

Board* SceneGraph::getBoard(){
	return this->board;
}

TextObject* SceneGraph::getPainter(){
	return this->text;
}

int *SceneGraph::getActualTheme(){
	return &actualTheme;
}

void SceneGraph::setActualTheme( int theme ){
	this->actualTheme = theme;
}

void SceneGraph::updateTheme(){
	char number[2];
	number[0] = (char)((*this->getActualTheme()+1)+48);
	number[1] = '\0';

	char *backApp = strdup( "ap_backBackground" );
	char *leftApp = strdup( "ap_leftBackground" );
	char *bottomApp = strdup( "ap_bottomBackground" );
	char *rightApp = strdup( "ap_rightBackground" );
	char *topApp = strdup( "ap_topBackground" );
	char *frontApp = strdup( "ap_frontBackground" );

	strcat( backApp, number );
	strcat( leftApp, number );
	strcat( bottomApp, number );
	strcat( rightApp, number );
	strcat( topApp, number );
	strcat( frontApp, number );

	this->graphNodes->at( "backBackground" )->setAppRefId(backApp);
	this->graphNodes->at( "leftBackground" )->setAppRefId(leftApp);
	this->graphNodes->at( "bottomBackground" )->setAppRefId(bottomApp);
	this->graphNodes->at( "rightBackground" )->setAppRefId(rightApp);
	this->graphNodes->at( "topBackground" )->setAppRefId(topApp);
	this->graphNodes->at( "frontBackground" )->setAppRefId(frontApp);
}

SceneGraph::~SceneGraph(){

};

int ** SceneGraph::getLogicalBoard(){
	int ** logical = (int **)malloc(sizeof(int *) * 8);
	for(int i=0; i<8; i++) logical[i] = (int *)malloc(sizeof(int) * 8);

	for(int i=0; i<8; i++) memcpy( logical[i], this->getBoard()->getBoard()[i], sizeof(int)*8);

	return logical;
}

int ** SceneGraph::getAppearenceBoard(){
	int ** appearence = (int **)malloc(sizeof(int *) * 8);
	for(int i=0; i<8; i++) appearence[i] = (int *)malloc(sizeof(int) * 8);

	for(int i=0; i<8; i++) memcpy( appearence[i], this->getBoard()->getAppBoard()[i], sizeof(int)*8);

	return appearence;
}

void SceneGraph::setBothBoards( int **logical, int **appearence ){
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			this->board->setAppBoardAt(j, i, appearence[j][i]);
			this->board->setBoardAt(i, j, logical[i][j]);
		}
	}
}