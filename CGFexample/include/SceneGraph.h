#ifndef _SCENEGRAPH_H_
#define _SCENEGRAPH_H_

#include <string>
#include <vector>

#include "Camera.h"
#include "PerspectiveCamera.h"
#include "OrthogonalCamera.h"
#include "Lighting.h"
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
		void addLightingValues( char *doublesided, char *local, char *lightingEnabled, char *lightingAmbient, float lightingAmbientX, float lightingAmbientY, float lightingAmbientZ, float lightingAmbientAlfa);
		
		void addCamera( Camera *camera );
		// OLD STUFF //
		// void addPerspectiveCameras( vector<PerspectiveCamera> &cameras );
		// void addOrthogonalCameras( vector<OrthogonalCamera> &cameras );
		//void addLights( vector<Lighting> &lights );
		void addOmniLights( vector<OmniLight> &lights );
		void addSpotLights( vector<SpotLight> &lights );
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
		// OLD STUFF //
		// vector<Camera> cameras;
		// vector<PerspectiveCamera> perspectiveCameras;
		// vector<OrthogonalCamera> orthogonalCameras;

		// Lighting Values //
		string *doublesided;
		string *local;
		string *lightingEnabled;
		string *lightingAmbient;
		float lightingAmbientX, lightingAmbientY, lightingAmbientZ, lightingAmbientAlfa;
		//vector<Lighting> lights;
		vector<OmniLight> omniLights;
		vector<SpotLight> spotLights;

		// Texture Values //
		vector<Texture> textures;

		// Appearence Values //
		vector<Appearence> appearences;

		// Graph and Node Values //
};		//string *rootid;

#endif