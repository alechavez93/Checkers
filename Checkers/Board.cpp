#ifndef BOARD_CPP
#define BOARD_CPP

#include "Piece.h"
#include "Board.h"
#include <vector>
#include <string>


using namespace std;

Board::Board(int size)
{
	t = new Tools();
	char color = 'w';			//We use this variable to keep track of the block color(white, back)
	this->size = size;			//Setting the size of the board

	board = new Block*[size];	//Creating an array of pointers to Block

	for (int i = 0; i < size; i++){			//Initiating the arrays results in a 2D array of blocks called "board"
		board[i] = new Block[size];
	}

	for (int i = 0; i < size; i++){			//Passing down the coordinates row, col, and color of every block
		if (i % 2 == 0)						//This alternates the colors in the same column every row
			color = 'w';
		else
			color = 'd';

		for (int j = 0; j < size; j++){
			board[i][j].setBlock(i, j, color);	//This sets the mentioned info into the block

			if (color == 'd')					//This alternates the colors in the same row every column
				color = 'w';
			else
				color = 'd';
		}
	}

	fillUpBoard();

}

Board::~Board()
{
	delete &size;
	delete t;

	for (int i = 0; i < size; i++){			//This destructs every sngle block in the board
		for (int j = 0; j < size; j++){
			board[i][j].~Block();
		}
	}
}

void Board::displayBoard(){
	int count;

	//line1 = " -------- "
	//Line2 = "|OOOOOOOO|"
	//Line3 = "|        |"
	//Line4 = "|OOXXXXOO|
	//Line5 = "|  XXXX  |"
	//Line6 = "|0X0XX0X0|"

	cout << "\n\n\n";
	cout << "\t\t      0         1         2         3         4         5         6         7" << endl;

	for (int i = 0; i < size; i++){				//Lopping through Rows

		count = 0;
		for (int k = 0; k < 5; k++){			//6 Subrow system
			for (int j = 0; j < size; j++){		//Looping though Columns

				if (j == 0 && count == 2){
					cout << "\t\t" << i << " ";
					count++;
				}
				else if (j == 0){
					cout << "\t\t  ";
					count++;
				}
					

				if (board[i][j].getColor() == 'w'){			//In case the Block is White

					switch (k)
					{
					case 0: case 5:
						displaySpecial(1, 'n');
						break;
					case 1: case 4:
						displaySpecial(2, 'n');
						break;
					case 2: 
						if (!(board[i][j].isItEmpty())){										//In case the Block is Filled subrows 2 and 3 change to piece color
							if (!board[i][j].getPiece()->isCrownd())
								displaySpecial(4, board[i][j].getPiece()->getColor());				//The 4 middle blocks take the piece color
							else 
								displaySpecial(6, board[i][j].getPiece()->getColor());
						}
						else{
							displaySpecial(2, 'n');
						}
						break;
					case 3:
						if (!(board[i][j].isItEmpty())){										//In case the Block is Filled subrows 2 and 3 change to piece color
							displaySpecial(4, board[i][j].getPiece()->getColor());				//The 4 middle blocks take the piece color
						}
						else{
							displaySpecial(2, 'n');
						}
						break;
					}
				}

				else{										//In case the Block is Black
					switch (k)
					{
					case 0: case 5:
						displaySpecial(1, 'n');
						break;
					case 1: case 4:
						displaySpecial(3, 'n');
						break;
					case 2: case 3:
						if (!(board[i][j].isItEmpty())){										//In case the Block is Filled(Very unlikekly since we are doing Checkers!)
							displaySpecial(5, board[i][j].getPiece()->getColor());				//The 4 middle blocks take the piece color
						}
						else{
							displaySpecial(3, 'n');
						}
						break;
					}
				}
			}
			cout << endl;
		}
		
	}
	cout << "\t\t  ";
	for (int i = 0; i < size; i++)						//The ending line to complete our Board
		displaySpecial(1, 'n');

	
}

