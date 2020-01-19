#include "stdafx.h"
#include "Slot.h"
#include "Credits.h"
#include "Screen.h"
using namespace std;


#pragma region Constructors
Slot::Slot(Console &console) : console(console)
{}

Slot::~Slot()
{}
#pragma endregion


#pragma region Methods: Slot manipulation

void Slot::GetCredits(Credits credits)
{
	this->credits = credits;
}

void Slot::GetScreen(Screen screen)
{
	this->screen = screen;
}

bool Slot::Play()										//what happens after pressing 'X'
{
		if (credits.GetBet() > credits.GetCredits())	//if you have less credits than bet you can't play
		{
			credits.SetBet(credits.GetCredits());
			SetPrizeTable();
			return false;
		}
		else											//substracting bet from credits
		{
			credits.SetCredits(credits.GetCredits() - credits.GetBet());
			return true;
		}
}

void Slot::PlayerDoAction()								//what happens if you press 'B' or 'X'
{
	if (console.KeyPressed(KEY_B))						//change bet
	{
		credits.ChangeBet();
		SetPrizeTable();
		Sleep(350);
	}
	else if(console.KeyPressed(KEY_X))					//start a possible play
	{
		if (credits.GetCredits() > 0)
		{
			spin = Play();
			if (spin == true)							//if play is possible
			{
				Spin();
				win = CheckWin();						
				if (win == true)						//checking win condition
				{
					Beep(850, 350);
					Beep(850, 350);

					Beep(825, 150);
					Beep(825, 350);
					Beep(850, 500);
				}
				else
				{
					Beep(200, 400);
				}
				spin = false;
			}
		}
		Sleep(300);
	}
}

void Slot::Spin()											//function imitating a spin animation
{
	DWORD currentTickCount;
	DWORD lastDrawTickCount = 0;

	bool wasDrawn = false;

	for (int i = 0; i < 3; i++)
	{
		wasDrawn = false;
		while (wasDrawn == false)
		{
			currentTickCount = GetTickCount();				//tickcount in ms
			if (currentTickCount - lastDrawTickCount > 600)
			{
				console.CopyBackgroundToSlot();
 				screen.RandomizeScreen();
				DrawScreen();
				if (i == 2 && screen.GetSymbolSlotScreenChar(0, 1) == screen.GetSymbolSlotScreenChar(1, 1) && screen.GetSymbolSlotScreenChar(1, 1) == screen.GetSymbolSlotScreenChar(2, 1))
				{
					console.DrawTextOnSlot((short)7, (short)8, screen.GetSymbolSlotScreenString(0, 1), FOREGROUND_RED | FOREGROUND_GREEN);
					console.DrawTextOnSlot((short)10, (short)8, screen.GetSymbolSlotScreenString(1, 1), FOREGROUND_RED | FOREGROUND_GREEN);
					console.DrawTextOnSlot((short)13, (short)8, screen.GetSymbolSlotScreenString(2, 1), FOREGROUND_RED | FOREGROUND_GREEN);
				}
				credits.DoDrawCredits(console);
				credits.DoDrawBet(console);
				SetPrizeTable();
				console.CopySlotToScreen();

				lastDrawTickCount = GetTickCount();
				wasDrawn = true;
			}
		}
	}
}

void Slot::DrawScreen()
{
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			console.DrawTextOnSlot((short)(7 + x*3), (short)(6 + 2*y), screen.GetSymbolSlotScreenString(x,y), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
		}
	}
}

void Slot::SetPrizeTable()											//drowing a prize table on the right
{
	console.DrawTextOnSlot((short)26, (short)6, to_string(screen.GetMultiplayer(4) * credits.GetBet()), screen.GetColor(4));
	console.DrawTextOnSlot((short)26, (short)7, to_string(screen.GetMultiplayer(3) * credits.GetBet()), screen.GetColor(3));
	console.DrawTextOnSlot((short)26, (short)8, to_string(screen.GetMultiplayer(2) * credits.GetBet()), screen.GetColor(2));
	console.DrawTextOnSlot((short)26, (short)9, to_string(screen.GetMultiplayer(1) * credits.GetBet()), screen.GetColor(1));
	console.DrawTextOnSlot((short)26, (short)10, to_string(screen.GetMultiplayer(0) * credits.GetBet()), screen.GetColor(0));

}

bool Slot::CheckWin()												//checking win condition
{
	if (screen.GetSymbolSlotScreenChar(0, 1) == screen.GetSymbolSlotScreenChar(1, 1) && screen.GetSymbolSlotScreenChar(1, 1) == screen.GetSymbolSlotScreenChar(2, 1))
	{
		if (screen.GetSymbolSlotScreenChar(0, 1) == screen.GetSymbol(0))
		{
			AddWin(0);
			return true;
		}
		else if (screen.GetSymbolSlotScreenChar(0, 1) == screen.GetSymbol(1))
		{
			AddWin(1);
			return true;
		}
		else if (screen.GetSymbolSlotScreenChar(0, 1) == screen.GetSymbol(2))
		{
			AddWin(2);
			return true;
		}
		else if (screen.GetSymbolSlotScreenChar(0, 1) == screen.GetSymbol(3))
		{
			AddWin(3);
			return true;
		}
		else
		{
			AddWin(4);
			return true;
		}
		return false;
	}
}

void Slot::AddWin(int number)										//adding win to credits
{
	credits.SetCredits(credits.GetCredits() + (credits.GetBet() * screen.GetMultiplayer(number)));
	credits.DoDrawCredits(console);
}

void Slot::Simulate()												//simulating whole machine
{
	DWORD currentTickCount;
	DWORD lastDrawTickCount = 0;

	while (!console.KeyPressed(VK_ESCAPE))							//simulation last till pressing 'ESC'
	{
		currentTickCount = GetTickCount();							//tickcount in ms

		if (currentTickCount - lastDrawTickCount > 20)				// 50 frames per second
		{
			PlayerDoAction();
			console.CopyBackgroundToSlot();
			credits.DoDrawCredits(console);
			credits.DoDrawBet(console);
			DrawScreen();
			SetPrizeTable();
			console.CopySlotToScreen();

			lastDrawTickCount = GetTickCount();
		}
	}
}


#pragma endregion
