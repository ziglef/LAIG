#ifndef _GRAPHNODE_H_
#define _GRAPHNODE_H_

#include <string>
#include <vector>

using std::string;
using std::vector;

class GraphNode{
	public:
		GraphNode();
		~GraphNode();

	protected:
		string *id;
		string *appRefId;
		string *translate;
		float translateX, translateY, translateZ;
		string *scale;
		float scaleX, scaleY, scaleZ;
		string *rotateAxis;
	    float rotateAngle;
		vector<string> nodeRefIds;
};

#endif