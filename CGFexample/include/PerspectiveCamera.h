#ifndef _PERSPECTIVECAMERA_H
#define _PERSPECTIVECAMERA_H

#include "Camera.h"

class PerspectiveCamera : public Camera{
	public:
		PerspectiveCamera(
							char *id,
							float near,
							float far,
							float angle,
							float *pos,
							float *target ) : Camera ( id, near, far ){
			this->angle = angle;
			this->setX(pos[0]);
			this->setY(pos[1]);
			this->setZ(pos[2]);
			
			for(int i=0; i<3; i++) this->target[i] = target[i];
		
		};
		~PerspectiveCamera();
		string getType();
		string getID();

	protected:
		float angle;
};

#endif