#ifndef _GRAPHNODE_H_
#define _GRAPHNODE_H_

#include <string>
#include <vector>

using std::string;
using std::vector;

class GraphNode{
	public:
		GraphNode( char *id, char *appRefId, vector<string> &nodeRefIdVector, float translate[4][4], float scale[4][4], float rotate[4][4] );
		~GraphNode();

	protected:
		string id;
		string appRefId;
		vector<string> nodeRefIdVector;
		vector<Primitive> primitives;
		float translate[4][4];
		float scale[4][4];
	    float rotate[4][4];
};

#endif