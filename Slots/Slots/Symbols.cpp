#include "stdafx.h"
#include "Symbols.h"

using namespace std;


#pragma region Constructors

Symbols::Symbols(): Symbols(0, 0, 'x', 0)
{}

Symbols::Symbols(int multiplier, int probability, char symbol, WORD color): multiplier(multiplier), probability(probability), symbol(symbol), color(color)
{}


Symbols::~Symbols()
{}

#pragma endregion

#pragma region Accesors

int Symbols::GetMultiplier() const
{
	return multiplier;
}

int Symbols::GetProbability() const
{
	return probability;
}

char Symbols::GetSymbol() const
{
	return symbol;
}

WORD Symbols::GetColor() const
{
	return color;
}
#pragma endregion