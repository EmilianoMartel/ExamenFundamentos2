#include <iostream>
#include <sstream>
#include <conio.h>
#include <Windows.h>

#define MAX_WIDTH 5
#define MAX_HEIGHT 5

using namespace std;

const string TITLE = "Lidian and the Crystal Heart";

struct Vector2 {
	int X = 0;
	int Y = 0;
	void print() {
		cout << "Position is = " << X << " " << Y << endl;
	}
} position;

Vector2 tempPosition;
Vector2 playerOriginalPosition;
Vector2 crystalOriginalPosition;

struct Tile {
	Vector2 position;
	char graphic = 'X';
	bool hasPlayer = false;
	bool hasCrystal = false;
};

Tile player;
Tile Dirt;
Tile Hole;
Tile Crystal;
Tile Tree;
Tile Exit;
Tile Sand;

Tile map[MAX_WIDTH][MAX_HEIGHT]{
	{Dirt, Hole, Dirt, Dirt, Tree},
	{Dirt, Dirt, Dirt, Dirt, Tree},
	{Hole, Dirt, Sand, Sand, Tree},
	{Dirt, Dirt, Dirt, Dirt, Dirt},
	{Dirt, Tree, Tree, Hole, Exit}
};

bool rePlay = true;
int inputOption = 0;

int CheckIntInput(int cant) {
	string input;
	bool inputValue = false;
	int inputNum = 1;

	do {
		cout << "Enter a option: " << endl;
		getline(cin, input);

		istringstream stream(input);

		if (stream >> inputNum) {
			inputValue = true;
			if (inputNum > cant) {
				cout << "The input is out of range. Please try again" << endl;
				inputValue = false;
			}
		}
		else {
			cout << "Invalid input. Please try again." << endl;
		}
	} while (!inputValue);

	return inputNum;
}

void PressAnyButton() {
	cout << "Press any key to continue..." << endl;
	getchar();
	system("cls");
}

void Intro() {
	cout << "Ledian ventures into an Amazonas rainforest to get the sacret Heart of Crystal." << endl;
	cout << "This artifact allows you to enchant any creature or person who lives in the world" << endl;
	cout << "But despite the great power of him, His defect is his fragility," << endl;
	cout << "since any change rough on the ground, the heart will break and his power will disappear forever." << endl;
	PressAnyButton();
}

void Instructions() {
	system("cls");
	cout << "Your mission is to take the Crystal Heart(H) and escape the rainforest." << endl;
	cout << "You can move with W A S D." << endl;
	cout << "When you dont have a Crystal Heart(H), you can walk over the dirt(X) and sand(S)." << endl;
	cout << "But when you take the Crystal Heart(H), you cant walk over the sand(S) anymore." << endl;
	cout << "If you falling in a hole(O), you lose immediately." << endl;
	cout << "The goal is to reach the exit(E) with the Crystal Heart(H)" << endl;
	cout << "P = Player" << endl;
	cout << "X = Dirt" << endl;
	cout << "S = Sand" << endl;
	cout << "T = Tree" << endl;
	cout << "H = Crystal Heart" << endl;
	cout << "E = Exit" << endl;
	PressAnyButton();
}

void ResetGame() {
	Tile ORIGINAL[MAX_WIDTH][MAX_HEIGHT]{
	{Dirt, Hole, Dirt, Dirt, Tree},
	{Dirt, Dirt, Dirt, Dirt, Tree},
	{Hole, Dirt, Sand, Sand, Tree},
	{Dirt, Dirt, Dirt, Dirt, Dirt},
	{Dirt, Tree, Tree, Hole, Exit}
	};
	playerOriginalPosition.X = 0;
	playerOriginalPosition.Y = 0;
	crystalOriginalPosition.X = 3;
	crystalOriginalPosition.Y = 0;

	for (size_t i = 0; i < MAX_WIDTH; i++)
	{
		for (size_t j = 0; j < MAX_HEIGHT; j++)
		{
			map[i][j] = ORIGINAL[i][j];
			map[i][j].position.X = j;
			map[i][j].position.Y = i;
			if (map[i][j].position.X == playerOriginalPosition.X && map[i][j].position.Y == playerOriginalPosition.Y) {
				map[i][j].hasPlayer = true;
				player.position = playerOriginalPosition;
				tempPosition = player.position;
			}
			else {
				map[i][j].hasPlayer = false;
			}
			if (map[i][j].position.X == crystalOriginalPosition.X && map[i][j].position.Y == crystalOriginalPosition.Y) {
				map[i][j].hasCrystal = true;
				Crystal.position = crystalOriginalPosition;
			}
			else {
				map[i][j].hasCrystal = false;
			}
		}
	}
}

