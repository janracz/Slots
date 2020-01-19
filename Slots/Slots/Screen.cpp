#include "stdafx.h"
#include "Screen.h"

using namespace std;

#pragma region Constructor

Screen::Screen() : Screen(1)
{}

Screen::Screen(int i)						//seting starting screen and all symbols data
{
		SymbolsArray[0] = Symbols(1, 35, 'J', FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
		SymbolsArray[1] = Symbols(2, 27, 'Q', FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
		SymbolsArray[2] = Symbols(4, 18, 'K', FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
		SymbolsArray[3] = Symbols(5, 13, 'A', FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
		SymbolsArray[4] = Symbols(10, 7, '7', FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
		SlotScreen[0][0] = GetSymbol(1);
		SlotScreen[0][1] = GetSymbol(4);
		SlotScreen[0][2] = GetSymbol(2);
		SlotScreen[1][0] = GetSymbol(0);
		SlotScreen[1][1] = GetSymbol(4);
		SlotScreen[1][2] = GetSymbol(1);
		SlotScreen[2][0] = GetSymbol(3);
		SlotScreen[2][1] = GetSymbol(4);
		SlotScreen[2][2] = GetSymbol(0);
}

Screen::~Screen()
{}

#pragma endregion

#pragma region Accesors

int Screen::GetMultiplayer(int number) const
{
	return SymbolsArray[number].GetMultiplier();
}

int Screen::GetProbability(int number) const
{
	return SymbolsArray[number].GetProbability();
}

char Screen::GetSymbol(int number) const
{
	return SymbolsArray[number].GetSymbol();
}

WORD Screen::GetColor(int number) const
{
	return SymbolsArray[number].GetColor();
}

char Screen::GetSymbolSlotScreenChar(int x, int y) const
{
	return SlotScreen[x][y];
}

string Screen::GetSymbolSlotScreenString(int x, int y) const
{
	string s(1, SlotScreen[x][y]);
	return s;
}

void Screen::SetSymbolSlotScreen(int x, int y, char symbol)
{
	this->SlotScreen[x][y] = symbol;
}

#pragma endregion

#pragma region Class methods

void Screen::RandomizeScreen()									//creating a random configuration of symbols on screen
{
	srand(time(NULL));

	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			int randomNumber = rand() % 100 + 1;
			if (randomNumber > SymbolsArray[4].GetProbability() + SymbolsArray[3].GetProbability() + SymbolsArray[2].GetProbability() + SymbolsArray[4].GetProbability())
			{
				SetSymbolSlotScreen(x, y, SymbolsArray[0].GetSymbol());
			}
			else if (randomNumber >  SymbolsArray[4].GetProbability() + SymbolsArray[3].GetProbability() + SymbolsArray[2].GetProbability())
			{
				SetSymbolSlotScreen(x, y, SymbolsArray[1].GetSymbol());
			}
			else if (randomNumber > SymbolsArray[4].GetProbability() + SymbolsArray[3].GetProbability())
			{
				SetSymbolSlotScreen(x, y, SymbolsArray[2].GetSymbol());
			}
			else if (randomNumber > SymbolsArray[4].GetProbability())
			{
				SetSymbolSlotScreen(x, y, SymbolsArray[3].GetSymbol());
			}
			else
			{
				SetSymbolSlotScreen(x, y, SymbolsArray[4].GetSymbol());
			}
		}
	}

}

#pragma endregion 