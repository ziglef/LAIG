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

int gameOver = 0;
int wasfirstPointPicked = 0;
int playermoved = 1;
char points[4][2];
int *results;
int resultsLength;
int oldX, oldY;

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

int TPinterface::checkBoardForPieces( int pieceType ){
	int i,j;
	for(i=0; i<8; i++){
		for(j=0; j<8; j++){
			if( sg->getBoard()->getBoardAt(i, j) == pieceType ) break;
		}
		if( j != 8 ) break;
	}
	if( i != 8 ) return 1; else return 0;
}

void TPinterface::makeCompPlay( int mode ){
		if( gameMode != 3 ) turn = mode;

		char *answer;
		char *msg;

		int i;

		// Save the board //
		if(( turn == 1 ) && ( gameMode == 3 )){
			sg->pStack.push_back( sg->getLogicalBoard() );
			sg->pStack.push_back( sg->getAppearenceBoard() );
		}

		// First Comp Plays //
		int comp1HasPieces = checkBoardForPieces( turn );
		if( comp1HasPieces ){
			// Get a random piece //
			int compX, compY;
			do{
				i=0;
				resultsLength=-1;
				compX = rand()%8;
				compY = rand()%8;

				if( sg->getBoard()->getBoardAt( compX, compY ) == turn ){
					answer = (char *)malloc(sizeof(char) * 256 );
					msg = possibleMoves( compX+1, compY+1 );
					envia(msg, strlen(msg));
					recebe(answer);

					results = line2results( answer, &resultsLength );
			
					for(i=0; i<resultsLength; i+=2)
						if(sg->getBoard()->getBoardAt(results[i]-1, results[i+1]-1) != turn) break;

				}
			}while( i >= resultsLength );

			// Get new position //
			int newCompX, newCompY;
			do{
				free( answer );
				answer = (char *)malloc(sizeof(char) * 256 );
				msg = moveComputer( compX+1, compY+1, rand() );
				envia(msg, strlen(msg));
				recebe(answer);
				pair2variable( answer, &newCompX, &newCompY );
			}while( sg->getBoard()->getBoardAt( newCompX-1, newCompY-1 ) == turn );

			// Clear old position //
			sg->getBoard()->setBoardAt( compX, compY, 0 );
			// Check new position for points //
			if( sg->getBoard()->getBoardAt( newCompX-1, newCompY-1 ) != 0 && sg->getBoard()->getBoardAt( newCompX-1, newCompY-1 ) != turn ){
				if( turn == 1)
					sg->p1points += 1;
				if( turn == 2 )
					sg->p2points += 1;
			}
			// Set the new position //
			sg->getBoard()->setBoardAt( newCompX-1, newCompY-1, turn );
		}
		// Check Game Over //
		free( answer );
		answer = (char *)malloc(sizeof(char) * 256 );
		msg = endGame( sg->getBoard()->getBoard() );
		envia(msg, strlen(msg));
		recebe(answer);
			
		if(answer[0] == '0')
			gameOver = 0;
		else
			gameOver = 1;

		if( turn == 1 ) turn = 2; else turn = 1;
}

