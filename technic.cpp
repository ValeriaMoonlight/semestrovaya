#include "stdio.h"
#include "conio.h"
#include "windows.h"
#include <time.h>


void SetConsoleSize(int x, int y)
{
	HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD crd = { x , y };
	SMALL_RECT src = { 0, 0, crd.X - 1, crd.Y - 1 };
	SetConsoleWindowInfo(out_handle, true, &src);
	SetConsoleScreenBufferSize(out_handle, crd);

}


void ClearRow(int X, int Y, int rowWidth)
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	COORD                      homeCoords = { X,Y };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;

	// Fill the row with spaces
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		rowWidth,
		homeCoords,
		&count
	)) return;

	//Fill the row with the current colors and attributes
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		rowWidth,
		homeCoords,
		&count
	)) return;

	//Move the cursor home
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

void ClearScreen(int X1, int Y1, int X2, int Y2)
{
	while (Y1<Y2)
		ClearRow(X1, Y1++, X2 - X1);
}


void Draw(int x, int y)
{
	HANDLE hCons;
	COORD crd;
	hCons = GetStdHandle(STD_OUTPUT_HANDLE);

	crd.X = x;
	crd.Y = y;

	SetConsoleCursorPosition(hCons, crd);
}
