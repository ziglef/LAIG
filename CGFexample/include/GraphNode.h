#ifndef _GRAPHNODE_H_
#define _GRAPHNODE_H_

#include <string>
#include <vector>
#include "CGF\CGFobject.h"

using std::string;
using std::vector;

class GraphNode{
	public:
		GraphNode( char *id, char *appRefId, vector<string> &nodeRefIdVector );
		GraphNode( char *id, vector<string> &nodeRefIdVector );
		void setPrimitives( vector<CGFobject*> primitives );
		vector<CGFobject*> getPrimitives();
		float *getTransformationMatrix();
		vector<string> getNodeRefIdVector();
		~GraphNode();
		string getID();

	protected:
		string id;
		string appRefId;
		vector<string> nodeRefIdVector;
		vector<CGFobject*> primitives;
		float transformationMatrix[16];
};

#endif