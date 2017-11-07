#include "stdafx.h"
#include <vector>
#include "regular_piece_module.h"
#include "board_model.h"

using namespace std;

regular_piece_module::regular_piece_module() {
}

regular_piece_module::~regular_piece_module() {
}

void regular_piece_module::set_opposing_color(int color) {
	if (color == 1) {
		opposing_color = color;
		direction = -1;
	}
	else if (color == 2) {
		opposing_color = color;
		direction = 1;
	}
}

bool regular_piece_module::under_limit_for_move(vector<int> position) {
	if (opposing_color == 1 && position.at(0) - 1 >= 0) {
		return true;
	}
	if (opposing_color == 2 && position.at(0) + 1 < 8) {
		return true;
	}
	else {
	}
		return false;
}

vector<vector<int>> regular_piece_module::get_moves(vector<int> position, vector<vector<int>> board_matrix)
{
	vector<vector<int>> moves;
	if (under_limit_for_move(position) && position[1] + 1 < 8 && board_matrix[position[0] + direction][position[1] + 1] == 0) {
		vector<int> move;
		move.push_back(position[0]);
		move.push_back(position[1]);
		move.push_back(position[0] + direction);
		move.push_back(position[1] + 1);
		moves.push_back(move);
	}
	if (under_limit_for_move(position) && position[1] - 1 >= 0 && board_matrix[position[0] + direction][position[1] - 1] == 0) {
		vector<int> move;
		move.push_back(position[0]);
		move.push_back(position[1]);
		move.push_back(position[0] + direction);
		move.push_back(position[1] - 1);
		moves.push_back(move);
	}
	return moves;
}

vector<vector<int>> regular_piece_module::combine(vector<int> jump, vector<vector<int>> additional_jumps) {
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

bool regular_piece_module::under_limit_for_jump(vector<int> position) {
	if (opposing_color == 1 && position.at(0) - 2 >= 0) {
		return true;
	}
	if(opposing_color == 2 && position.at(0) + 2 < 8) {
		return true;
	}
	else {
		return false;
	}
}

vector<vector<int>> regular_piece_module::get_jumps(vector<int> position, vector<vector<int>> board_matrix) {
	vector<vector<int>> jumps;
	if (under_limit_for_jump(position) && position.at(1) + 2 < 8) {
		if (board_matrix[position[0] + direction][position[1] + 1] % 10 == opposing_color && board_matrix[position[0] + 2 * direction][position[1] + 2] == 0) {
			vector<int> move;
			move.push_back(position[0]);
 			move.push_back(position[1]);
			move.push_back(position[0] + direction);
			move.push_back(position[1] + 1);
			move.push_back(position[0] + 2 * direction);
			move.push_back(position[1] + 2);
			jumps.push_back(move);
		}
	}
	if (under_limit_for_jump(position) && position.at(1) - 2 >= 0) {
		if (board_matrix[position[0] + direction ][position[1] - 1] % 10 == opposing_color && board_matrix[position[0] + 2 * direction][position[1] - 2] == 0) {
			vector<int> move;
			move.push_back(position[0]);
			move.push_back(position[1]);
			move.push_back(position[0] + direction);
			move.push_back(position[1] - 1);
			move.push_back(position[0] + 2 * direction);
			move.push_back(position[1] - 2);
			jumps.push_back(move);
		}
	}
	vector<vector<int>> final_jumps;
	for (auto jump : jumps) {
		vector<int> final_pos;
		final_pos.push_back(jump.at(jump.size() - 2));
		final_pos.push_back(jump.at(jump.size() - 1));
		if (get_jumps(final_pos, board_matrix).size() > 0) {
			vector<vector<int>> combined_jumps = combine(jump, get_jumps(final_pos, board_matrix));
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
