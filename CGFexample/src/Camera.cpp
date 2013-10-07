#include "../include/Camera.h"

Camera::Camera(){

}

Camera::Camera(string _id, float _near, float _far){
			this->id=_id;
			this->near=_near;
			this->far=_far;
}

Camera::~Camera(){

}

string Camera::getType(){
	return "";
}

string Camera::getID(){
	return "";
}