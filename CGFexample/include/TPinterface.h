#ifndef TPinterface_H
#define TPinterface_H

#include "CGFinterface.h"
#include "YafScene.h"

class TPinterface: public CGFinterface {

	GLUI_RadioGroup *lights;
	GLUI_RadioGroup *cameras;
	GLUI_RadioGroup *drawmode;
	public:
		TPinterface( SceneGraph *sg) : CGFinterface(){
			this->sg = sg;
		};

		virtual void initGUI();
		virtual void processGUI(GLUI_Control *ctrl);

		virtual void processKeyboard(unsigned char key, int x, int y);

		int count;

	protected:
		SceneGraph *sg;
};


#endif
