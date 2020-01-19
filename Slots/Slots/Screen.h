#pragma once
#include "Symbols.h"

using namespace std;


class Screen
{
private:
	Symbols SymbolsArray[5];
	char SlotScreen[3][3];

public:
	Screen();
	Screen(int);
	~Screen();

	//getters
	int GetMultiplayer(int) const;
	int GetProbability(int) const;
	char GetSymbol(int) const;
	WORD GetColor(int) const;
	char GetSymbolSlotScreenChar(int, int) const;
	string GetSymbolSlotScreenString(int, int) const;

	//setter
	void SetSymbolSlotScreen(int, int, char);


	//class methods
	void RandomizeScreen();
};