void Board::fillUpBoard(){

	redCount = blueCount = 12;

		board[0][0].createPiece('b'); board[0][2].createPiece('b'); board[0][4].createPiece('b'); board[0][6].createPiece('b');
		board[1][1].createPiece('b'); board[1][3].createPiece('b'); board[1][5].createPiece('b'); board[1][7].createPiece('b');
		board[2][0].createPiece('b'); board[2][2].createPiece('b'); board[2][4].createPiece('b'); board[2][6].createPiece('b');

		board[5][1].createPiece('r'); board[5][3].createPiece('r'); board[5][5].createPiece('r'); board[5][7].createPiece('r');
		board[6][0].createPiece('r'); board[6][2].createPiece('r'); board[6][4].createPiece('r'); board[6][6].createPiece('r');
		board[7][1].createPiece('r'); board[7][3].createPiece('r'); board[7][5].createPiece('r'); board[7][7].createPiece('r');

}

void Board::movePiece(int row1, int col1, int row2, int col2){

	//Checking for index out of bounds
	if (row1 < 0 || row1 >7 || row2 < 0 || row2 >7 || col1 < 0 || col1 >7 || col2 < 0 || col2 >7){
		cout << "Invalid Indexes!" << endl;
		return;
	}

	//Better way to move the piece by passing it around the blocks
	if (board[row2][col2].isItEmpty()){
		board[row2][col2].setPiece(board[row1][col1].getPiece());
		board[row1][col1].empty();
	}

	//Secondary way to move the piece by creating a new one with the same color
	/*if(board[row2][col2].isItEmpty()){
	Piece *p = board[row1][col1].getPiece();
	board[row2][col2].createPiece(board[row1][col1].getPiece()->getColor());
	board[row1][col1].empty();
	}*/
}

void Board::displayEmptyValues(){

	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			cout << board[i][j].isItEmpty() << " ";
		}
		cout << endl;
	}
}

void Board::displaySpecial(int n, char color){

	//line1 = " -------- "
	//Line2 = "|OOOOOOOO|"
	//Line3 = "|        |"
	//Line4 = "|OOXXXXOO|
	//Line5 = "|  XXXX  |"
	//Line6 = "|0X0XX0X0|"

	string str = "";
	str += (char)-37;


	string line1 = " -------- ";
	string line2 = "|" + str + str + str + str + str + str + str + str + "|";
	string line3 = "|        |";

	switch (n)
	{

	case 1:
		cout << line1;
		break;
	case 2:
		cout << line2;
		break;
	case 3:
		cout << line3;
		break;
	case 4:
		cout << "|" + str + str;
		t->displayText(str + str, color);
		t->displayText(str + str, color);
		cout << str + str + "|";
		break;
	case 5:
		cout << "|  ";
		t->displayText(str + str, color);
		t->displayText(str + str, color);
		cout << "  |";
		break;
	case 6:
		cout << "|" + str;
		t->displayText(str, color);
		t->displayText(str, 'g');
		t->displayText(str + str, color);
		t->displayText(str, 'g');
		t->displayText(str, color);
		cout << str + "|";
		break;

	default:
		cout << "Invaid Input!!" << endl;
		break;
	}
}

