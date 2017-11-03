#include "stdafx.h"
#include "artificial_intelligence.h"
#include "king_module.h"
#include <iostream>
#include <vector>
#include <random>
#define WHITE 1
#define WHITE_KING 11
#define BLACK 2
#define BLACK_KING 12

using namespace std;

artificial_intelligence::artificial_intelligence()
{
}

artificial_intelligence::~artificial_intelligence()
{
}


vector<vector<int>> artificial_intelligence::get_pieces(vector<vector<int>> board_matrix, bool king, bool white) {
	vector<vector<int>> pieces;
	int piece_value;
	if(king && white){
		piece_value = WHITE_KING;
	}
	else if(!king && white) {
		piece_value = WHITE;
	}
	else if (king && !white) {
		piece_value = BLACK_KING;
	}
	else {
		piece_value = BLACK;
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if ((board_matrix)[i][j] == piece_value) {
				vector<int> position;
				position.push_back(i);
				position.push_back(j);
				pieces.push_back(position);
			}
		}
	}
	return pieces;
}

vector<vector<int>> artificial_intelligence::get_all_possible_moves(bool white, vector<vector<int>> board_matrix) {
	vector<vector<int>> pieces;
	vector<vector<int>> kings;
	if (white) {
		pieces = get_pieces(*model->get_board_matrix(), false, true);
		kings = get_pieces(*model->get_board_matrix(), true, true);
	}
	else {
		pieces = get_pieces(*model->get_board_matrix(), false, false);
		kings = get_pieces(*model->get_board_matrix(), true, false);
	}
	vector<vector<int>>* ptr_board_matrix = &board_matrix;
	vector<vector<int>> moves;
	if (white) {
		rpm.set_opposing_color(BLACK);
	}
	else {
		rpm.set_opposing_color(WHITE);
	}
	for (auto piece : pieces) {
		vector<vector<int>> piece_moves = rpm.get_moves(piece);
		moves.insert(moves.end(), piece_moves.begin(), piece_moves.end());
	}
	vector<vector<int>> final_jumps;
	for (auto piece : pieces) {
		vector<vector<int>> jumps = rpm.get_jumps(piece);
		final_jumps.insert(final_jumps.end(), jumps.begin(), jumps.end());
	}
	vector<vector<int>> king_jumps;
	for (auto king : kings) {
		vector<vector<int>> jumps = km.get_moves(ptr_board_matrix, king[0], king[1]);
	}
	moves.insert(moves.end(), final_jumps.begin(), final_jumps.end());
	moves.insert(moves.end(), king_jumps.begin(), king_jumps.begin());
	return moves;
}

vector<int> artificial_intelligence::get_random_move(vector<vector<int>> moves) {
	mt19937 rng;
	rng.seed(random_device()());
	uniform_int_distribution<mt19937::result_type> dist(0, moves.size() - 1);
	int choice = dist(rng);
	vector<int> move = moves[choice];
	return move;
}


int artificial_intelligence::board_score(vector<vector<int>> board_matrix) {
	int piece_difference = get_pieces(board_matrix, false, true).size() - get_pieces(board_matrix, false, true).size();
	int king_difference = get_pieces(board_matrix, false, true).size() - get_pieces(board_matrix, false, true).size();
	return 2 * king_difference + piece_difference;
}

int artificial_intelligence::score_move(vector<int> move, vector<vector<int>> board_matrix, int depth, bool max) {
	board_matrix = execute_move(move, board_matrix);
	if (depth == 0) {
		return board_score(board_matrix);
	}
	else {
		if (max) {
			int max_val = -1;
			vector<vector<int>> move_set = get_all_possible_moves(true, board_matrix);
			for (auto move : move_set) {
				int value = score_move(move, board_matrix, depth-1, !max);
				if (value > max_val) {
					max_val = value;
				}
			}
			return max_val;
		}
		else {
			int min_val = 9999;
			vector<vector<int>> move_set = get_all_possible_moves(false, board_matrix);
			for (auto move : move_set) {
				int value = score_move(move, board_matrix, depth - 1, !max);
				if (value < min_val) {
					min_val = value;
				}
			}
			return min_val;

		}
	}
}


vector<vector<int>> artificial_intelligence::execute_move(vector<int> move, vector<vector<int>> board_matrix) {
	for (int i = 0; i < move.size() - 2; i += 2) {
		board_matrix.at(move[i]).at(move[i + 1]) = 0;
	}
	board_matrix.at(move[move.size() - 2]).at(move[move.size() - 1]) = 1;
	return board_matrix;
}

void artificial_intelligence::do_move(board_model* model) {
	km.set_opposing_color(2);
	this->rpm = regular_piece_module(model);
	this->model = model;
	vector<vector<int>>* board_matrix = model->get_board_matrix();
	vector<vector<int>> moves = get_all_possible_moves(true, *board_matrix);
	int high_score = 0;
	vector<int> final_move;
	for (auto move : moves) {
		int score = score_move(move, *board_matrix, 3, false);
		if (score > high_score) {
			high_score = score;
			final_move = move;
		}
	}
	if (final_move.empty()) {
		final_move = get_random_move(moves);
		int x;
		cout << "press any key to continue" << endl;
		cin >> x;
	}
	*board_matrix = execute_move(final_move, *board_matrix);
}




