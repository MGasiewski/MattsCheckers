#include "stdafx.h"
#include "artificial_intelligence.h"
#include "king_module.h"
#include <iostream>
#include <vector>
#include <random>
#include <cstdlib>
#define STD_DEPTH 4
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
		vector<vector<int>> piece_moves = rpm.get_moves(piece, board_matrix);
		moves.insert(moves.end(), piece_moves.begin(), piece_moves.end());
	}
	for (auto piece : pieces) {
		vector<vector<int>> jumps = rpm.get_jumps(piece, board_matrix);
		moves.insert(moves.end(), jumps.begin(), jumps.end());
	}
	for (auto king : kings) {
		vector<vector<int>> kmoves = km.get_moves(ptr_board_matrix, king[0], king[1]);
		moves.insert(moves.end(), kmoves.begin(), kmoves.end());
	}
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
	int piece_difference = get_pieces(board_matrix, false, true).size() - get_pieces(board_matrix, false, false).size();
	int king_difference = get_pieces(board_matrix, true, true).size() - get_pieces(board_matrix, true, false).size();
	return 2 * king_difference + piece_difference;
}

int artificial_intelligence::get_best_move(vector<vector<int>> board_matrix, int depth, int alpha, int beta, bool max) {
	if (depth == 0) {
		return board_score(board_matrix);
	}
	else {
		if (max) {
			int max_val = -999;
			vector<vector<int>> move_set = get_all_possible_moves(true, board_matrix);
			vector<int> best_move;
			for (auto move : move_set) {
				board_matrix = execute_move(move, board_matrix, board_matrix[move[0]][move[1]]);
				int value = get_best_move(board_matrix, depth-1, alpha, beta, !max);
				if (value > max_val) {
					max_val = value;
					best_move = move;
				}
				if (max_val > alpha) {
					alpha = max_val;
				}
				if (beta <= alpha){
					break;
				}
			}
			if (depth == STD_DEPTH) {
				final_move = best_move;
				cout << "\n top level value: " << max_val << endl;
			}
			return max_val;
		}
		else {
			int min_val = 999;
			vector<vector<int>> move_set = get_all_possible_moves(false, board_matrix);
			for (auto move : move_set) {
				board_matrix = execute_move(move, board_matrix, board_matrix[move[0]][move[1]]);
				int value = get_best_move(board_matrix, depth - 1, alpha, beta, !max);
				if (value < min_val) {
					min_val = value;
				}

				if (min_val < beta) {
					beta = min_val;
				}
				if (beta <= alpha) {
					break;
				}
			}
			return min_val;
		}
	}
}


vector<vector<int>> artificial_intelligence::execute_move(vector<int> move, vector<vector<int>> board_matrix, int piece_type) {
	for (int i = 0; i < move.size() - 2; i += 2) {
		board_matrix.at(move[i]).at(move[i + 1]) = 0;
	}
	board_matrix.at(move[move.size() - 2]).at(move[move.size() - 1]) = piece_type;
	for (int i = 0; i < 8; i++) {
		if (board_matrix.at(0).at(i) == 2) {
			board_matrix.at(0).at(i) = 12;
		}
		if (board_matrix.at(7).at(i) == 1) {
			board_matrix.at(7).at(i) = 11;
		}
	}
	return board_matrix;
}

void artificial_intelligence::do_move(board_model* model) {
	km.set_opposing_color(2);
	this->rpm = regular_piece_module();
	this->model = model;
	vector<vector<int>>* board_matrix = model->get_board_matrix();
	if (get_all_possible_moves(true, *board_matrix).empty() || (get_pieces(*board_matrix, false, true).empty() && get_pieces(*board_matrix, true, true).empty())) {
		cout << "PC LOSES. GAME over" << endl;
		cout << "Press key to exit" << endl;
		int x = _gettch();
		exit(EXIT_SUCCESS);
	}
	int y = get_best_move(*board_matrix, STD_DEPTH, -10000, 10000, true);
	view = board_view(model);
	vector<vector<int>> one_move_list;
	one_move_list.push_back(final_move);
	view.print_board_with_moves(one_move_list, final_move[1], final_move[0]);
	cout << y << endl; //TODO remove
	cout << "press any key to acknowledge move" << endl;
	int x = _gettch();
	*board_matrix = execute_move(final_move, *board_matrix, (*board_matrix)[final_move[0]][final_move[1]]); 
}



