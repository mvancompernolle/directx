#include "System.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow )
{
	System* system;
	bool result;


	// Create the system object.
	system = new System;

	// Initialize and run the system object.
	if ( system->init() )
	{
		system->run();
	}

	// Shutdown and release the system object.
	system->shutDown();
	delete system;
	system = 0;

	return 0;
}