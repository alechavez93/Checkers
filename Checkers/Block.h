#ifndef BLOCK_H
#define BLOCK_H


#include "Piece.h"


class Block
{

private:
	bool isEmpty;
	int row, col;
	char color;
	Piece *p;

public:
	Block();
	void setBlock(int row, int col, char color);
	~Block();
	int getRow();
	int getCol();
	char getColor();
	Piece* getPiece();
	bool isItEmpty();
	void createPiece(char c);
	void setPiece(Piece *p);
	void empty();
};

#endif