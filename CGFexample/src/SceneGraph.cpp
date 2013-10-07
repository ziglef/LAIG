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
}

void SceneGraph::setInitialCamera( char *initCamera){
	this->initialCamera = new string( initCamera );
}


void SceneGraph::addCamera( Camera *camera ){
	this->cameras->insert( std::pair<string, Camera*>(camera->getID(), camera) );
}

void SceneGraph::addLight( Lightning *light ){
	this->lights->insert( std::pair<string, Lightning*>(light->getID(), light) );
}

void SceneGraph::addLightningValues( char *doublesided, char *local, char *LightningEnabled, char *LightningAmbient, float LightningAmbientX, float LightningAmbientY, float LightningAmbientZ, float LightningAmbientAlfa){
	this->LightningAmbientX = LightningAmbientX;
	this->LightningAmbientY = LightningAmbientY;
	this->LightningAmbientZ = LightningAmbientZ;
	this->LightningAmbientAlfa = LightningAmbientAlfa;
	
	this->doublesided = new string( doublesided );
	this->local = new string( local );
	this->LightningEnabled = new string( LightningEnabled );
	this->LightningAmbient = new string( LightningAmbient );
}

void SceneGraph::addTextures( vector<Texture> &textures ){
	this->textures = textures;
}

void SceneGraph::addAppearences( vector<Appearence> &appearences ){
	this->appearences = appearences;
}

SceneGraph::~SceneGraph(){

};
