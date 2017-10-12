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
	if (player_y - 2 >= 0 && player_x + 2 < 8 && game_matrix.at(player_y - 1).at(player_x + 1) == 1) {
		if (game_matrix.at(player_y - 2).at(player_x + 2) == 0) {
			return true;
		}
	}
	if (player_y - 2 >= 0 && player_x - 2 >= 0 && game_matrix.at(player_y - 1).at(player_x-1)==1) {
		if ( game_matrix.at(player_y - 2).at(player_x - 2) == 0) {
			return true;
		}
	}
	return false;
}

vector<vector<int>> game_logic::combine(vector<int> jump, vector<vector<int>> additional_jumps) {
	vector<vector<int>> combined_jumps;
	for (auto additional_jump : additional_jumps) {
		vector<int> new_jump = jump;
		for (auto value : additional_jump) {
			new_jump.push_back(value);
		}
		combined_jumps.push_back(new_jump);
	}
	return combined_jumps;
}

vector<vector<int>> game_logic::get_jumps(int player_x, int player_y) {
	vector<vector<int>> game_matrix = *(model->get_board_matrix());
	vector<vector<int>> jumps;
	if (player_x + 2 < 8 && player_y - 2 >= 0) {
		if (game_matrix[player_y - 1][player_x + 1] == 1 && game_matrix[player_y - 2][player_x + 2] == 0) {
			vector<int> move;
			move.push_back(player_x + 2);
			move.push_back(player_y - 2);
			move.push_back(player_x + 1);
			move.push_back(player_y - 1);
			jumps.push_back(move);
		}
	}
	if (player_x - 2 >= 0 && player_y - 2 >= 0) {
		if (game_matrix[player_y - 1][player_x - 1] == 1 && game_matrix[player_y - 2][player_x - 2] == 0) {
			vector<int> move;
			move.push_back(player_x - 2);
			move.push_back(player_y - 2);
			move.push_back(player_x - 1);
			move.push_back(player_y - 1);
			jumps.push_back(move);
		}
	}
	vector<vector<int>> final_jumps;
	for (auto jump : jumps) {
		if (can_jump(jump[0], jump[1])) {
			vector<vector<int>> combined_jumps = combine(jump, get_jumps(jump[0], jump[1]));
			for (auto combined_jump : combined_jumps) {
				final_jumps.push_back(combined_jump);
			}
		}
		else {
			final_jumps.push_back(jump);
		}
	}
	return final_jumps;
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

void game_logic::make_kings() {
	vector<vector<int>>* board_matrix = model->get_board_matrix();
	for (int i = 0; i < 8; i++) {
		if ((*board_matrix).at(0).at(i) == 2) {
			(*board_matrix).at(0).at(i) = 12;
		}
		if ((*board_matrix).at(7).at(i) == 1) {
			(*board_matrix).at(7).at(i) = 11;
		}
	}
}

void game_logic::execute_move(vector<int> move, int& user_x, int& user_y) {
	vector<vector<int>>* board_matrix = (*model).get_board_matrix();
	int piece_value = (*board_matrix)[user_y][user_x];
	(*board_matrix)[user_y][user_x] = 0;
	//TODO implement correct placement after double (multi) jump
	for (int i = 2; i < move.size(); i += 2) {
		(*board_matrix)[move[i + 1]][move[i]] = 0;
	}
	if (move.size() < 5) {
		user_y = move.at(1);
		user_x = move.at(0);
	}
	else {
		user_y = move[move.size() - 3];
		user_x = move[move.size() - 4];
	}
	(*board_matrix)[user_y][user_x] = piece_value;
	
}

game_logic::~game_logic() {
}

void game_logic::handle_movement(vector<vector<int>> moves, int& user_x, int& user_y) {
	bool selected = true;
	vector<vector<int>>::iterator it = moves.begin();
	if ((*it).size() < 5) {
		view.print_board_with_moves(moves, (*it)[0], (*it)[1]);
	}
	else {
		view.print_board_with_moves(moves, (*it)[(*it).size() - 4], (*it)[(*it).size() - 3]);
	}
	cout << "Press LEFT and RIGHT to cycle through moves. Press space to execute move, or escape to select another piece";
	int c = _getch();
	while (selected) {
		switch (c)
		{
		case KEY_RIGHT:
			if (it == moves.end()-1) {
				it = moves.begin();
				if ((*it).size() < 5){
					view.print_board_with_moves(moves, (*it)[0], (*it)[1]);
				}
				else {
					view.print_board_with_moves(moves, (*it)[(*it).size() - 4], (*it)[(*it).size() - 3]);
				}
			}
			else {
				it++;
				if ((*it).size() < 5) {
					view.print_board_with_moves(moves, (*it)[0], (*it)[1]);
				}
				else {
					view.print_board_with_moves(moves, (*it)[(*it).size() - 4], (*it)[(*it).size() - 3]);
				}
			}
			break;
		case KEY_LEFT:
			if (it == moves.begin()) {
				it = moves.end()-1;
				if ((*it).size() < 5) {
					view.print_board_with_moves(moves, (*it)[0], (*it)[1]);
				}
				else {
					view.print_board_with_moves(moves, (*it)[(*it).size() - 4], (*it)[(*it).size() - 3]);
				}
			}
			else {
				it--;
				if ((*it).size() < 5) {
					view.print_board_with_moves(moves, (*it)[0], (*it)[1]);
				}
				else {
					view.print_board_with_moves(moves, (*it)[(*it).size() - 4], (*it)[(*it).size() - 3]);
				}
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
			make_kings();
			this->intelligence.do_move(model);
			make_kings();
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