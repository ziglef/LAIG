#include "../include/GraphNode.h"

GraphNode::GraphNode( char *id, char *appRefId, vector<string> &nodeRefIdVector, bool hasDL ){
	this->id = id;
	this->appRefId = appRefId;
	this->nodeRefIdVector = nodeRefIdVector;
	this->DL = hasDL;
	this->displayList = 0;
}

GraphNode::GraphNode( char *id, vector<string> &nodeRefIdVector, bool hasDL ){
	this->id = id;
	this->appRefId = "";
	this->nodeRefIdVector = nodeRefIdVector;
	this->DL = hasDL;
	this->displayList = 0;
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

string GraphNode::getAppRefId(){
	return this->appRefId;
}

string GraphNode::getID(){
	return this->id;
}

bool GraphNode::hasDL(){
	return this->DL;
}

void GraphNode::setDL( GLuint DL ){
	this->displayList = DL;
}

GLuint GraphNode::getDL(){
	return this->displayList;
}

GraphNode::~GraphNode(){

}