void TPinterface::processHits (GLint hits, GLuint buffer[]) 
{
	int i, j;

	GLuint *ptr = buffer;
	GLuint mindepth = 0xFFFFFFFF;
	GLuint *selected=NULL;
	GLuint nselected;

	// iterate over the list of hits, and choosing the one closer to the viewer (lower depth)
	for (i=0;i<hits;i++) {
		int num = *ptr; ptr++;
		GLuint z1 = *ptr; ptr++;
		ptr++;
		if (z1 < mindepth && num>0) {
			mindepth = z1;
			selected = ptr;
			nselected=num;
		}
		for (j=0; j < num; j++) 
			ptr++;
	}

	// If the player made a play, then get the new board
	if( playermoved && gameMode != 3 && playerTurn == 1 ){
		sg->pStack.push_back( sg->getLogicalBoard() );
		sg->pStack.push_back( sg->getAppearenceBoard() );
		playermoved = 0;
	}

	isPlayingMovie = sg->getPlayingMovie();

	// Comp vs Comp
	if( !gameOver && !isPlayingMovie && gameMode == 3 && dificulty != -1 ){
		makeCompPlay( 0 );
	} else if((selected!=NULL) && ( !gameOver ) && ( !isPlayingMovie ) && ( gameMode != -1 ) && ( dificulty != -1 )){
		// if there were hits, the one selected is in "selected", and it consist of nselected "names" (integer ID's)
		// this should be replaced by code handling the picked object's ID's (stored in "selected"), 
		// possibly invoking a method on the scene class and passing "selected" and "nselected"
		printf("Picked ID's: ");
		//for (int i=0; i<nselected; i++)
		printf("%d %d",selected[0], selected[1]);
		printf("\n");

		if(( gameMode == 2 ) && ( playerTurn == 1 )){
			makeCompPlay( 1 );
			playerTurn = 2;
		} else if( wasfirstPointPicked == 0 && sg->getBoard()->getBoardAt( selected[0]-1, selected[1]-1) == playerTurn ){	
			char *answer = (char *)malloc(sizeof(char) * 256 );
			char *msg = possibleMoves( (int)selected[0], (int)selected[1] );
			envia(msg, strlen(msg));
			recebe(answer);
			
			results = line2results( answer, &resultsLength );
			printf("Line: ");
			for(i=0; i<resultsLength; i++)
				printf("%d ", results[i]);
			printf("\n");
			
			for(i=0; i<resultsLength; i+=2){
				if(sg->getBoard()->getBoardAt(results[i]-1, results[i+1]-1) == playerTurn){
					sg->getBoard()->setAppBoardAt(results[i+1]-1, results[i]-1, 4);
				}else{
					sg->getBoard()->setAppBoardAt(results[i+1]-1, results[i]-1, 3);
				}
			}

			// DEBUG INFO //
			doDebug();

			oldX = selected[0];
			oldY = selected[1];
			wasfirstPointPicked = 1;
		}else{
			if( sg->getBoard()->getAppBoardAt( (int)selected[1]-1, (int)selected[0]-1 ) == 3 ){
				// Logical Board changes //
				// New piece //
				if( sg->getBoard()->getBoardAt( (int)selected[0]-1,(int)selected[1]-1 ) != 0 && sg->getBoard()->getBoardAt( (int)selected[0]-1, (int)selected[1]-1 ) != playerTurn ){
					if( playerTurn == 1)
						sg->p1points += 1;
					if( playerTurn == 2 )
						sg->p2points += 1;
				}
				sg->getBoard()->setBoardAt( (int)selected[0]-1, (int)selected[1]-1, playerTurn );

				// Old piece //
				sg->getBoard()->setBoardAt( oldX-1, oldY-1, 0 );

				// Set playermoved true //
				playermoved = 1;
			}

			// Appearence Board Changes //
			for(i=0; i<resultsLength; i+=2){
				if( sg->getBoard()->getAppBoardAt( oldY-1, oldX-1 ) == 1 )
					sg->getBoard()->setAppBoardAt(results[i+1]-1, results[i]-1, 0);
				else
					sg->getBoard()->setAppBoardAt(results[i+1]-1, results[i]-1, 1);
			}

			// Detects if game over! //
			char *answer = (char *)malloc(sizeof(char) * 256 );
			char *msg = endGame( sg->getBoard()->getBoard() );
			envia(msg, strlen(msg));
			recebe(answer);
			
			if(answer[0] == '0')
				gameOver = 0;
			else
				gameOver = 1;

			// If Player vs Comp //
			if( gameMode == 1 && playermoved ) makeCompPlay( 2 );

			if(( gameMode == 0 ) && ( playermoved ))
				if( playerTurn == 1 )
					playerTurn = 2;
				else
					playerTurn = 1;

			if( gameMode == 2 )
				if( playerTurn == 1 )
					playerTurn = 2;
				else
					playerTurn = 1;

			if( gameMode == 0 ) sg->setActualCamera( playerTurn );

			// End second step //
			wasfirstPointPicked = 0;
		}
	}

	if( gameOver ){
		sg->setGameOver(true);
		sg->endTime = glutGet(GLUT_ELAPSED_TIME);
	}
}

void TPinterface::processKeyboard(unsigned char key, int x, int y){

}

