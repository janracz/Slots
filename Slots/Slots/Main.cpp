#include "stdafx.h"
#include "Slot.h"
#include "Console.h"
#include "Credits.h"
#include "Screen.h"

using namespace std;
#define WIDTH 35
#define HEIGHT 18


int main()
{
	// initialize random generator
	srand((unsigned int)time(0));

	// create console 
	Console console(WIDTH, HEIGHT);
	
	//set starting credits
	Credits credits(1000, 1);

	//set starting screen
	Screen screen(1);						//nie wiem czemu to musi byæ w ten g³upi sposob

	// create slot machine
	Slot slot(console);
	slot.GetCredits(credits);
	slot.GetScreen(screen);
	
	slot.Simulate();
}