#ifndef TOOLS_H
#define TOOLS_H

#include<iostream>
#include<string>
#include<Windows.h>

using namespace std;

class Tools
{
public:
	Tools();
	~Tools();

	//Function can display string in 3 colors, 'r' for red, 'b' for blue, and 'g' for green (works on Windows!)
	void displayText(string str, char color);

	//Function can adjust the console screen dimentions when poping out (works on Windows!)
	void adjustScreen(int width, int height);

};

#endif