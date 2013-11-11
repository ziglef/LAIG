#include "../include/Vehicle.h"

Vehicle::Vehicle(){

	GLfloat aux[512][3];
	FILE *f = fopen("teapot.bpt", "r");

	for(int i=0; i<512; ++i) fscanf(f, "%f %f %f", &(aux[i][0]), &(aux[i][1]), &(aux[i][2]));
	fclose(f);

	std::vector<GLfloat**> pointsVector;

	for(int j=0; j<32; j++){
		GLfloat **ctrlpoints = (GLfloat**)malloc(sizeof(GLfloat*)*16);
		for(int i=0; i<16; i++){
			ctrlpoints[i] = (GLfloat*)malloc(sizeof(GLfloat)*3);
			ctrlpoints[i][0] = aux[i+(j*16)][0];
			ctrlpoints[i][1] = aux[i+(j*16)][1];
			ctrlpoints[i][2] = aux[i+(j*16)][2];
		}
		pointsVector.push_back(ctrlpoints);
	}
	/*
	for(int i=0; i<32; i++){
		printf("Point %d:\n", i);
		for(int j=0; j<16; j++){
			printf(" %f %f %f \n", pointsVector[i][j][0], pointsVector[i][j][1], pointsVector[i][j][2]);
		}
	}
	*/
	for(int i=0; i<32; i++){
		this->patch.push_back(new Patch( 4, 5, 5, "fill", 16, pointsVector[i] ));
	}
		
}

Vehicle::~Vehicle(){

}

void Vehicle::draw(){
	for(int i=0; i<32; i++){
		glPushMatrix();
		 this->patch[i]->draw();
		glPopMatrix();
	}
}