#pragma once
#include "stdafx.h"
#include <vector>
#include "board_model.h"
#include "king_module.h"
#define LOWER_LEFT 1
#define LOWER_RIGHT 2
#define UPPER_LEFT 3
#define UPPER_RIGHT 4

king_module::king_module(){}

king_module::~king_module(){}

vector<vector<int>> king_module::get_moves(vector<vector<int>>* board_matrix, int king_y, int king_x) {
	vector<vector<int>> moves;
	if (king_y != 0 && king_x - 1 >= 0 && (*board_matrix).at(king_y - 1).at(king_x - 1) == 0) {
		vector<int> move;
		move.push_back(king_y);
		move.push_back(king_x);
		move.push_back(king_y - 1);
		move.push_back(king_x - 1);
		moves.push_back(move);
	}
	if (king_y != 0 && king_x + 1 < 8 && (*board_matrix).at(king_y - 1).at(king_x + 1) == 0) {
		vector<int> move;
		move.push_back(king_y);
		move.push_back(king_x);
		move.push_back(king_y - 1);
		move.push_back(king_x + 1);
		moves.push_back(move);
	}
	if (king_y != 7 && king_x - 1 >= 0 && (*board_matrix).at(king_y + 1).at(king_x - 1) == 0) {
		vector<int> move;
		move.push_back(king_y);
		move.push_back(king_x);
		move.push_back(king_y + 1);
		move.push_back(king_x - 1);
		moves.push_back(move);
	}
	if (king_y != 7 && king_x + 1 < 8 && (*board_matrix).at(king_y + 1).at(king_x + 1) == 0) {
		vector<int> move;
		move.push_back(king_y);
		move.push_back(king_x);
		move.push_back(king_y + 1);
		move.push_back(king_x + 1);
		moves.push_back(move);
	}
	vector<vector<int>> jumps = get_jumps(board_matrix, king_y, king_x, 0);
	for (auto jump : jumps) {
		moves.push_back(jump);
	}
	return moves;
}

vector<vector<int>> king_module::combine(vector<int> jump, vector<vector<int>> additional_jumps) {
	vector<vector<int>> combined_jumps;
	if (!additional_jumps.empty()) {
		for (auto additional_jump : additional_jumps) {
			vector<int> new_jump = jump;
			for (auto value : additional_jump) {
				new_jump.push_back(value);
			}
			combined_jumps.push_back(new_jump);
		}
	}
	else {
		combined_jumps.push_back(jump);
	}
	return combined_jumps;
}

vector<vector<int>> king_module::get_jumps(vector<vector<int>>* board_matrix, int king_y, int king_x, int direction) {
	vector<vector<int>> jumps;
	if (king_y - 2 >= 0 && king_x - 2 >= 0 && (*board_matrix).at(king_y - 1).at(king_x - 1) == 1) {
		if ((*board_matrix).at(king_y - 2).at(king_x - 2) == 0 && direction!=LOWER_RIGHT) {
			vector<int> jump;
			jump.push_back(king_y);
			jump.push_back(king_x);
			jump.push_back(king_y - 1);
			jump.push_back(king_x - 1);
			jump.push_back(king_y - 2);
			jump.push_back(king_x - 2);
			jump.push_back(UPPER_LEFT);
			jumps.push_back(jump);
		}
	}
	if (king_y - 2 >= 0 && king_x + 2 < 8 && (*board_matrix).at(king_y - 1).at(king_x + 1) == 1) {
		if ((*board_matrix).at(king_y - 2).at(king_x + 2) == 0 && direction!=LOWER_LEFT) {
			vector<int> jump;
			jump.push_back(king_y);
			jump.push_back(king_x);
			jump.push_back(king_y - 1);
			jump.push_back(king_x + 1);
			jump.push_back(king_y - 2);
			jump.push_back(king_x + 2);
			jump.push_back(UPPER_RIGHT);
			jumps.push_back(jump);
		}
	}
	if (king_y + 2 < 8 && king_x - 2 >= 0 && (*board_matrix).at(king_y + 1).at(king_x - 1) == 1) {
		if ((*board_matrix).at(king_y + 2).at(king_x - 2) == 0 && direction!=UPPER_RIGHT) {
			vector<int> jump;
			jump.push_back(king_y);
			jump.push_back(king_x);
			jump.push_back(king_y + 1);
			jump.push_back(king_x - 1);
			jump.push_back(king_y + 2);
			jump.push_back(king_x - 2);
			jump.push_back(LOWER_LEFT);
			jumps.push_back(jump);
		}
	}
	if (king_y + 2 < 8 && king_x + 2 < 8 && (*board_matrix).at(king_y + 1).at(king_x + 1) == 1) {
		if ((*board_matrix).at(king_y + 2).at(king_x + 2) == 0 && direction!=UPPER_LEFT) {
			vector<int> jump;
			jump.push_back(king_y);
			jump.push_back(king_x);
			jump.push_back(king_y + 1);
			jump.push_back(king_x + 1);
			jump.push_back(king_y + 2);
			jump.push_back(king_x + 2);
			jump.push_back(LOWER_RIGHT);
			jumps.push_back(jump);
		}
	}
	vector<vector<int>> final_jumps;
	for (auto jump : jumps) {
		int jump_direction = jump.back();
		jump.pop_back();
		vector<vector<int>> secondary_jumps = get_jumps(board_matrix, jump.at(jump.size()-2), jump.at(jump.size()-1), jump_direction);
		if (secondary_jumps.size() > 0) {
			vector<vector<int>> combined_jumps = combine(jump, secondary_jumps);
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