#pragma once
#include "Console.h"
#include "Credits.h"
#include "Screen.h"

using namespace std;



#define MAXANIMALS 15
#define KEY_B 0x42
#define KEY_X 0x58
class Slot
{
private:
	//info about credits
	Credits credits;
	//checker if we need to spin
	bool spin = false;
	bool win = false;
	//look of the screen
	Screen screen;
	// Technical object grouping console operations
	Console &console;

public:
	// Constructors
	Slot(Console &console);
	~Slot();

	//getters
	void GetCredits(Credits);
	void GetScreen(Screen);

	//class methods
	bool Play();
	void PlayerDoAction();
	void Spin();
	void DrawScreen();
	void SetPrizeTable();
	bool CheckWin();
	void AddWin(int);
	void Simulate();
};
