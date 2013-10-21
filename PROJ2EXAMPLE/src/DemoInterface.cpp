#include "DemoInterface.h"
#include "DemoScene.h"
#include "DemoShader.h"

DemoInterface::DemoInterface()
{
}


void DemoInterface::processKeyboard(unsigned char key, int x, int y)
{
	// Uncomment below if you would like to process the default keys (e.g. 's' for snapshot, 'Esc' for exiting, ...)
	CGFinterface::processKeyboard(key, x, y);
}

void DemoInterface::initGUI()
{
	// Check CGFinterface.h and GLUI documentation for the types of controls available
	GLUI_Panel *varPanel= addPanel("Teapot Shader", 1);
	addSpinnerToPanel(varPanel, "normScale", 2,NULL, 1);
	
	addColumn();

	varPanel= addPanel("Display List", 1);
	addCheckboxToPanel(varPanel, "Use", &(((DemoScene*) scene)->myDLObj->usingDL), 2);

	addColumn();
	
	varPanel= addPanel("Animations", 1);
	addButtonToPanel(varPanel, "Reset", 3);

	addColumn();

	addCheckbox( "Wireframe", &(((DemoScene*) scene)->wireframe), 4);
}

void DemoInterface::processGUI(GLUI_Control *ctrl)
{
	switch (ctrl->user_id)
	{
		case 1:  
		{
			((DemoShader *)((DemoScene*) scene)->demoshader)->normScale=ctrl->float_val;
			break;
		};
		case 3:
		{
			((DemoScene*) scene)->myIncAnimObj->reset();
			((DemoScene*) scene)->myTimeAnimObj->reset();
			
			break;
		};
	};
}

