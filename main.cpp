#include <iostream>
#include<cstdlib>
#include <windows.h>
#include "G:\Apps\GIT\colors\color-console\include\color.hpp"

using namespace std;

const int BOARD_SIZE = 10;
const int TOTAL_SHIPS = 15;
int player_score, enemy_score;

void setColor(int color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

int getIntegerInput() {
	int number;

	// Loop until the user enters a valid integer
	while (true) {

		std::cin >> number;

		// Check if the input is valid
		if (std::cin.fail()) {
			std::cin.clear(); // clear the error flag
			std::cin.ignore(10000, '\n'); // discard invalid input up to 10,000 characters
			std::cout << "(0-9)\n";
		}
		else {
			std::cin.ignore(10000, '\n'); // discard any extra characters in the input buffer
			return number; // valid integer input
		}
	}
}

void Victory()
{
	system("cls");
	setColor(2);
	cout << "You Won!\n\n";
	setColor(7);
	//system("pause");
	exit(0);
}

void Defeat()
{
	system("cls");
	setColor(4);
	cout << "You Lost!\n\n";
	setColor(7);
	//system("pause");
	exit(0);
}

void displayBoard(char board[BOARD_SIZE][BOARD_SIZE], bool isEnemyBoard = false)
{
	// Print horizontal header row
	cout << "  ";
	for (int i = 0; i < BOARD_SIZE; i++) {
		cout << i << " ";
	}
	cout << endl;

	// Print the board
	for (int i = 0; i < BOARD_SIZE; i++) {
		cout << i << " ";
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (isEnemyBoard && board[i][j] == 'S') {
				// Display enemy ships as water ('~') to keep them hidden
				setColor(9);
				cout << '~' << " ";
				setColor(7);
			}
			else if (board[i][j] == 'S') {
				setColor(12); // Red for ships
				cout << board[i][j] << " ";
				setColor(7);
			}
			else if (board[i][j] == '~')
			{
				setColor(9);
				cout << board[i][j] << " ";
				setColor(7);
			}
			else if (board[i][j] == 'X')
			{
				setColor(4);
				cout << board[i][j] << " ";
				setColor(7);
			}
			else if (board[i][j] == '0')
			{
				setColor(8);
				cout << board[i][j] << " ";
				setColor(7);
			}
			else {
				cout << board[i][j] << " "; // Print normally for other characters
			}
		}
		cout << endl;
	}
	cout << endl;
}

bool canPlaceShip(char board[BOARD_SIZE][BOARD_SIZE], int size, bool direction, int col, int row)
{
	if (direction == 1)
	{
		if (col + size > BOARD_SIZE)
		{
			return false;
		}
		for (int i = 0; i < size; i++)
		{
			if (board[row][col + i] != '~')
			{
				return false;
			}
		}
	}

	if (direction == 0)
	{
		if (row + size > BOARD_SIZE)
		{
			return false;
		}
		for (int i = 0; i < size; i++)
		{
			if (board[row + i][col] != '~')
			{
				return false;
			}
		}
	}
	return true;
}

void placeShip(char board[BOARD_SIZE][BOARD_SIZE], int size) {
	bool placed = false;
	while (!placed) {
		// Randomly choose row, column, and orientation
		int row = rand() % BOARD_SIZE;
		int col = rand() % BOARD_SIZE;
		bool horizontal = rand() % 2;

		if (canPlaceShip(board, size, horizontal, col, row) == true) {
			if (horizontal) {
				for (int i = 0; i < size; i++) {

					board[row][col + i] = 'S';  // Place horizontally
				}
			}
			else {
				for (int i = 0; i < size; i++) {
					board[row + i][col] = 'S';  // Place vertically
				}
			}
			placed = true;  // Ship placed successfully
		}
	}
}

