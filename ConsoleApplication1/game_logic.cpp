#pragma once
#include "stdafx.h"
#include <vector>
#include "game_logic.h"
#include <conio.h>
#include <iostream>
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define SPACE 32
#define ESC 27

using namespace std;

game_logic::game_logic(board_model* model, board_view view){
	this->model = model;
	this->view = view;
}

game_logic::game_logic() {
}

void game_logic::execute_move(vector<int> move, int& user_x, int& user_y) {
	vector<vector<int>>* board_matrix = (*model).get_board_matrix();
	(*board_matrix)[user_y][user_x] = 0;
	(*board_matrix)[move.at(1)][move.at(0)] = 2;
	user_y = move.at(1);
	user_x = move.at(0);
}

game_logic::~game_logic() {
}

void game_logic::handle_movement(vector<vector<int>> moves, int& user_x, int& user_y) {
	bool selected = true;
	int c = 0;
	vector<vector<int>>::iterator it = moves.begin();
	while (selected) {
		view.print_board_with_moves(moves, (*it).at(0), (*it).at(1));
		cout << "Press LEFT and RIGHT to cycle through moves. Press space to execute move, or escape to select another piece";
		switch (c)
		{
		case KEY_RIGHT:
			if (it == moves.end()-1) {
				it = moves.begin();
			}
			else {
				it++;
			}
			break;
		case KEY_LEFT:
			if (it == moves.begin()) {
				it = moves.end()-1;
			}
			else {
				it--;
			}
			break;
		case ESC:
			selected = false;
			view.clear_move_data(moves);
			view.print_board(user_x, user_y);
			break;
		case SPACE:
			execute_move(*it, user_x, user_y);
			view.clear_move_data(moves);
			view.print_board(user_x, user_y);
			selected = false;
			break;
		default:
			break;
		}
		if(c!=SPACE)
			c = _getch();
	}
}