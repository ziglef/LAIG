#ifndef _PERSPECTIVECAMERA_H
#define _PERSPECTIVECAMERA_H

#include "Camera.h"
#include "CGFscene.h"

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
		
			for(int i=0; i<3; i++){
				this->position[i] = pos[i];
				this->target[i] = target[i];
			}
		
		};
		void applyView();
		void updateProjectMatrix( int width, int height );
		~PerspectiveCamera();
		string getType();
		string getID();

	protected:
		float angle;
};

#endif