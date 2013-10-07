#include <iostream>
#include <exception>

#include "../include/XMLscene.h"
#include "../include/SceneGraph.h"

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

	XMLScene *GraphScene = new XMLScene(f, debug);

	fflush( stdin );
	getchar();

	return 0;
}
