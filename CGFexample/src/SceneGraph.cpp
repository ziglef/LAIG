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
}

void SceneGraph::setInitialCamera( char *initCamera){
	this->initialCamera = new string( initCamera );
}

void SceneGraph::addPerspectiveCameras( vector<PerspectiveCamera> &cameras ){
	this->perspectiveCameras = cameras;
}

void SceneGraph::addOrthogonalCameras( vector<OrthogonalCamera> &cameras ){
	this->orthogonalCameras = cameras;
}

void SceneGraph::addLightingValues( char *doublesided, char *local, char *lightingEnabled, char *lightingAmbient, float lightingAmbientX, float lightingAmbientY, float lightingAmbientZ, float lightingAmbientAlfa){
	this->lightingAmbientX = lightingAmbientX;
	this->lightingAmbientY = lightingAmbientY;
	this->lightingAmbientZ = lightingAmbientZ;
	this->lightingAmbientAlfa = lightingAmbientAlfa;
	
	this->doublesided = new string( doublesided );
	this->local = new string( local );
	this->lightingEnabled = new string( lightingEnabled );
	this->lightingAmbient = new string( lightingAmbient );
}

void SceneGraph::addOmniLights( vector<OmniLight> &lights ){
	this->omniLights = lights;
}

void SceneGraph::addSpotLights( vector<SpotLight> &lights ){
	this->spotLights = lights;
}

void SceneGraph::addTextures( vector<Texture> &textures ){
	this->textures = textures;
}

void SceneGraph::addAppearences( vector<Appearence> &appearences ){
	this->appearences = appearences;
}

SceneGraph::~SceneGraph(){

};
