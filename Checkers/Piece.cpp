#ifndef PIECE_CPP
#define PIECE_CPP

#include "Piece.h"
#include <vector>

using namespace std;

Piece::Piece(int row, int col, char color)
{
	this->row = row;
	this->col = col;
	this->color = color;
	this->isItCrownd = false;
}

void Piece::setMyPiece(int row, int col, char color)
{
	this->row = row;
	this->col = col;
	this->color = color;
	this->isItCrownd = false;
}


Piece::~Piece()
{
	delete &row;
	delete &col;
	delete &color;
}

int Piece::getRow(){
	return row;
}

int Piece::getCol(){
	return col;
}

char Piece::getColor(){
	return color;
}

vector<int> Piece::posibleMoves(){
	vector<int> V {-1, -1, 1, -1};
	return V;
}

void Piece::setPiece(int row, int col){
	this->row = row;
	this->col = col;
}

bool Piece::isCrownd(){
	return isItCrownd;
}



#endif // PIECE_CPP
