#ifndef TOOLS_CPP
#define TOOLS_CPP

#include "Tools.h"
#include <stdio.h>
#include "conio.h"
#include<iostream>
#include<string>
#include<Windows.h>

using namespace std;

Tools::Tools()
{
}


Tools::~Tools()
{
}

void Tools::displayText(string str, char color){

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;


	switch (color)
	{
	case 'r':
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << str;
		break;

	case 'b':
		SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << str;
		break;

	case 'g':
		SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << str;
		break;

	default:
		cout << str;
		break;
	}

	SetConsoleTextAttribute(h, wOldColorAttrs);

}

void Tools::adjustScreen(int width, int height){
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, width, height, TRUE); // 800 width, 800 height
}


#endif