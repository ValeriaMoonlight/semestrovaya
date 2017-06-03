#include "arcanoid.h"
#include "tech.h"
#include <stdlib.h>
#include "math.h"
#include <time.h>
#include "conio.h"
#include "windows.h"
#include "stdio.h"


int main()
{	
	playing GamePlay;
	
	GamePlay.BallPlay.dx = 1;
	GamePlay.BallPlay.dy = 1;

	SetConsoleSize(GamePlay.FieldPlay.width, GamePlay.FieldPlay.height);
	GamePlay.PlatformPlay.x = GamePlay.FieldPlay.width / 2;
	GamePlay.PlatformPlay.y = GamePlay.FieldPlay.height - 2;
	
	system("color B1");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GamePlay = FieldDraw(GamePlay, hConsole);

	while(TRUE)
	{
		
		SetConsoleTextAttribute(hConsole, (WORD)((11 << 4) | 5));
		Draw(GamePlay.PlatformPlay.x - 3, GamePlay.PlatformPlay.y);
		ClearScreen(GamePlay.PlatformPlay.x - 3, GamePlay.PlatformPlay.y, GamePlay.PlatformPlay.x+4, GamePlay.PlatformPlay.y+1);
		GamePlay.PlatformPlay=PlatformMove(GamePlay.PlatformPlay);
		Draw(GamePlay.PlatformPlay.x-3, GamePlay.PlatformPlay.y);
		printf("_______");

		
		Draw(GamePlay.BallPlay.x, GamePlay.BallPlay.y);
		ClearScreen(GamePlay.BallPlay.x, GamePlay.BallPlay.y, GamePlay.BallPlay.x + 1, GamePlay.BallPlay.y + 1);
		GamePlay = BallVector(GamePlay);
		GamePlay.BallPlay = BallMove(GamePlay.BallPlay);
		Draw(GamePlay.BallPlay.x, GamePlay.BallPlay.y);
		printf("O"); 

		GameWin(GamePlay);

		Sleep(100);
	}
	
	getchar();
	getchar();
	return 0;
}
