#include "stdafx.h"
#include "Console.h"
using namespace std;


Console::Console(short width, short height) : width(width), height(height)
{
	// Allocate buffer for console
	buffer_background = new CHAR_INFO[width*height];
	buffer_slot = new CHAR_INFO[width*height];

	// Create consolewindows
	window_size = { 0,0, width -1, height -1};
	bufferCoord = { width, height };
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);						// Get console handle
	SetConsoleTitle(L"MAGIC SLOT");									// Set console title
	SetConsoleWindowInfo(hConsole, TRUE, &window_size);				// Set window size
	SetConsoleScreenBufferSize(hConsole, bufferCoord);				// Set screen's buffer size


	for (short y = 0; y < height; ++y)								//set color
		for (short x = 0; x < width; ++x)
		{
			GetCharXYInBuffer(buffer_background, x, y)->Char.AsciiChar = (unsigned char)0;
			GetCharXYInBuffer(buffer_background, x, y)->Attributes = 0;
		}
	for (short y = 0; y < 17; y++)									//draw slot machine
		for (short x = 0; x < 33; x++)
		{
			GetCharXYInBuffer(buffer_background, x, y)->Attributes = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN;
			GetCharXYInBuffer(buffer_background, x, y)->Char.AsciiChar = slotMachine[y][x];
		}
	for (short y = 7; y < 10; y++)									//colour winning line
	{
		if (y == 8)
		{
			GetCharXYInBuffer(buffer_background, 5, y)->Attributes = FOREGROUND_RED | FOREGROUND_GREEN;
			GetCharXYInBuffer(buffer_background, 8, y)->Attributes = FOREGROUND_RED | FOREGROUND_GREEN;
			GetCharXYInBuffer(buffer_background, 11, y)->Attributes = FOREGROUND_RED | FOREGROUND_GREEN;
			GetCharXYInBuffer(buffer_background, 14, y)->Attributes = FOREGROUND_RED | FOREGROUND_GREEN;
		}
		else
		{
			for (short x = 5; x < 15; x++)
			{
				GetCharXYInBuffer(buffer_background, x, y)->Attributes = FOREGROUND_RED | FOREGROUND_GREEN;
			}
		}
	}
	for (short y = 4; y < 11; y++)									//colour '$' symbols on the side of slot machine
	{
		GetCharXYInBuffer(buffer_background, 2, y)->Attributes = FOREGROUND_GREEN;
		GetCharXYInBuffer(buffer_background, 17, y)->Attributes = FOREGROUND_GREEN;
	}
	CursorHide();
}


Console::~Console()
{
	delete[] buffer_background;
	delete[] buffer_slot;
}


void Console::CopyBackgroundToSlot()
{
	memcpy(buffer_slot, buffer_background, sizeof(CHAR_INFO) * width * height);
}

void Console::CopySlotToScreen()
{
	WriteConsoleOutputA(hConsole, buffer_slot, bufferCoord, COORD_00, &window_size);
}

void Console::CursorHide()
{
	CONSOLE_CURSOR_INFO lpCursor{ 20, false };
	SetConsoleCursorInfo(hConsole, &lpCursor);
}

void Console::DrawTextOnBuffer(CHAR_INFO * buffer, short x, short y, string info, WORD color)
{
	const char* text = info.c_str();
	int maxCharsToCopy = width - x - 1;
	int textLength = strlen(text);
	int charsToCopy = textLength > maxCharsToCopy ? maxCharsToCopy : textLength;

	for (int i = 0; i < charsToCopy; i++)
	{
		CHAR_INFO *charptr = GetCharXYInBuffer(buffer, x + i, y);
		charptr->Char.AsciiChar = text[i];
		charptr->Attributes = color;
	}

}


CHAR_INFO* Console::GetCharXYInBuffer(CHAR_INFO *buffer, short x, short y)
{
	return &buffer[x + width * y];
}

void Console::DrawTextOnBackground(short x, short y, string info, WORD color)
{
	DrawTextOnBuffer(buffer_background, x, y, info, color);
}


void Console::DrawTextOnSlot(short x, short y, string info, WORD color)
{
	DrawTextOnBuffer(buffer_slot, x, y, info, color);
}


void Console::GotoXY(short x, short y)
{
	SetConsoleCursorPosition(hConsole, COORD{ x, y });
}

bool Console::KeyPressed(int vKey)
{
	SHORT state = GetAsyncKeyState(vKey) && 0x8000;
	return state == 1;
}


#pragma region Accessors
int Console::GetWidth()
{
	return width;
}

int Console::GetHeight()
{
	return height;
}

#pragma endregion 