void setUpTheMap(char Player_Board[BOARD_SIZE][BOARD_SIZE], char Enemy_Board[BOARD_SIZE][BOARD_SIZE])
{
	/////////////////
	srand(time(0));

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {

			Player_Board[i][j] = '~';
			Enemy_Board[i][j] = '~';
		}

	}
	setColor(7);
	placeShip(Player_Board, 5);
	placeShip(Player_Board, 4);
	placeShip(Player_Board, 3);
	placeShip(Player_Board, 2);
	placeShip(Player_Board, 1);

	placeShip(Enemy_Board, 5);
	placeShip(Enemy_Board, 4);
	placeShip(Enemy_Board, 3);
	placeShip(Enemy_Board, 2);
	placeShip(Enemy_Board, 1);

	setColor(2);
	cout << "Your Board" << endl;
	setColor(7);
	displayBoard(Player_Board	);


	setColor(4);
	cout << "Enemy Board" << endl;
	setColor(7);
	displayBoard(Enemy_Board,true);

}

void gameCycle(char Player_Board[BOARD_SIZE][BOARD_SIZE], char Enemy_Board[BOARD_SIZE][BOARD_SIZE], bool& isPlayerMove)
{
	int x, y;
	bool isRightCoordinates = false;

	if (isPlayerMove) // Player's turn
	{
		cout << "Enter coordinates (x y): ";
		x = getIntegerInput();
		y = getIntegerInput();

		if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE && Enemy_Board[x][y] != '0') {
			isRightCoordinates = true;
		}
		if (x == 888 && y == 888)
		{
			cout << endl;
			cout << dye::yellow_on_black("Congrats, u found an easter egg\n");
			displayBoard(Enemy_Board, false);
			system("pause");
		}


		if (isRightCoordinates) {
			if (Enemy_Board[x][y] == '~') {
				Enemy_Board[x][y] = '0'; // Mark miss
				setColor(4);
				cout << "It's a miss!\n\n";
				setColor(7);
				isPlayerMove = false;
			}
			else if (Enemy_Board[x][y] == 'S') {
				player_score++;
				Enemy_Board[x][y] = 'X'; // Mark hit
				setColor(2);
				cout << "It's a hit! Your score: " << player_score << "\n\n";
				setColor(7);
				isPlayerMove = true;
			}
			 // Now it's the enemy's turn
		}
		else {
			cout << "Invalid coordinates. Try again.\n";
		}
	}
	else // Enemy's turn
	{
		bool enemyMoveComplete = false;
		while (!enemyMoveComplete) {
			x = rand() % BOARD_SIZE;
			y = rand() % BOARD_SIZE;

			if (Player_Board[x][y] == '~') {
				Player_Board[x][y] = '0'; // Mark miss
				enemyMoveComplete = true;
				isPlayerMove = true; // Now it's the player's turn
			}
			else if (Player_Board[x][y] == 'S') {
				enemy_score++;
				Player_Board[x][y] = 'X'; // Mark hit
				enemyMoveComplete = true;
				isPlayerMove = true; // Now it's the player's turn
				setColor(4);
				cout << "Enemy hit your ship!\n";
				setColor(7);
			}
		}
	}
	system("cls");
	if (player_score >= TOTAL_SHIPS)
	{
		Victory();
	}
	else if (enemy_score >= TOTAL_SHIPS)
	{
		Defeat();
	}
}

int main()
{
	char Player_Board[BOARD_SIZE][BOARD_SIZE]; // board array
	char Enemy_Board[BOARD_SIZE][BOARD_SIZE];
	int size;
	bool gameOver = false;
	bool isPlayerMove = true;

	setUpTheMap(Player_Board, Enemy_Board);

	while (!gameOver)
	{
		gameCycle(Player_Board, Enemy_Board, isPlayerMove);

		setColor(2);
		cout << "Your Board\n";
		setColor(7);
		displayBoard(Player_Board);

		setColor(12);
		cout << "Enemy Board\n";
		setColor(7);
		displayBoard(Enemy_Board,true);

		setColor(2);
		cout << player_score;
		setColor(7);
		cout << " : ";
		setColor(12);
		cout << enemy_score << "\n\n";
		setColor(7);

	}

	system("pause");
	return 0;
}