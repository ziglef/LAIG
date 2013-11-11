#ifndef _GRAPHNODE_H_
#define _GRAPHNODE_H_

#include <string>
#include <vector>
#include "CGF\CGFobject.h"
#include "LinearAnimation.h"

using std::string;
using std::vector;

class GraphNode{
	public:
		GraphNode( char *id, char *appRefId, vector<string> &nodeRefIdVector, bool hasDL );
		GraphNode( char *id, vector<string> &nodeRefIdVector, bool hasDL );
		GraphNode( char *id, vector<string> &nodeRefIdVector, bool hasDL, char *animationRef );
		GraphNode( char *id, char *appRefId, vector<string> &nodeRefIdVector, bool hasDL, char *animationRef );
		void setPrimitives( vector<CGFobject*> primitives );
		vector<CGFobject*> getPrimitives();
		float *getTransformationMatrix();
		string getAppRefId();
		vector<string> getNodeRefIdVector();
		string getID();
		bool hasDL();
		void setDL( GLuint DL );
		GLuint getDL();
		bool hasAnimation();
		string getAnimationRef();
		~GraphNode();

	protected:
		string id;
		string appRefId;
		vector<string> nodeRefIdVector;
		vector<CGFobject*> primitives;
		float transformationMatrix[16];
		bool DL;
		GLuint displayList;
		string animationRef;
		bool anim;
	friend class YafScene;
};

#endif