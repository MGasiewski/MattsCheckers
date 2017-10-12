#pragma once
#include "stdafx.h"
#include <vector>
#include "board_model.h"
#include "king_module.h"

king_module::king_module(){}

king_module::~king_module(){}

vector<vector<int>> king_module::get_moves(vector<vector<int>>* board_matrix, int king_y, int king_x) {
	vector<vector<int>> moves;
	if (king_y != 0 && king_x - 1 >= 0 && (*board_matrix).at(king_y - 1).at(king_x - 1) == 0) {
		vector<int> move;
		move.push_back(king_x - 1);
		move.push_back(king_y - 1);
		moves.push_back(move);
	}
	if (king_y != 0 && king_x + 1 < 8 && (*board_matrix).at(king_y - 1).at(king_x + 1) == 0) {
		vector<int> move;
		move.push_back(king_x + 1);
		move.push_back(king_y - 1);
		moves.push_back(move);
	}
	if (king_y != 7 && king_x - 1 >= 0 && (*board_matrix).at(king_y + 1).at(king_x - 1) == 0) {
		vector<int> move;
		move.push_back(king_x - 1);
		move.push_back(king_y + 1);
		moves.push_back(move);
	}
	if (king_y != 7 && king_x + 1 < 8 && (*board_matrix).at(king_y + 1).at(king_x + 1) == 0) {
		vector<int> move;
		move.push_back(king_x + 1);
		move.push_back(king_y + 1);
		moves.push_back(move);
	}
	return moves;
}

vector<vector<int>> king_module::get_jumps(vector<vector<int>>* board_matrix, int king_y, int king_x) {
	vector<vector<int>> jumps;
	if (king_y - 2 >= 0 && king_x - 2 >= 0 && (*board_matrix).at(king_y - 1).at(king_x - 1) == 1) {
		if ((*board_matrix).at(king_y - 2).at(king_x - 2) == 0) {
			vector<int> jump;
			jump.push_back(king_x - 1);
			jump.push_back(king_y - 1);
			jump.push_back(king_x - 2);
			jump.push_back(king_y - 2);
			jumps.push_back(jump);
		}
	}
	if (king_y - 2 >= 0 && king_x + 2 < 8 && (*board_matrix).at(king_y - 1).at(king_x + 1) == 1) {
		if ((*board_matrix).at(king_y - 2).at(king_x + 2) == 0) {
			vector<int> jump;
			jump.push_back(king_x + 1);
			jump.push_back(king_y - 1);
			jump.push_back(king_x + 2);
			jump.push_back(king_y - 2);
			jumps.push_back(jump);
		}
	}
	if (king_y + 2 < 8 && king_x - 2 >= 0 && (*board_matrix).at(king_y + 1).at(king_x - 1) == 1) {
		if ((*board_matrix).at(king_y + 2).at(king_x - 2) == 0) {
			vector<int> jump;
			jump.push_back(king_x - 1);
			jump.push_back(king_y + 1);
			jump.push_back(king_x - 2);
			jump.push_back(king_y + 2);
			jumps.push_back(jump);
		}
	}
	if (king_y + 2 < 8 && king_x + 2 < 8 && (*board_matrix).at(king_y + 1).at(king_x + 1) == 1) {
		if ((*board_matrix).at(king_y + 2).at(king_x + 2) == 0) {
			vector<int> jump;
			jump.push_back(king_x + 1);
			jump.push_back(king_y + 1);
			jump.push_back(king_x + 2);
			jump.push_back(king_y + 2);
			jumps.push_back(jump);
		}
	}
}