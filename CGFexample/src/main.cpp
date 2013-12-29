#include <iostream>
#include <exception>

#include <time.h>

#include "../include/XMLscene.h"
#include "../include/SceneGraph.h"
#include "../include/CGF/CGFapplication.h"
#include "../include/YafScene.h"
#include "../include/TPinterface.h"

using std::cout;
using std::exception;

int main(int argc, char* argv[]) {

	bool debug = false;
	int debugOption = 0;
	srand( time(NULL) );

	printf("Filename? ");
	//scanf("%s", f);

	printf("Would you like to run the DEBUG profile? ( 1/0 )\n");
	//scanf("%d", &debugOption);
	debugOption = 1;
	
	if(debugOption)
		debug = true;
	else
		debug = false;

	try {
		CGFapplication app = CGFapplication();
		app.init(&argc, argv);
		XMLScene *GraphScene = new XMLScene("boardGame2.yaf", debug);
		app.setScene( new YafScene( GraphScene->getSG()) );
		app.setInterface( new TPinterface( GraphScene->getSG()) );
		app.run();
	}
	catch(GLexception& ex) {
		cout << "Error: " << ex.what();
		getchar();getchar();
		return -1;
	}
	catch(exception& ex) {
		cout << "Unexpected error: " << ex.what();
		getchar();getchar();
		return -1;
	}
	return 0;
}
