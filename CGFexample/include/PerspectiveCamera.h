#ifndef _PERSPECTIVECAMERA_H
#define _PERSPECTIVECAMERA_H

#include "Camera.h"

class PerspectiveCamera : public Camera{
	public:
		PerspectiveCamera( char *id, float near, float far, float angle, char *pos, float posX, float posY, float posZ, char *target, float targetX, float targetY, float targetZ );
		~PerspectiveCamera();
		string getType();
		string getID();

	protected:
		float angle;
		string *pos;
		float posX,posY,posZ;
		string *target;
		float targetX,targetY,targetZ;
};

#endif