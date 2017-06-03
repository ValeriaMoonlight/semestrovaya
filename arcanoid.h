#pragma once
#include "windows.h"

typedef struct platform
{
	int x;
	int y; 
}platform;

typedef struct wall
{
	int x;
	int y;

}wall;

typedef struct ball
{
	int x=20;
	int y=35;
	int speed=1;
	int dx;
	int dy;
} ball;

typedef struct blocks
{
	int x;
	int y;
	bool visible;

}blocks;

typedef struct field
{
	int height=50;
	int width=50;
}field;

typedef struct playing
{
	ball BallPlay;
	platform PlatformPlay;;
	field FieldPlay;
	wall LeftWall, RightWall, TopWall;
	blocks BlockPlay[5][15];

}playing;

playing FieldDraw(playing GamePlay, HANDLE hConsole);
ball BallMove(ball BallPlay);
playing BallVector(playing GamePlay);
platform PlatformMove(platform PlatformPlay);
playing BlockInvisible(playing GamePlay, int i, int j);
void GameOver(field FieldPlay);
void GameWin(playing FieldPlay);
