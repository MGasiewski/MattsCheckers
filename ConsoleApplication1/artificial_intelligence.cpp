#include "stdafx.h"
#include "artificial_intelligence.h"
#include "king_module.h"
#include <iostream>
#include <vector>
#include <random>

using namespace std;

artificial_intelligence::artificial_intelligence()
{
}

artificial_intelligence::~artificial_intelligence()
{
}


void artificial_intelligence::do_move(board_model* model) {
	this->rpm = regular_piece_module(model);
	mt19937 rng;
	rng.seed(random_device()());
	this->model = model;
	vector<vector<int>> white_pieces;
	vector<vector<int>>* board_matrix = model->get_board_matrix();
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if ((*board_matrix)[i][j] % 10 == 1) {
				vector<int> position;
				position.push_back(i);
				position.push_back(j);
				white_pieces.push_back(position);
			}
		}
	}

	vector<vector<int>> moves;
	for (auto white_piece : white_pieces) {
		vector<vector<int>> piece_moves = rpm.get_moves(white_piece);
		moves.insert(moves.end(), piece_moves.begin(), piece_moves.end());
	}
	vector<vector<int>> final_jumps;
	for (auto white_piece : white_pieces) {
		vector<vector<int>> jumps = rpm.get_jumps(white_piece);
		final_jumps.insert(final_jumps.end(), jumps.begin(), jumps.end());
	}
	moves.insert(moves.end(), final_jumps.begin(), final_jumps.end());
	uniform_int_distribution<mt19937::result_type> dist(0, moves.size() - 1);
	int choice = dist(rng);
	vector<int> move = moves[choice];
	for (int i = 0; i < move.size() - 2; i += 2) {
		board_matrix->at(move[i]).at(move[i + 1]) = 0;
	}
	board_matrix->at(move[move.size() - 2]).at(move[move.size() - 1]) = 1;
}



