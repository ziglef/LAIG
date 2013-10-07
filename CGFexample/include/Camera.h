#ifndef _CAMERA_H
#define _CAMERA_H

#include <string>
using std::string;

class Camera{
	public:
		Camera();
		~Camera();
		virtual string getType()=0;

	protected:
		string *id;
		float near;
		float far;
};

#endif