void Board::realAction(int row1, int col1, int row2, int col2){
	
	//Checking for index out of bounds
	if (row1 < 0 || row1 >7 || row2 < 0 || row2 >7 || col1 < 0 || col1 >7 || col2 < 0 || col2 >7 || board[row1][col1].isItEmpty()){
		cout << "Invalid Indexes!" << endl;
		return;
	}

	//In case of red's turn
	if (isRedTurn && (board[row1][col1].getPiece()->getColor() == 'r')){

		//Checking the block to move to is empty
		if (board[row2][col2].isItEmpty()){		

			if (((col1 == col2 - 1) && (row1 == row2 + 1)) || ((col1 == col2 + 1) && (row1 == row2 + 1))){ //Left or Right move
				if (!canAttack('r')){							//Only if we cant attack we move
					movePiece(row1, col1, row2, col2);
					isRedTurn = false;
				}
			}
			//Left or Right backward move in case of crownd piece
			else if (board[row1][col1].getPiece()->isCrownd() && (((col1 == col2 + 1) && (row1 == row2 - 1)) || ((col1 == col2 - 1) && (row1 == row2 - 1)))){
				if (!canAttack('r')){							//Only if we cant attack we move
					movePiece(row1, col1, row2, col2);
					isRedTurn = false;
				}
			}
			else if ((col1 == col2 + 2) && (row1 == row2 + 2)){	//left attack
				if (canAttack('r') && !board[row1 - 1][col1 - 1].isItEmpty() && (board[row1 - 1][col1 - 1].getPiece()->getColor() == 'b')){
					movePiece(row1, col1, row2, col2);			//We move
					board[row1 - 1][col1 - 1].empty();			//We delete the piece attacked
					isRedTurn = false;
				}
			}
			else if ((col1 == col2 - 2) && (row1 == row2 + 2)){	//right attack
				if (canAttack('r') && !board[row1 - 1][col1 + 1].isItEmpty() && (board[row1 - 1][col1 + 1].getPiece()->getColor() == 'b')){
					movePiece(row1, col1, row2, col2);			//We move
					board[row1 - 1][col1 + 1].empty();			//We delete the piece attacked
					isRedTurn = false;
				}
			}
			else if (board[row1][col1].getPiece()->isCrownd() && ((col1 == col2 + 2) && (row1 == row2 - 2))){	//left attack backwards
				if (canAttack('r') && !board[row1 + 1][col1 - 1].isItEmpty() && (board[row1 + 1][col1 - 1].getPiece()->getColor() == 'b')){
					movePiece(row1, col1, row2, col2);			//We move
					board[row1 + 1][col1 - 1].empty();			//We delete the piece attacked
					isRedTurn = false;
				}
			}
			else if (board[row1][col1].getPiece()->isCrownd() && ((col1 == col2 - 2) && (row1 == row2 - 2))){	//Right attack backwards
				if (canAttack('r') && !board[row1 + 1][col1 + 1].isItEmpty() && (board[row1 + 1][col1 + 1].getPiece()->getColor() == 'b')){
					movePiece(row1, col1, row2, col2);			//We move
					board[row1 + 1][col1 + 1].empty();			//We delete the piece attacked
					isRedTurn = false;
				}
			}
			else{								
				cout << "Invalid Input";	//invalid move
			}
		}

		//If the block is full
		else{
			cout << "The Block you want to move to is full" << endl;
		}
	}

	//In case of blue's turn
	else if (!isRedTurn && (board[row1][col1].getPiece()->getColor() == 'b')){
		//Checking the block to move to is empty
		if (board[row2][col2].isItEmpty()){

			if (((col1 == col2 + 1) && (row1 == row2 - 1)) || ((col1 == col2 - 1) && (row1 == row2 - 1))){ //Left or Right move
				if (!canAttack('b')){							//Only if we cant attack we move
					movePiece(row1, col1, row2, col2);
					isRedTurn = true;
				}
			}
			//Left or Right backward move in case of crownd piece
			else if (board[row1][col1].getPiece()->isCrownd() && (((col1 == col2 - 1) && (row1 == row2 + 1)) || ((col1 == col2 + 1) && (row1 == row2 + 1)))){
				if (!canAttack('b')){							//Only if we cant attack we move
					movePiece(row1, col1, row2, col2);
					isRedTurn = true;
				}
			}
			else if ((col1 == col2 + 2) && (row1 == row2 - 2)){	//left attack
				if (canAttack('b') && !board[row1 + 1][col1 - 1].isItEmpty() && (board[row1 + 1][col1 - 1].getPiece()->getColor() == 'r')){
					movePiece(row1, col1, row2, col2);			//We move
					board[row1 + 1][col1 - 1].empty();			//We delete the piece attacked
					isRedTurn = true;
				}
			}
			else if ((col1 == col2 - 2) && (row1 == row2 - 2)){	//right attack
				if (canAttack('b') && !board[row1 + 1][col1 + 1].isItEmpty() && (board[row1 + 1][col1 + 1].getPiece()->getColor() == 'r')){
					movePiece(row1, col1, row2, col2);			//We move
					board[row1 + 1][col1 + 1].empty();			//We delete the piece attacked
					isRedTurn = true;
				}
			}
			else if (board[row1][col1].getPiece()->isCrownd() && ((col1 == col2 + 2) && (row1 == row2 + 2))){	//left attack backwards
				if (canAttack('b') && !board[row1 - 1][col1 - 1].isItEmpty() && (board[row1 - 1][col1 - 1].getPiece()->getColor() == 'r')){
					movePiece(row1, col1, row2, col2);			//We move
					board[row1 - 1][col1 - 1].empty();			//We delete the piece attacked
					isRedTurn = true;
				}
			}
			else if (board[row1][col1].getPiece()->isCrownd() && ((col1 == col2 - 2) && (row1 == row2 + 2))){	//Right attack backwards
				if (canAttack('b') && !board[row1 - 1][col1 + 1].isItEmpty() && (board[row1 - 1][col1 + 1].getPiece()->getColor() == 'r')){
					movePiece(row1, col1, row2, col2);			//We move
					board[row1 - 1][col1 + 1].empty();			//We delete the piece attacked
					isRedTurn = false;
				}
			}
			else{
				cout << "Invalid Input";	//invalid move
			}
		}

		//If the block is full
		else{
			cout << "The Block you want to move to is full" << endl;
		}
	}
}

