#ifndef _XMLSCENE_H_
#define _XMLSCENE_H_

#include "tinyxml.h"
#include "SceneGraph.h"
#include "Cylinder.h"
#include "Torus.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "CGF\CGFscene.h"
#include <cmath>

class XMLScene
{
public:
	XMLScene( char *filename, bool debug );
	~XMLScene();

	static TiXmlElement *findChildByAttribute( TiXmlElement *parent,const char * attr, const char *val );
	SceneGraph *getSG();
	
protected:

	// The main SceneGraph //
	SceneGraph *sg;

	// The Main .yaf Document //
	TiXmlDocument* doc;

	// The yaf Tag //
	TiXmlElement* yafElement;

	// Global Scene Variables //
	TiXmlElement* globals; 

	// Scene Cameras //
	TiXmlElement* cameras;
		TiXmlElement* cameraChilds;  // Cameras //

	// Scene Lightning //
	TiXmlElement* lighting;
		TiXmlElement* lights;	// Lights //

	// Scene Textures //
	TiXmlElement* textures;
		TiXmlElement* textureTextures;	// Scene Texture (Single Instance) //

	// Scene Appearances //
	TiXmlElement* appearances;
		TiXmlElement* appearanceAppearances; // Scene Appearance (Single Instance) //

	// Scene Animations <- NEW -> //
	TiXmlElement* animations;
		TiXmlElement* animationsAnimation;   // Scene Animation (Single Instance) //

	// Scene Graph //
	TiXmlElement* sceneGraph;
		TiXmlElement* nodeGraph;								// Graph Node //
			TiXmlElement* transformsNodeGraph;					// Node Transformation //
				TiXmlElement* transformsChildNodeGraph;         // Tranformations //
				TiXmlElement* appearanceRefNodeGraph;			// Appearance Referecene //
				TiXmlElement* animationRefNodeGraph;			// Animation <- NEW -> //
				TiXmlElement* planePartsNodeGraph;				// Plane <- NEW -> //
				TiXmlElement* patchNodeGraph;					// Patch <- NEW -> //
					TiXmlElement* controlpointNodeGraph;		// Control Point <- NEW -> //
				TiXmlElement* vehicleNodeGraph;					// Vehicle <- NEW -> //
				TiXmlElement* waterlineNodeGraph;				// Water Line <- NEW -> //
			TiXmlElement* childrenNodeGraph;					// Node Children //
				TiXmlElement* noderefChildrenNodeGraph;			// Node Children Reference //
				TiXmlElement* rectangleChildrenNodeGraph;		// Node Rectangle Primitive //
				TiXmlElement* triangleChildrenNodeGraph;		// Node Triangle Primitive //
				TiXmlElement* cylinderChildrenNodeGraph;		// Node Cylinder Primitive //
				TiXmlElement* sphereChildrenNodeGraph;		    // Node Sphere Primitive //
				TiXmlElement* torusChildrenNodeGraph;		    // Node Torus Primitive //
};

#endif