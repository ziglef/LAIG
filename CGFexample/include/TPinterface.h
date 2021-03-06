#ifndef TPinterface_H
#define TPinterface_H

#include <stack>
#include "CGFinterface.h"
#include "YafScene.h"
#pragma comment(lib, "Ws2_32.lib")

class TPinterface: public CGFinterface {

	GLUI_RadioGroup *lights;
	GLUI_RadioGroup *cameras;
	GLUI_RadioGroup *drawmode;
	GLUI_RadioGroup *themes;
	
	private:
		bool isPlayingMovie;
		int gameMode;
		int dificulty;
		int turn;
		int playerTurn;
		int checkBoardForPieces( int pieceType );
		void makeCompPlay( int mode );

	public:
		TPinterface( SceneGraph *sg) : CGFinterface(){
			this->sg = sg;
		};

		virtual void initGUI();
		virtual void processGUI(GLUI_Control *ctrl);
		virtual void processKeyboard(unsigned char key, int x, int y);
		virtual void processMouse(int button, int state, int x, int y);	
		void performPicking(int x, int y);
		void processHits(GLint hits, GLuint buffer[]);
		bool socketConnect();
		void envia(char *s, int len);
		void recebe(char *ans);
		void quit();

		int count;

		void doDebug();

	protected:
		SceneGraph *sg;
};


#endif
