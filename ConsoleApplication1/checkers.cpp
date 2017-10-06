// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "board_model.h"
#include "game_controller.h"
#include "board_view.h"
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define SPACE 32

using namespace std;

int main()
{
	board_model board;
	game_controller controller;
	board_view view;
	controller.set_board_view(view);
	controller.set_board_model(board);
	int user_x = 2;
	int user_y = 5;
	view.print_board(user_x, user_y);
	int c = 0;
	while (1)
	{
		c = _getch();
		controller.handle_user_input(c, user_x, user_y);
		vector<vector<int>> valid_moves;
		valid_moves = controller.get_valid_moves_black(board, user_x, user_y);
		for (auto valid_move : valid_moves) {
			for (auto coord : valid_move) {
				cout << coord << " ";
			}
			cout << endl;
		}
	}
    return 0;
}