void TPinterface::initGUI()
{

	count = 0;
	isPlayingMovie = false;
	gameMode = -1;
	dificulty = -1;
	turn = 1;
	playerTurn = 1;

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
	cameras = addRadioGroupToPanel( camerasPanel, sg->getActualCamera(), 12 );
	addRadioButtonToGroup( cameras, "Free Movement Camera" );
	addRadioButtonToGroup( cameras, "White Player Camera" );
	addRadioButtonToGroup( cameras, "Black Player Camera" );
	addRadioButtonToGroup( cameras, "Sideview Camera" );
	addRadioButtonToGroup( cameras, "Overview Camera" );

	addColumn();
	GLUI_Panel *drawmodePanels = addPanel("Draw Mode",1);
	drawmode = addRadioGroupToPanel( drawmodePanels, sg->getDrawModeChoice(), 20 );
	addRadioButtonToGroup( drawmode, "Fill" );
	addRadioButtonToGroup( drawmode, "Line" );
	addRadioButtonToGroup( drawmode, "Point" );
	*(sg->getDrawModeChoice()) = 0;
	
	addColumn();
	GLUI_Panel *themesPanels = addPanel("Game Themes",1);
	themes = addRadioGroupToPanel( themesPanels, sg->getActualTheme(), 21);
	addRadioButtonToGroup( themes, "Chinese" );
	addRadioButtonToGroup( themes, "Florest" );
	addRadioButtonToGroup( themes, "Desert" );
	sg->setActualTheme(1);

	addColumn();
	GLUI_Panel *gameOptions = addPanel("Game Options", 1);
	// Game Mode Info:
		// -1 - Yet to be chosen
		// 0 - Player vs Player
		// 1 - Player vs Computer
		// 2 - Computer vs Player
		// 3 - Computer vs Computer
	GLUI_Listbox *GameModeListBox = addListboxToPanel( gameOptions, "Game Mode ", &(this->gameMode), 10 );
		GameModeListBox->add_item(-1, "Please select game mode");
		GameModeListBox->add_item(0, "Player vs Player");
		GameModeListBox->add_item(1, "Player vs Computer");
		GameModeListBox->add_item(2, "Computer vs Player");
		GameModeListBox->add_item(3, "Computer vs Computer");

	// Dificulty Info:
		// -1 - Yet to be chosen
		// 0 - Easy as Hell
		// 1 - Still really easy
		// 2 - Still Easy
	GLUI_Listbox *GameDificultyListBox = addListboxToPanel( gameOptions, "Dificulty       ", &(this->dificulty), 11 );
		GameDificultyListBox->add_item(-1, "Please select dificulty");
		GameDificultyListBox->add_item(0, "Easiest");
		GameDificultyListBox->add_item(1, "Easier");
		GameDificultyListBox->add_item(2, "Easy");

	addButtonToPanel(gameOptions, "Undo", 25);
	addButtonToPanel(gameOptions, "Play Movie", 26);

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

void TPinterface::doDebug(){

	int i,j;

	// DEBUG INFO //
	printf("\n ----- DEBUG INFO ----- ");
	printf("Game Boards:\n");
	printf("Logical Board: \n");
	for(i=0; i<8; i++){
		printf("Line %d: ", i+1);
		for(j=0; j<8; j++){
			printf("%d ", sg->getBoard()->getBoardAt(i, j));
		}
		printf("\n");
	}

	printf("Appearence Board: \n");
	for(i=0; i<8; i++){
		printf("Line %d: ", i+1);
		for(j=0; j<8; j++){
			printf("%d ", sg->getBoard()->getAppBoardAt(i, j));
		}
		printf("\n");
	}

	if( sg->pStack.size() > 0 ){
		printf("Top of the stack:\n");
		printf("Logical Board: \n");
		for(i=0; i<8; i++){
			printf("Line %d: ", i+1);
			for(j=0; j<8; j++){
				printf("%d ", sg->pStack[sg->pStack.size()-2][i][j]);
			}
			printf("\n");
		}

		printf("Appearence Board: \n");
		for(i=0; i<8; i++){
			printf("Line %d: ", i+1);
			for(j=0; j<8; j++){
				printf("%d ", sg->pStack[sg->pStack.size()-1][i][j]);
			}
			printf("\n");
		}
	} else {
		printf("No stack to print!\n");
	}

	printf(" ----- END OF DEBUG INFO ----- \n");
}

void TPinterface::processGUI(GLUI_Control *ctrl){
	switch( ctrl->user_id ){
		case 10:
			ctrl->disable();
			if( gameMode == 0 ) sg->setActualCamera( 1 );
			break;

		case 11:
			ctrl->disable();
			break;

		case 25:
			isPlayingMovie = sg->getPlayingMovie();
			if((sg->pStack.size() > 0) && (!isPlayingMovie) && (!gameOver)){
				doDebug();
				this->sg->setBothBoards( sg->pStack[sg->pStack.size()-2], sg->pStack[sg->pStack.size()-1] );
				sg->pStack.pop_back();
				sg->pStack.pop_back();
			}
			break;

		case 26:
			if(sg->pStack.size() > 0){
				isPlayingMovie = sg->getPlayingMovie();
				if( !isPlayingMovie ){
					isPlayingMovie = true;
					sg->setPlayingMovie( true );
				}
			}
			break;

		default: break;
	}
}