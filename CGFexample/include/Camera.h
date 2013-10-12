#ifndef _CAMERA_H
#define _CAMERA_H

#include "CGF\CGFcamera.h"
#include <string>
using std::string;

class Camera : public CGFcamera{
	public:
		Camera() : CGFcamera(){};
		Camera(string id, float near, float far) : CGFcamera(){
			this->id = id;
			this->near = near;
			this->far = far;
		};
		~Camera();
		virtual string getType();
		virtual string getID();

	protected:
		string id;
		float near;
		float far;
};

#endif