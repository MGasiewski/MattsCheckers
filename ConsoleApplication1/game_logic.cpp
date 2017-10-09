#pragma once
#include "stdafx.h"
#include <vector>
#include "game_logic.h"
#include <conio.h>
#include <iostream>
#include "artificial_intelligence.h"
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define SPACE 32
#define ESC 27

using namespace std;

game_logic::game_logic(board_model* model, board_view view){
	this->model = model;
	this->view = view;
	artificial_intelligence ai;
	this->intelligence = ai;
}

game_logic::game_logic() {
}

bool game_logic::can_jump(int player_x, int player_y) {
	vector<vector<int>> game_matrix = *(model->get_board_matrix());
	if (player_y == 7) {
		return false;
	}
	if (game_matrix.at(player_y - 1).at(player_x + 1) == 1) {
		if (player_y - 2 >= 0 && player_x + 2 < 8 && game_matrix.at(player_y - 2).at(player_x + 2) == 0) {
			return true;
		}
	}
	if (game_matrix.at(player_y - 1).at(player_x-1)==1) {
		if (player_y - 2 >= 0 && player_x -2 >= 0 && game_matrix.at(player_y - 2).at(player_x - 2) == 0) {
			return true;
		}
	}
}

vector<vector<int>> game_logic::get_valid_moves(int player_x, int player_y, bool player_white) {
	vector<vector<int>>* game_matrix = model->get_board_matrix();
	vector<vector<int>> valid_moves;
	if (player_y == 0) {
		return valid_moves;
	}
	else if (player_x == 0) {
		if ((*game_matrix).at(player_y - 1).at(player_x + 1) == 0) {
			vector<int> single_move;
			single_move.push_back(player_x + 1);
			single_move.push_back(player_y - 1);
			valid_moves.push_back(single_move);
			return valid_moves;
		}
		else {
			return valid_moves;
		}
	}
	else if (player_x == 7) {
		if ((*game_matrix).at(player_y - 1).at(player_x - 1) == 0) {
			vector<int> single_move;
			single_move.push_back(player_x - 1);
			single_move.push_back(player_y - 1);
			valid_moves.push_back(single_move);
			return valid_moves;
		}
		else {
			return valid_moves;
		}
	}
	else {
 		if ((*game_matrix).at(player_y - 1).at(player_x - 1) == 0) {
			vector<int> single_move;
			single_move.push_back(player_x - 1);
			single_move.push_back(player_y - 1);
			valid_moves.push_back(single_move);
		}
		if ((*game_matrix).at(player_y - 1).at(player_x + 1) == 0) {
			vector<int> single_move;
			single_move.push_back(player_x + 1);
			single_move.push_back(player_y - 1);
			valid_moves.push_back(single_move);
		}
		return valid_moves;
	}
}

void game_logic::execute_move(vector<int> move, int& user_x, int& user_y) {
	vector<vector<int>>* board_matrix = (*model).get_board_matrix();
	(*board_matrix)[user_y][user_x] = 0;
	(*board_matrix)[move.at(1)][move.at(0)] = 2;
	user_y = move.at(1);
	user_x = move.at(0);
	if (move.size() > 2) {
		for (int i = 2; i < move.size(); i += 2) {
			(*board_matrix)[move[i + 1]][move[i]] = 0;
		}
	}
}

game_logic::~game_logic() {
}

void game_logic::handle_movement(vector<vector<int>> moves, int& user_x, int& user_y) {
	bool selected = true;
	vector<vector<int>>::iterator it = moves.begin();
	view.print_board_with_moves(moves, (*it)[0], (*it)[1]);
	cout << "Press LEFT and RIGHT to cycle through moves. Press space to execute move, or escape to select another piece";
	int c = _getch();
	while (selected) {
		switch (c)
		{
		case KEY_RIGHT:
			if (it == moves.end()-1) {
				it = moves.begin();
				view.print_board_with_moves(moves, (*it)[0], (*it)[1]);
			}
			else {
				it++;
				view.print_board_with_moves(moves, (*it)[0], (*it)[1]);
			}
			break;
		case KEY_LEFT:
			if (it == moves.begin()) {
				it = moves.end()-1;
				view.print_board_with_moves(moves, (*it)[0], (*it)[1]);
			}
			else {
				it--;
				view.print_board_with_moves(moves, (*it)[0], (*it)[1]);
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
			this->intelligence.do_move(model);
			view.print_board(user_x, user_y);
			selected = false;
			break;
		default:
			break;
		}
		if(c!=SPACE && c!=ESC)
			c = _getch();
	}
}