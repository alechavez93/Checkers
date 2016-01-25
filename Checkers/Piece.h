#ifndef PIECE_H
#define PIECE_H


#include<iostream>
#include <vector>

using namespace std;


class Piece
{

private:
	bool isItCrownd = false;
	int row;
	int col;
	char color='n';

public:
	Piece(int row, int col, char color);
	~Piece();
	void setPiece(int row, int col);
	int getRow();
	int getCol();
	char getColor();
	bool isCrownd();
	vector<int> posibleMoves();
	void setMyPiece(int row, int col, char color);
};






#endif // !PIECE_H