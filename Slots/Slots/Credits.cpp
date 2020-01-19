#include "stdafx.h"
#include "Credits.h"

using namespace std;

#pragma region Constructors

Credits::Credits() : Credits(0, 0)
{}

Credits::Credits(int credits, int bet): credits(credits), bet(bet)
{}

Credits::~Credits()
{}
#pragma endregion

#pragma region Accesors
//setters
void Credits::SetCredits(int credits)
{
	this->credits = credits;
}

void Credits::SetBet(int bet)
{
	this->bet = bet;
}

//getters
int Credits::GetCredits() const
{
	return credits;
}

int Credits::GetBet() const
{
	return bet;
}

#pragma endregion

#pragma region Class methods

void Credits::DoDrawCredits(Console &console)
{
	console.DrawTextOnSlot((short)CREDITS_X, (short)CREDITS_Y, to_string(GetCredits()) , FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
}

void Credits::DoDrawBet(Console &console)
{
	console.DrawTextOnSlot((short)BET_X, (short)BET_Y, to_string(GetBet()), FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
}

void Credits::ChangeBet()
{
	if (GetBet() == 10)
	{
		SetBet(1);
	}
	else
	{
		SetBet(GetBet() + 1);
	}
}
#pragma endregion