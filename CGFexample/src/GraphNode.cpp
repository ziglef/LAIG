#include "../include/GraphNode.h"

GraphNode::GraphNode( char *id, char *appRefId, vector<string> &nodeRefIdVector, float translate[4][4], float scale[4][4], float rotate[4][4] ){
	this->id = id;
	this->appRefId = appRefId;

	this->nodeRefIdVector = nodeRefIdVector;

	for( int i=0; i < 4; i++ )
		for( int j=0; j < 4; j++)
			this->translate[i][j] = translate[i][j];

	for( int i=0; i < 4; i++ )
		for( int j=0; j < 4; j++)
			this->scale[i][j] = scale[i][j];

	for( int i=0; i < 4; i++ )
		for( int j=0; j < 4; j++)
			this->rotate[i][j] = rotate[i][j];

}

GraphNode::~GraphNode(){

}