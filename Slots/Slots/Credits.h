#pragma once
#include "Console.h"

using namespace std;


#define CREDITS_X 11
#define CREDITS_Y 12
#define BET_X 28
#define BET_Y 12


class Credits
{

private:
	int credits;
	int bet;

public:
	Credits();
	Credits(int, int);

	~Credits();

	//setters
	void SetCredits(int);
	void SetBet(int);

	//getters
	int GetCredits() const;
	int GetBet() const;

	//class methods
	void DoDrawCredits(Console &);
	void DoDrawBet(Console &);
	void ChangeBet();
};