void Replay() {
	int reReplayChoose;
	cout << "¿Play again?." << endl;
	cout << "1 - RePlay" << endl;
	cout << "2 - Back to menu" << endl;
	cout << "3 - Exit" << endl;
	reReplayChoose = CheckIntInput(3);
	switch (reReplayChoose)
	{
	case 1:
		ResetGame();
		cout << "Okey! Good luck!" << endl;
		PressAnyButton();
		break;
	case 2:
		rePlay = false;
		cout << "Back to menu." << endl;
		PressAnyButton();
		break;
	case 3:
		rePlay = false;
		inputOption = 3;
		break;
	default:
		break;
	}
}

void WinOrLoseLogic(string logic) {
	if (logic == "win") {
		cout << "Congratulations, you win!" << endl;
	}
	else {
		cout << "You fail the mission." << endl;
	}
	Replay();
	
}

void ShowMap() {
	for (size_t i = 0; i < MAX_WIDTH; i++)
	{
		cout << endl;
		for (size_t j = 0; j < MAX_HEIGHT; j++)
		{
			if (map[i][j].hasPlayer) {
				cout << player.graphic << " ";
			}
			else if (map[i][j].hasCrystal) {
				cout << Crystal.graphic << " ";
			}
			else {
				cout << map[i][j].graphic << " ";
			}
		}
	}
}

char GetInput() {
	if (_kbhit()) {
		return _getch();
	}
	return '0';
}

void ProcessInput(char input) {
	switch (input)
	{
	case 'w':
		if (tempPosition.Y > 0) {
			tempPosition.Y -= 1;
		}
		break;
	case 'a':
		if (tempPosition.X > 0) {
			tempPosition.X -= 1;
		}
		break;
	case 's':
		if (tempPosition.Y < MAX_HEIGHT) {
			tempPosition.Y += 1;
		}
		break;
	case 'd':
		if (tempPosition.X < MAX_WIDTH) {
			tempPosition.X += 1;
		}
		break;
	default:
		break;
	}
}

void MoveCheck() {
	for (size_t i = 0; i < MAX_WIDTH; i++)
	{
		cout << endl;
		for (size_t j = 0; j < MAX_HEIGHT; j++)
		{
			if (map[i][j].position.X == tempPosition.X && map[i][j].position.Y == tempPosition.Y) {
				char tipeTile = map[i][j].graphic;
				switch (tipeTile)
				{
				case 'X':
					player.position = map[i][j].position;
				case 'S':
					if (player.hasCrystal) {
						tempPosition.X = player.position.X;
						tempPosition.Y = player.position.Y;
					}
					else {
						player.position.X = map[i][j].position.X;
						player.position.Y = map[i][j].position.Y;
					}
					break;
				case 'E':
					player.position = map[i][j].position;
					if (player.hasCrystal) {
						WinOrLoseLogic("win");
					}
					break;
				case 'T':
					tempPosition = player.position;
					break;
				case 'O':
					player.position = map[i][j].position;
					WinOrLoseLogic("lose");
					break;
				default:
					break;
				}
			}
			if (map[i][j].position.X == player.position.X && map[i][j].position.Y == player.position.Y) {
				map[i][j].hasPlayer = true;
				if (map[i][j].hasCrystal) {
					player.hasCrystal = true;
					map[i][j].hasCrystal = false;
					player.position = map[i][j].position;
				}
			}
			else {
				map[i][j].hasPlayer = false;
			}
		}
	}
}

void Game() {
	while (rePlay)
	{
		system("cls");
		ShowMap();
		ProcessInput(GetInput());
		MoveCheck();
		Sleep(100);
	}
}

int main()
{
	Dirt.graphic = 'X';
	Sand.graphic = 'S';
	Exit.graphic = 'E';
	Tree.graphic = 'T';
	Crystal.graphic = 'H';
	Hole.graphic = 'O';
	player.graphic = 'P';

	map[playerOriginalPosition.X][playerOriginalPosition.Y].hasPlayer = true;
	map[crystalOriginalPosition.X][crystalOriginalPosition.Y].hasCrystal = true;

	do
	{
		cout << TITLE << endl;
		cout << "Play" << endl;
		cout << "Instructions" << endl;
		cout << "Exit" << endl;
		inputOption = CheckIntInput(3);
		switch (inputOption)
		{
		case 1:
			rePlay = true;
			ResetGame();
			system("cls");
			Intro();
			Game();
			break;
		case 2:
			Instructions();
			break;
		default:
			break;
		}
	} while (inputOption != 3);
}