bool Board::canAttack(char color){
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			if (!board[i][j].isItEmpty() && board[i][j].getPiece()->getColor() == color && canPieceAttack(i,j)){
				return true;
			}
		}
	}
	return false;
}

bool Board::canPieceAttack(int row, int col){
	bool top = 1, left = 1, bot = 1, right = 1; //We check if we go out of bounds with any attack
	if (row - 2 < 0) top = 0;
	if (row + 2 > 7) bot = 0;
	if (col - 2 < 0) left = 0;
	if (col + 2 > 7) right = 0;

	if (board[row][col].isItEmpty()){
		cout << "Empty" << endl;
		return false;
	}

	if (board[row][col].getPiece()->isCrownd()){ //Crowned Piece no  matter if its red or blue
		if ((top && left && posibleAttack(row, col, "topleft")) || (top && right && posibleAttack(row, col, "topright")) || (bot && left && posibleAttack(row, col, "downleft")) || (bot && right && posibleAttack(row, col, "downright"))){
			return true;
		}
		else{
			return false;
		}
	}
	
	if (board[row][col].getPiece()->getColor() == 'r'){	//Red Piece
		if ((top && left && posibleAttack(row, col, "topleft")) || (top && right && posibleAttack(row, col, "topright"))){
			return true;
		}
		else return false;
	}
	else if (board[row][col].getPiece()->getColor() == 'b'){	//Blue Piece
		if ((bot && left && posibleAttack(row, col, "downleft")) || (bot && right && posibleAttack(row, col, "downright"))){
			return true;  
		}
		else return false;
	}
}

bool Board::posibleAttack(int row, int col, string str){
	char opposite;
	if (board[row][col].getPiece()->getColor() == 'r'){
		opposite = 'b';
	}
	else{
		opposite = 'r';
	}

	if (str.compare("downleft") == 0){
		if ((board[row + 2][col - 2].isItEmpty() && !board[row + 1][col - 1].isItEmpty() && board[row + 1][col - 1].getPiece()->getColor() == opposite)){
			return true;
		}
		else return false;
	}
	else if (str.compare("downright") == 0){
		if ((board[row + 2][col + 2].isItEmpty() && !board[row + 1][col + 1].isItEmpty() && board[row + 1][col + 1].getPiece()->getColor() == opposite)){
			return true;
		}
		else return false;
	}
	else if (str.compare("topleft") == 0){
		if ((board[row - 2][col - 2].isItEmpty() && !board[row - 1][col - 1].isItEmpty() && board[row - 1][col - 1].getPiece()->getColor() == opposite)){
			return true;
		}
		else return false;
	}
	else if (str.compare("topright") == 0){
		if ((board[row - 2][col + 2].isItEmpty() && !board[row - 1][col + 1].isItEmpty() && board[row - 1][col + 1].getPiece()->getColor() == opposite)){
			return true;
		}
		else return false;
	}
	else{
		cout << "invalid criteria" << endl;
		return false;
	}

}

void Board::changeTurn(){
	if (isRedTurn)
		isRedTurn = false;
	else
		isRedTurn = true;
}

#endif