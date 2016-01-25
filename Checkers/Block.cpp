#ifndef BLOCK_CPP
#define BLOCK_CPP


#include "Piece.h"
#include "Block.h"


Block::Block(){
	row = 0;
	col = 0;
	color = 'n';
	isEmpty = true;
	p = NULL;
}

void Block::setBlock(int row, int col, char color)
{
	this->row = row;
	this->col = col;
	this->color = color;
	isEmpty = true;
	
}

Block::~Block()
{
	delete &row;
	delete &col;
	delete &color;
	delete p;

}

int Block::getRow(){
	return row;
}

int Block::getCol(){
	return col;
}

char Block::getColor(){
	return color;
}

Piece* Block::getPiece(){
	return p;
}

void Block::setPiece(Piece *p){
	this->p = p;
	p->setPiece(this->col, this->col);
	isEmpty = false;
}

bool Block::isItEmpty(){
	return isEmpty;
}

void Block::empty(){
	p = NULL;
	isEmpty = true;
}

void Block::createPiece(char c){
	p = new Piece(this->row, this->col, c);
	isEmpty = false;
}

#endif