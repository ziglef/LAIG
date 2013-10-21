#ifndef DemoInterface_H
#define DemoInterface_H

#include "CGFinterface.h"

class DemoInterface: public CGFinterface {
	public:
		DemoInterface();

		virtual void initGUI();
		virtual void processGUI(GLUI_Control *ctrl);

		virtual void processKeyboard(unsigned char key, int x, int y);
};


#endif
