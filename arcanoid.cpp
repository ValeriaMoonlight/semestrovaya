#include "arcanoid.h"
#include "tech.h"
#include <stdlib.h>
#include "math.h"
#include "stdio.h"
#include "conio.h"
#include "windows.h"
#include <time.h>

playing FieldDraw(playing GamePlay, HANDLE hConsole)
{
	
	SetConsoleTextAttribute(hConsole, (WORD)((11 << 4) | 1));

	for (int i = 1; i < GamePlay.FieldPlay.height; i++)
	{
		GamePlay.LeftWall.x = 1;
		GamePlay.LeftWall.y = i;
		Draw(GamePlay.LeftWall.x, GamePlay.LeftWall.y);
		printf("|");

		GamePlay.RightWall.x = GamePlay.FieldPlay.width - 2;
		GamePlay.RightWall.y = i;
		Draw(GamePlay.RightWall.x, GamePlay.RightWall.y);
		printf("|");

	}
	for (int i = 2; i < GamePlay.FieldPlay.width - 2; i++)
	{
		GamePlay.TopWall.x = i;
		GamePlay.TopWall.y = 0;
		Draw(GamePlay.TopWall.x, GamePlay.TopWall.y);
		printf("_");
	}
	SetConsoleTextAttribute(hConsole, (WORD)((11 << 4) | 2));
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 15; j++)
		{
			GamePlay.BlockPlay[i][j].visible = 1;
		}
	int x = 4, y = 2;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			GamePlay.BlockPlay[i][j].x = x;
			GamePlay.BlockPlay[i][j].y = y;

			Draw(GamePlay.BlockPlay[i][j].x, GamePlay.BlockPlay[i][j].y);
			printf("%c", 220);
			x += 3;
		}
		y += 3;
		x = 4;
	}
	return GamePlay;
}
ball BallMove(ball BallPlay)
{

	BallPlay.x += (BallPlay.dx*BallPlay.speed);
	BallPlay.y += (BallPlay.dy*BallPlay.speed);

	return BallPlay;
}

playing BallVector(playing GamePlay)
{

	if ((GamePlay.BallPlay.x == GamePlay.RightWall.x - 1) |
		(GamePlay.BallPlay.x == GamePlay.LeftWall.x + 1))
	{
		GamePlay.BallPlay.dx *= -1;
		GamePlay.BallPlay.dy *= 1;
	}
	
	if (GamePlay.BallPlay.y == GamePlay.TopWall.y+1)
	{
		GamePlay.BallPlay.dx *= 1;
		GamePlay.BallPlay.dy *= -1;
	}

	if (GamePlay.BallPlay.y >= GamePlay.FieldPlay.height-1)
	{
		GamePlay.BallPlay.dx *= 0;
		GamePlay.BallPlay.dy *= 0;
		GameOver(GamePlay.FieldPlay);

	}

	if ((GamePlay.BallPlay.y == GamePlay.PlatformPlay.y) && 
		((GamePlay.BallPlay.x == GamePlay.PlatformPlay.x)|
			(GamePlay.BallPlay.x == GamePlay.PlatformPlay.x - 1) |
			(GamePlay.BallPlay.x == GamePlay.PlatformPlay.x - 2) |
			(GamePlay.BallPlay.x == GamePlay.PlatformPlay.x - 3) |
			(GamePlay.BallPlay.x == GamePlay.PlatformPlay.x - 4) |
				(GamePlay.BallPlay.x == GamePlay.PlatformPlay.x + 1) |
				(GamePlay.BallPlay.x == GamePlay.PlatformPlay.x + 2) |
				(GamePlay.BallPlay.x == GamePlay.PlatformPlay.x + 3) |
				(GamePlay.BallPlay.x == GamePlay.PlatformPlay.x + 4)))
	{
		GamePlay.BallPlay.dx *= 1;
		GamePlay.BallPlay.dy *= -1;
	}
	for (int i=0; i<5; i++)
		for (int j = 0; j<15; j++)
			if (GamePlay.BlockPlay[i][j].visible == 1)
			{
				if (((GamePlay.BallPlay.y == GamePlay.BlockPlay[i][j].y)|
					(GamePlay.BallPlay.y == GamePlay.BlockPlay[i][j].y+1)) &&
					(GamePlay.BallPlay.x == GamePlay.BlockPlay[i][j].x)|
					(GamePlay.BallPlay.x == GamePlay.BlockPlay[i][j].x-1))
				{
				
					GamePlay.BlockPlay[i][j].visible = 0;
					GamePlay.BallPlay.dx *= 1;
					GamePlay.BallPlay.dy *= -1;
					GamePlay=BlockInvisible(GamePlay,i,j);
				}
			}
	return GamePlay;
}

platform PlatformMove(platform PlatformPlay)
{

		if (_kbhit())
		{
			int code = _getch();
			if (code == 0 || code == 224)
			{
				code = _getch();

				switch (code)
				{
				case 77:
					PlatformPlay.x += 2;
				case 75:
					PlatformPlay.x -= 1;
				}
			}
		}

	return PlatformPlay;
}

playing BlockInvisible(playing GamePlay, int i, int j)
{
	Draw(GamePlay.BlockPlay[i][j].x, GamePlay.BlockPlay[i][j].y);
	ClearScreen(GamePlay.BlockPlay[i][j].x, GamePlay.BlockPlay[i][j].y, GamePlay.BlockPlay[i][j].x + 1, GamePlay.BlockPlay[i][j].y + 1);

	return GamePlay;
}

void GameOver(field FieldPlay)
{
	Draw(FieldPlay.width / 2.5, FieldPlay.height / 2);
	printf("GAME OVER");
	if (_getch())
		exit(-1);
}
void GameWin(playing GamePlay)
{
	int  count = 0;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 15; j++)
			if (GamePlay.BlockPlay[i][j].visible == 0)
				count++;
	if (count == 15*5)
	{
		Draw(GamePlay.FieldPlay.width / 2.5, GamePlay.FieldPlay.height / 2);
		printf("GAME WIN");
		if (_getch())
			exit(-1);
	}
}
