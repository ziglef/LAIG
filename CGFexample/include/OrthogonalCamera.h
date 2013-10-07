#ifndef _ORTHOGONALCAMERA_H
#define _ORTHOGONALCAMERA_H

#include "Camera.h"

class OrthogonalCamera : public Camera{
	public:
		OrthogonalCamera( char *id, float near, float far, float left, float right, float up, float bottom );
		~OrthogonalCamera();
		string getType();
		string getID();

	protected:
		float left;
		float right;
		float top;
		float bottom;
};

#endif