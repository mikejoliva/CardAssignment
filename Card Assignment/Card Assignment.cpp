// Card Assignment.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "game.h"

//This define is used to "hijack" the output of the console and redirect it to a text file
//#define _FILEOUTPUT

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  
#endif

#ifdef _FILEOUTPUT
#include <fstream>      // std::ofstream
#endif

int main()
{
#ifdef _FILEOUTPUT
	std::streambuf *psbuf, *backup;
	std::ofstream filestr;
	filestr.open("..//output.txt");

	backup = std::cout.rdbuf();     // back up cout's streambuf

	psbuf = filestr.rdbuf();        // get file's streambuf
	std::cout.rdbuf(psbuf);         // assign streambuf to cout
#endif

	//invoke the function that controls the game logic
	CGame* pGame = new CGame;
	pGame->GameManager();
	//delete pointer to the game class
	delete pGame;
	//wait for keypress to exit
	std::cin.clear();
	std::cin.ignore();
	std::cin.get();

#ifdef _FILEOUTPUT
	std::cout.rdbuf(backup);        // restore cout's original streambuf
	filestr.close();
#endif
#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
	return 0;
}