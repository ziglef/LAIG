#include "../include/TPinterface.h"
#include "../include/YafScene.h"

void TPinterface::processKeyboard(unsigned char key, int x, int y){

}

void TPinterface::initGUI()
{

	count = 0;
	
	// Check CGFinterface.h and GLUI documentation for the types of controls available
	GLUI_Panel *lightsPanel= addPanel( "Lights", 1 );
	for( map<string, Lighting*>::iterator it = sg->getLights()->begin(); it != sg->getLights()->end(); it++){
		if( count == 0 )
			it->second->setToogled(1);
		else
			it->second->setToogled(0);
		addCheckboxToPanel(lightsPanel, (char*)it->second->getID().c_str() ,it->second->getToogled(), count );	
		count++;
	}
	
	addColumn();
	GLUI_Panel *camerasPanel = addPanel( "Cameras", 1 );
	cameras = addRadioGroupToPanel( camerasPanel, sg->getActualCamera(), 11 );
	for( map<string, Camera*>::iterator it = sg->getCameras()->begin(); it != sg->getCameras()->end(); it++){
		addRadioButtonToGroup( cameras, (char*)it->second->getID().c_str() );	
		count++;
	}

	addColumn();
	GLUI_Panel *drawmodePanels = addPanel("Draw Mode",1);
	drawmode = addRadioGroupToPanel( drawmodePanels, sg->getDrawModeChoice(), 20 );
	addRadioButtonToGroup( drawmode, "Fill" );
	addRadioButtonToGroup( drawmode, "Line" );
	addRadioButtonToGroup( drawmode, "Point" );
	*(sg->getDrawModeChoice()) = 0;
	
}

void TPinterface::processGUI(GLUI_Control *ctrl){

}

