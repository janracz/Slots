#pragma once
#include "Console.h"

using namespace std;


class Symbols
{
private:
	int multiplier;
	int probability;
	char symbol;
	WORD color;

public:
	//Constructors and destructor
	Symbols();
	Symbols(int, int, char, WORD);
	~Symbols();

	//getters
	int GetMultiplier() const;
	int GetProbability() const;
	char GetSymbol() const;
	WORD GetColor() const;
};
