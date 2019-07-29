#include "TheGameApp.h"
#include "CRT.h"

int main() {
	
	// allocation
	auto app = DBG_NEW TheGameApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	_CrtDumpMemoryLeaks();

	return 0;
}