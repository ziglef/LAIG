#include <iostream>
#include <exception>

#include "../include/XMLscene.h"
#include "../include/SceneGraph.h"
#include "../include/CGF/CGFapplication.h"
#include "../include/YafScene.h"

using std::cout;
using std::exception;

int main(int argc, char* argv[]) {

	bool debug = false;
	int debugOption = 0;
	char f[256];

	printf("Filename? ");
	scanf("%s", f);

	printf("Would you like to run the DEBUG profile? ( 1/0 )\n");
	scanf("%d", &debugOption);

	if(debugOption)
		debug = true;
	else
		debug = false;



	try {
		CGFapplication app = CGFapplication();
		app.init(&argc, argv);
		XMLScene *GraphScene = new XMLScene(f, debug);
		app.setScene( new YafScene( GraphScene->getSG()) );
		app.setInterface(new CGFinterface());
		app.run();
	}
	catch(GLexception& ex) {
		cout << "Error: " << ex.what();
		return -1;
	}
	catch(exception& ex) {
		cout << "Unexpected error: " << ex.what();
		return -1;
	}

	return 0;
}
