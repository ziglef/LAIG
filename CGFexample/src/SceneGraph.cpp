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

SceneGraph::~SceneGraph(){

};
