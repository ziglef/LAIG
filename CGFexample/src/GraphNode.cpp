#include "../include/GraphNode.h"

GraphNode::GraphNode( char *id, char *appRefId, vector<string> &nodeRefIdVector ){
	this->id = id;
	this->appRefId = appRefId;
	this->nodeRefIdVector = nodeRefIdVector;
}

float *GraphNode::getTransformationMatrix(){
	return &transformationMatrix[0];
}

GraphNode::~GraphNode(){

}