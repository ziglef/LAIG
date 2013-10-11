#include "../include/TPinterface.h"
#include "../include/YafScene.h"

TPinterface::TPinterface()
{
	testVar=0;
}

void TPinterface::processKeyboard(unsigned char key, int x, int y){

}

void TPinterface::initGUI()
{
	// Check CGFinterface.h and GLUI documentation for the types of controls available
	GLUI_Panel *varPanel= addPanel("Lights", 1);
	
	// You could also pass a reference to a variable from the scene class, if public
	addSpinnerToPanel(varPanel, "Val 2(scene)", 2, &testVar, 2);

	GLUI_Panel *luzes = addPanel("Luzes",1);
	addCheckboxToPanel(luzes,"Luz 1", &testVar,0);
	
	
	addColumn();
	GLUI_Panel *relogio = addPanel("Relogio",1);
	addButtonToPanel(relogio,"Pausar/Reniciar",5);

	addColumn();
	GLUI_Panel *texturas = addPanel("Texturas", 1);
	listbox = addListboxToPanel(texturas, "",  &testVar, 6);
	listbox->add_item(7, "Textura 1");
	listbox->add_item(8, "Textura 2");

	
	addSeparatorToPanel(texturas);
	radiobutons = addRadioGroupToPanel(texturas,  &testVar, 9);
	addRadioButtonToGroup(radiobutons, "Texturas");
	addRadioButtonToGroup(radiobutons, "Wireframe");
	
}

void TPinterface::processGUI(GLUI_Control *ctrl)
{
	/*printf ("GUI control id: %d\n  ",ctrl->user_id);
	switch (ctrl->user_id)
	{
		case 0:
		{
			printf ("Light 0 Flag: %d\n",(((LightingScene*) scene)->light0Flag));
		};

		case 1:
		{
			printf ("Light 1 Flag: %d\n",(((LightingScene*) scene)->light1Flag));
			break;
		};

		case 2:
		{
			printf ("Light 2 Flag: %d\n",(((LightingScene*) scene)->light2Flag));
			break;
		};

		case 3:
		{
			printf ("Light 3 Flag: %d\n",(((LightingScene*) scene)->light3Flag));
			break;
		};

		case 4:
		{
			printf ("Wlight Flag: %d\n",(((LightingScene*) scene)->wLightFlag));
			break;
		};

		case 5:
		{
			if(((LightingScene*) scene)->clockPausedFlag == 0){
				((LightingScene*) scene)->clockPausedFlag = 1;
			}
			else{
				((LightingScene*) scene)->clockPausedFlag = 0;
			}
			break;
		};

		case 6:
		{
			printf ("Robot Texture Flag: %d\n", (((LightingScene*)scene)->robotTexFlag));

			};
		break;

		case 9:
			printf("Wire Frame Flag: %d\n", (((LightingScene*)scene)->wireFrameFlag));
			break;
	};*/
}

