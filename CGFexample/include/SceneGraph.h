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
#include "Board.h"
#include "TextObject.h"
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
		void addLightingValues( char *doublesided, char *local, char *LightingEnabled, float *LightingAmbientV );
		
		// Adds cameras to the map //
		void addCamera( Camera *camera );

		void addLight( Lighting *light );

		void addTexture( Texture *texture );
		void addAnimation( LinearAnimation *animation );
		void addAppearence( Appearence *appearence );
		void setRootId( char *rootId );
		void addGraphNode( GraphNode *graphNode );

		// Getters for the protected values //
		float getbgx();
		float getbgy();
		float getbgz();
		float getbga();
		string getDrawmode();
		string getShading();
		string getCullface();
		string getCullorder();

		string getInitialCamera();
		map<string, Camera*> *getCameras();

		string getDoublesided();
		string getLocal();
		string getLightingEnabled();
		float* getLightingAmbientValues();
		map<string, Lighting*> *getLights();

		map<string, Texture*> *getTextures();

		map<string, Appearence*> *getAppearences();

		map<string, LinearAnimation*> *getAnimations();

		string getRootid();
		map<string, GraphNode*> *getGraphnodes();

		int *getDrawModeChoice();
		void setDrawModeChoice( int drawmode );
		int *getActualCamera();
		void setActualCamera( int num );

		void createBoard();
		Board* getBoard();

		TextObject* getText();


	protected:
		// Global Values //
		float bgX, bgY, bgZ, bgA;
		string drawmode;
		string shading;
		string cullface;
		string cullorder;
		
		// Camera Values //
		string initialCamera;
		map<string, Camera*> *cameras;

		// Lighting Values //
		string doublesided;
		string local;
		string LightingEnabled;
		float LightingAmbientV[4];
		map<string, Lighting*> *lights;

		// Texture Values //
		map<string, Texture*> *textures;

		// Animation Values //
		map<string, LinearAnimation*> *animations;

		// Appearence Values //
		map<string, Appearence*> *appearences;

		// Graph Nodes //
		string rootid;
		map<string, GraphNode*> *graphNodes;

		int drawModeChoice;
		int actualCamera;

		Board *board;
		TextObject *text;

	friend class YafScene;
};

#endif