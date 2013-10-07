#ifndef _XMLSCENE_H_
#define _XMLSCENE_H_

#include "tinyxml.h"
#include "SceneGraph.h"
#include <cmath>

#define PI 3.14159265358979323846

#define DEG2RAD(x) x*PI/180

class XMLScene
{
public:
	XMLScene( char *filename, bool debug );
	~XMLScene();

	static TiXmlElement *findChildByAttribute( TiXmlElement *parent,const char * attr, const char *val );
	//float** MultiplyMatrix( float matrixA[4][4], float matrixB[4][4] );
	
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
		TiXmlElement* orthogonalCamera;		// Orthogonal Cameras //
		TiXmlElement* perspectiveCamera;	// Perspective Cameras //

	// Scene Lightning //
	TiXmlElement* lighting;
		TiXmlElement* omniLighting;	// Omnidirection Lightning //
		TiXmlElement* spotLighting;	// Spot Lightning //

	// Scene Textures //
	TiXmlElement* textures;
		TiXmlElement* textureTextures;	// Scene Texture (Single Instance) //

	// Scene Appearances //
	TiXmlElement* appearances;
		TiXmlElement* appearanceAppearances; // Scene Appearance (Single Instance) //

	// Scene Graph //
	TiXmlElement* sceneGraph;
		TiXmlElement* nodeGraph;								// Graph Node //
			TiXmlElement* transformsNodeGraph;					// Node Transformation //
				TiXmlElement* translateTransformsNodeGraph;		// Node Transformation Translation //
				TiXmlElement* scaleTransformsNodeGraph;			// Node Transformation Scale //
				TiXmlElement* rotateTransformsNodeGraph;		// Node Transformation Rotate //
				TiXmlElement* appearanceRefNodeGraph;			// Appearance Referecene //
			TiXmlElement* childrenNodeGraph;					// Node Children //
				TiXmlElement* noderefChildrenNodeGraph;			// Node Children Refernce //
				TiXmlElement* rectangleChildrenNodeGraph;		// Node Rectangle Primitive //
				TiXmlElement* triangleChildrenNodeGraph;		// Node Triangle Primitive //
				TiXmlElement* cylinderChildrenNodeGraph;		// Node Cylinder Primitive //
				TiXmlElement* sphereChildrenNodeGraph;		    // Node Sphere Primitive //
				TiXmlElement* torusChildrenNodeGraph;		    // Node Torus Primitive //
};

#endif