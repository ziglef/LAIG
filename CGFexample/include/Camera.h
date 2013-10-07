#ifndef _CAMERA_H
#define _CAMERA_H

#include <string>
using std::string;

class Camera{
	public:
		Camera();
		Camera(string _id, float _near, float _far);
		~Camera();
		virtual string getType();
		virtual string getID();

	protected:
		string id;
		float near;
		float far;
};

#endif