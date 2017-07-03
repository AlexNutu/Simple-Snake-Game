// SnakeGamev0.1.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

void printingSnake()
{
	// for S 
	cout << "\n\n ==============================================================================\n\n\n\n";
	cout << "      ,dBBBBb.                                  BBB\n";
	cout << "     dBBP  YBBb                                 BBB\n";
	cout << "      YBBb.                                     BBB\n";
	cout << "       YBBBb.         BBBBBb.        BBBBb.     BBB  BBB     .dBBb.\n";
	cout << "          BYBBb.      BBB  BBb          BBb     BBB .BBP    dBP  Y8b\n";
	cout << "            BBBb      BBB  BBB     .dBBBBBB     BBBBBBK     BBBBBBBB\n";
	cout << "     YBBb  dBBP       BBB  BBB     BBB  BBB     BBB  BBb    YBb.\n";
	cout<<"       YBBBBP         BBB  BBB      YBBBBBB     BBB  BBB     YBBBBB\n";
	cout << "\n																		  v1.0";
	cout << "\n\n\n ==============================================================================\n\n";

}
void making_Sleep()
{
	Sleep(500);

	printingSnake();

	Sleep(400);
	
	system("cls");
	
	Sleep(400);
	
	printingSnake();

	Sleep(400);

	system("cls");

	Sleep(400);

	printingSnake();
	
	cout << endl << endl << " 			Press ENTER to start the game	"<<endl;
	
	_getch();

	Sleep(350);
	
	system("cls");
	
	Sleep(350);
}


bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score, prevScore, sleep, mode;
int tailX[100],tailY[100];
int nTail;// lungimea cozii
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirecton dir;

void SpeedLevel()
{
	if (score <= 50)
		Sleep(100);
	else
		if (score <= 100)
			Sleep(50);
		else
			return; //maximum speed
}
int gameMode()
{
	cout <<endl<< "			GAME MODE  " << endl;
	cout << endl << " 1. With walls active "<<endl;
	cout << endl << " 2. With walls inactive";
	cout << endl <<endl<< " SELECT : ";
	if (_getche() == '1')
		return 1;
	return 0;
}
void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width; // random number from 0 to width-1
	fruitY = rand() % height;// random number from 0 to height-1
	score = 0;
}
void Draw()
{
	system("cls");
	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++) {

		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
					
				}
				if (!print)
					cout << " ";
			}


			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;
	cout << " Score : " << score << endl;
}
void Input()
{
	if(_kbhit()) // functie ce returneaza 1 daca este apasata o tasta si 0 daca nu
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}
void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	if (mode == 1)
	{
		if (x > width || x<0 || y> height || y < 0)
			gameOver = true;
	}
	else
	{
		if (x >= width) 
			x = 0; 
			else 
				if (x < 0)
					x = width - 1;
		if (y >= height)
			y = 0;
		else
			if (y < 0)
				y = height-1;
	}
	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}
int main()
{
	making_Sleep();
	mode = gameMode();
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		SpeedLevel();
	}	
	cout << endl << endl;
	return 0;
}

