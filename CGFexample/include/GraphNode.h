#ifndef _GRAPHNODE_H_
#define _GRAPHNODE_H_

#include <string>
#include <vector>

using std::string;
using std::vector;

#include "Primitive.h"

class GraphNode{
	public:
		GraphNode( char *id, char *appRefId, vector<string> &nodeRefIdVector );
		~GraphNode();

	protected:
		string id;
		string appRefId;
		vector<string> nodeRefIdVector;
		float transformationMatrix[16];
};

#endif