#include <iostream>
#include "Board.h"

using namespace std;

void adjustScreen();
void StartScreen();
void Play();

int main(){

	int x1, x2, y1, y2;
	char c;
	Board *myBoard = new Board(8);

	adjustScreen();

	do{
		//Refreshing board
		system("cls");
		myBoard->displayBoard();

		//Players Messages
		cout << "\n\n\t\t   It is ";
		if (myBoard->isRedTurn) cout << "Red's turn:\n\t\t   ";
		else cout << "Blue's turn:\n\t\t   ";
		cout << "\n\t\t   from: ";

		//Getting Input
		cin >> x1; cin >> y1; cout << "\t\t   to: "; cin >> x2;  cin >> y2;
		myBoard->realAction(x1, y1, x2, y2);
		if (myBoard->goodAction && myBoard->canPieceAttack(x2, y2))
			myBoard->changeTurn();
		cout << endl;
	} while (x1 != -1);


	system("pause");
	return 0;
}


void adjustScreen(){
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, 750, 675, TRUE); // 800 width, 800 height
}
