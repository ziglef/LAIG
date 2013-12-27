#include "../include/TPinterface.h"
#include "../include/YafScene.h"
#include "../include/Parser.h"
#include <winsock2.h>
#include <iostream>

// buffer to be used to store the hits during picking
#define BUFSIZE 256
GLuint selectBuf[BUFSIZE];

#define IPADDRESS "127.0.0.1"
#define PORT 60070

SOCKET m_socket;

int wasfirstPointPicked = 0;
char points[4][2];

void TPinterface::processMouse(int button, int state, int x, int y) 
{
	CGFinterface::processMouse(button,state, x, y);

	// do picking on mouse press (GLUT_DOWN)
	// this could be more elaborate, e.g. only performing picking when there is a click (DOWN followed by UP) on the same place
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		performPicking(x,y);
}

void TPinterface::performPicking(int x, int y) 
{
	// Sets the buffer to be used for selection and activate selection mode
	glSelectBuffer (BUFSIZE, selectBuf);
	glRenderMode(GL_SELECT);

	// Initialize the picking name stack
	glInitNames();

	// The process of picking manipulates the projection matrix
	// so we will be activating, saving and manipulating it
	glMatrixMode(GL_PROJECTION);

	//store current projmatrix to restore easily in the end with a pop
	glPushMatrix ();

	//get the actual projection matrix values on an array of our own to multiply with pick matrix later
	GLfloat projmat[16];
	glGetFloatv(GL_PROJECTION_MATRIX,projmat);

	// reset projection matrix
	glLoadIdentity();

	// get current viewport and use it as reference for 
	// setting a small picking window of 5x5 pixels around mouse coordinates for picking
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	// this is multiplied in the projection matrix
	gluPickMatrix ((GLdouble) x, (GLdouble) (CGFapplication::height - y), 5.0, 5.0, viewport);

	// multiply the projection matrix stored in our array to ensure same conditions as in normal render
	glMultMatrixf(projmat);

	// force scene drawing under this mode
	// only the names of objects that fall in the 5x5 window will actually be stored in the buffer
	scene->display();

	// restore original projection matrix
	glMatrixMode (GL_PROJECTION);
	glPopMatrix ();

	glFlush();

	// revert to render mode, get the picking results and process them
	GLint hits;
	hits = glRenderMode(GL_RENDER);
	processHits(hits, selectBuf);
}

void TPinterface::processHits (GLint hits, GLuint buffer[]) 
{
	GLuint *ptr = buffer;
	GLuint mindepth = 0xFFFFFFFF;
	GLuint *selected=NULL;
	GLuint nselected;

	// iterate over the list of hits, and choosing the one closer to the viewer (lower depth)
	for (int i=0;i<hits;i++) {
		int num = *ptr; ptr++;
		GLuint z1 = *ptr; ptr++;
		ptr++;
		if (z1 < mindepth && num>0) {
			mindepth = z1;
			selected = ptr;
			nselected=num;
		}
		for (int j=0; j < num; j++) 
			ptr++;
	}
	
	// if there were hits, the one selected is in "selected", and it consist of nselected "names" (integer ID's)
	if (selected!=NULL)
	{
		// this should be replaced by code handling the picked object's ID's (stored in "selected"), 
		// possibly invoking a method on the scene class and passing "selected" and "nselected"
		printf("Picked ID's: ");
		//for (int i=0; i<nselected; i++)
		printf("%d %d",selected[0], selected[1]);
		printf("\n");

		if( wasfirstPointPicked == 0 ){/*
			printf("Logical Board: \n");
			for(int i=0; i<8; i++){
				printf("Line %d: ", i+1);
				for(int j=0; j<8; j++){
					printf("%d ", sg->getBoard()->getBoardAt(i, j));
				}
				printf("\n");
			}

			printf("Appearence Board: \n");
			for(int i=0; i<8; i++){
				printf("Line %d: ", i+1);
				for(int j=0; j<8; j++){
					printf("%d ", sg->getBoard()->getAppBoardAt(i, j));
				}
				printf("\n");
			}
			*/
			char *answer = (char *)malloc(sizeof(char) * 256 );
			char *msg = possibleMoves( (int)selected[0], (int)selected[1] );
			envia(msg, strlen(msg));
			recebe(answer);
			int resultsLength;
			int *results = line2results( answer, &resultsLength );
			printf("Line: ");
			for(int i=0; i<resultsLength; i++)
				printf("%d ", results[i]);
			printf("\n");
			
			for(int i=0; i<resultsLength; i+=2){
<<<<<<< HEAD
				printf("Result %d \n", i );
				if(sg->getBoard()->getBoardAt(results[i]-1, results[i+1]-1) == 1){
					sg->getBoard()->setAppBoardAt(results[i+1]-1, results[i]-1, 4);
				}else{
					sg->getBoard()->setAppBoardAt(results[i+1]-1, results[i]-1, 3);
				}
=======
				if(sg->getBoard()->getBoardAt(results[i], results[i+1]) == 1)
					sg->getBoard()->setAppBoardAt(results[i], results[i+1], 4);
				else
					sg->getBoard()->setAppBoardAt(results[i], results[i+1], 3);
>>>>>>> no message
			}

			wasfirstPointPicked = 1;
		}else{
			// Verificar se o local onde o jogador clickou tem a cor verde na matrix de aparencias
				// Se tiver
					// Atualiza matriz logica
					// Faz animaçao da peça
				// Se nao tiver
					// Aviso de que a jogoada nao é possivel (Desenho de letras no ecra) / TextObject.
			// Faz reset da matriz de aparencias
			wasfirstPointPicked = 0;
		}
	}
	else
		printf("Nothing selected while picking \n");	
}

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
	socketConnect();
}

bool TPinterface::socketConnect(){// Initialize Winsock.
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != NO_ERROR)
		printf("Client: Error at WSAStartup().\n");
    else
        printf("Client: WSAStartup() is OK.\n");

	// Create a socket.
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_socket == INVALID_SOCKET) {
        printf("Client: socket() - Error at socket(): %ld\n", WSAGetLastError());
        WSACleanup();
        return false;
    }
	else
       printf("Client: socket() is OK.\n");

    // Connect to a server.
    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    // Just test using the localhost, you can try other IP address
    clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientService.sin_port = htons(60070);

    if (connect(m_socket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
        printf("Client: connect() - Failed to connect.\n");
        WSACleanup();
        return false;
    }
    else {
       printf("Client: connect() is OK.\n");
       printf("Client: Can start sending and receiving data...\n");
    }

    // Send and receive data.
	printf("Connected\n");
	return true;
}

void TPinterface::envia(char *s, int len) {
	int bytesSent = send(m_socket, s, len, 0);
	if(bytesSent == SOCKET_ERROR)
		printf("Client: send() error %ld.\n", WSAGetLastError());
}

void TPinterface::recebe(char *ans) {
	int bytesRecv = SOCKET_ERROR;
	int pos = 0;
	while (true) {
		recv(m_socket, &ans[pos], 1, 0);
		if (ans[pos] == '\n')
			break;
		pos++;
	}
	ans[pos] = 0;
	cout << "prolog answered: " << ans << endl;
}

void TPinterface::quit() {
	cout << "Asking prolog to quit" << endl;
	char buff[] = "quit.\n";
	envia(buff, 6);
	char ans[128];
	recebe(ans);
}

void TPinterface::processGUI(GLUI_Control *ctrl){

}

