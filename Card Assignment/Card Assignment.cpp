// Card Assignment.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "game.h"

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  
#endif

int main()
{
	//invoke the function that controls the game logic
	CGame* myGame = new CGame;
	myGame->gameManager();
	delete myGame;
	std::cout << "End of program. press ENTER to close.";
	std::cin.get();
#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
	return 0;
}

