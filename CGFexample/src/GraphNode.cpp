#include "../include/GraphNode.h"

GraphNode::GraphNode( char *id, char *appRefId, vector<string> &nodeRefIdVector ){
	this->id = id;
	this->appRefId = appRefId;
	this->nodeRefIdVector = nodeRefIdVector;
}

GraphNode::GraphNode( char *id, vector<string> &nodeRefIdVector ){
	this->id = id;
	this->appRefId = "";
	this->nodeRefIdVector = nodeRefIdVector;
}

float *GraphNode::getTransformationMatrix(){
	return &transformationMatrix[0];
}

void GraphNode::setPrimitives( vector<CGFobject*> primitives ){
	this->primitives = primitives;
}

vector<CGFobject*> GraphNode::getPrimitives(){
	return this->primitives;
}

vector<string> GraphNode::getNodeRefIdVector(){
	return this->nodeRefIdVector;
}

GraphNode::~GraphNode(){

}

string GraphNode::getID(){
	return this->id;
}