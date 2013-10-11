#ifndef _ORTHOGONALCAMERA_H
#define _ORTHOGONALCAMERA_H

#include "Camera.h"
#include "CGFscene.h"

class OrthogonalCamera : public Camera{
	public:
		OrthogonalCamera(
							char *id,
							float near,
							float far,
							float left,
							float right,
							float top,
							float bottom 
							) : Camera( id, near, far ){
			this->left = left;
			this->right = right;
			this->top = top;
			this->bottom = bottom;
		};
		~OrthogonalCamera();
		void applyView();
		void updateProjectMatrix( int width, int height );
		string getType();
		string getID();

	protected:
		float left;
		float right;
		float top;
		float bottom;
};

#endif