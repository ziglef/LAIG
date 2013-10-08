#include "../include/SceneGraph.h"

SceneGraph::SceneGraph( float bgX, float bgY, float bgZ, float bgA, char *drawmode, char *shading, char *cullface, char *cullorder ){
	this->bgX = bgX;
	this->bgY = bgY;
	this->bgZ = bgZ;
	this->bgA = bgA;

	this->drawmode = new string( drawmode );
	this->shading = new string( shading );
	this->cullface = new string( cullface );
	this->cullorder = new string( cullorder );

	this->cameras = new map<string, Camera*>;
	this->lights = new map<string, Lighting*>;
	this->textures = new map<string, Texture*>;
	this->appearences = new map<string, Appearence*>;
	this->graphNodes = new map<string, GraphNode*>;
}

void SceneGraph::setInitialCamera( char *initCamera){
	this->initialCamera = new string( initCamera );
}


void SceneGraph::addCamera( Camera *camera ){
	this->cameras->insert( std::pair<string, Camera*>(camera->getID(), camera) );
}

void SceneGraph::addLight( Lighting *light ){
	this->lights->insert( std::pair<string, Lighting*>(light->getID(), light) );
}

void SceneGraph::addLightingValues( char *doublesided, char *local, char *LightingEnabled, char *LightingAmbient, float LightingAmbientX, float LightingAmbientY, float LightingAmbientZ, float LightingAmbientAlfa){
	this->LightingAmbientX = LightingAmbientX;
	this->LightingAmbientY = LightingAmbientY;
	this->LightingAmbientZ = LightingAmbientZ;
	this->LightingAmbientAlfa = LightingAmbientAlfa;
	
	this->doublesided = new string( doublesided );
	this->local = new string( local );
	this->LightingEnabled = new string( LightingEnabled );
	this->LightingAmbient = new string( LightingAmbient );
}

void SceneGraph::addTexture( Texture *texture ){
	this->textures->insert( std::pair<string, Texture *>(texture->getID(), texture) );
}

void SceneGraph::addAppearence( Appearence *appearence ){
	this->appearences->insert( std::pair<string, Appearence*>(appearence->getID(), appearence) );
}

void SceneGraph::setRootId( char *rootId ){
	this->rootid = rootid;
}

void SceneGraph::addGraphNode( GraphNode *graphNode ){
	this->graphNodes->insert( std::pair<string, GraphNode*>(graphNode->getID(), graphNode) );
}

map<string, Texture*>* SceneGraph::getTextures(){
	return this->textures;
}

SceneGraph::~SceneGraph(){

};
