#ifndef BOARD_H
#define BOARD_H


#include "Block.h"
#include <vector>
#include <string>
#include "Tools.h"


using namespace std;

class Board
{
public:
	int size;
	bool goodAction = false;
	int redCount = 0;
	int blueCount = 0;
	bool isRedTurn = true;
	Block **board;
	Tools *t;


public:
	Board(int size);
	~Board();
	void displayBoard();
	void displaySpecial(int n, char color);
	void fillUpBoard();
	void displayEmptyValues();
	void changeTurn();
	void movePiece(int row1, int col1, int row2, int col2);
	void realAction(int row1, int col1, int row2, int col2);
	bool posibleAttack(int row, int col, string str);
	bool canAttack(char color);
	bool canPieceAttack(int row, int col);
};


#endif