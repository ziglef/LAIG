#ifndef _SCENEGRAPH_H_
#define _SCENEGRAPH_H_

#include <string>
#include <vector>

#include "Camera.h"
#include "PerspectiveCamera.h"
#include "OrthogonalCamera.h"
#include "Lightning.h"
#include "OmniLight.h"
#include "SpotLight.h"
#include "Texture.h"
#include "Appearence.h"
#include "GraphNode.h"
#include <map>

using namespace std;

class SceneGraph {
	public:
		// Constructor With Global Values //
		SceneGraph( float bgX, float bgY, float bgZ, float bgA, char *drawmode, char *shading, char *cullface, char *cullorder );
		~SceneGraph();

		// Sets initial camera //
		void setInitialCamera( char *initCamera );

		// Sets lightning initial values //
		void addLightningValues( char *doublesided, char *local, char *LightningEnabled, char *LightningAmbient, float LightningAmbientX, float LightningAmbientY, float LightningAmbientZ, float LightningAmbientAlfa);
		
		// Adds cameras to the map //
		void addCamera( Camera *camera );

		void addLight( Lightning *light );

		void addTextures( vector<Texture> &textures );
		void addAppearences( vector<Appearence> &appearences );
		//void addGraphNodes();

	protected:
		// Global Values //
		float bgX, bgY, bgZ, bgA;
		string *drawmode;
		string *shading;
		string *cullface;
		string *cullorder;
		
		// Camera Values //
		string *initialCamera;
		map<string, Camera*> *cameras;

		// Lightning Values //
		string *doublesided;
		string *local;
		string *LightningEnabled;
		string *LightningAmbient;
		float LightningAmbientX, LightningAmbientY, LightningAmbientZ, LightningAmbientAlfa;
		map<string, Lightning*> *lights;

		// Texture Values //
		vector<Texture> textures;

		// Appearence Values //
		vector<Appearence> appearences;

		// Graph and Node Values //
};		//string *rootid;

#endif