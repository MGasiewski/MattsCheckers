#include "stdafx.h"
#include "artificial_intelligence.h"
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

vector<vector<int>> artificial_intelligence::get_moves(vector<vector<int>> positions)
{
	vector<vector<int>> moves;
	vector<vector<int>> board_matrix = *(this->model->get_board_matrix());
	for (auto position : positions) {
		if (position[0] == 7) {
			if (position[0] + 1 <8 && position[1]-1 >= 0 && board_matrix[position[0] + 1][position[1] - 1] == 0) {
				vector<int> move;
				move.push_back(position[0]);
				move.push_back(position[1]);
				move.push_back(position[0] + 1);
				move.push_back(position[1] - 1);
				moves.push_back(move);
			}
		}
		else if (position[0] == 0) {
			if (position[0] + 1 <8 && position[1] + 1 < 8 && board_matrix[position[0] + 1][position[1] + 1] == 0) {
				vector<int> move;
				move.push_back(position[0]);
				move.push_back(position[1]);
				move.push_back(position[0] + 1);
				move.push_back(position[1] - 1);
				moves.push_back(move);
			}
		}
		else {
			if (position[0] + 1 <8 && position[1] + 1 < 8 &&  board_matrix[position[0] + 1][position[1] + 1] == 0) {
				vector<int> move;
				move.push_back(position[0]);
				move.push_back(position[1]);
				move.push_back(position[0] + 1);
				move.push_back(position[1] + 1);
				moves.push_back(move);
			}
			if (position[0] + 1 <8 && position[1] - 1 >= 0 && board_matrix[position[0] + 1][position[1] - 1] == 0) {
				vector<int> move;
				move.push_back(position[0]);
				move.push_back(position[1]);
				move.push_back(position[0] + 1);
				move.push_back(position[1] - 1);
				moves.push_back(move);
			}
		}
	}
	return moves;
}

void artificial_intelligence::do_move(board_model* model) {
	mt19937 rng;
	rng.seed(random_device()());
	this->model = model;
	vector<vector<int>> black_pieces;
	vector<vector<int>>* board_matrix = model->get_board_matrix();
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if ((*board_matrix)[i][j] == 1) {
				vector<int> position;
				position.push_back(i);
				position.push_back(j);
				black_pieces.push_back(position);
			}
		}
	}
	vector<vector<int>> moves = get_moves(black_pieces);
	uniform_int_distribution<mt19937::result_type> dist(0, moves.size()-1);
	int choice = dist(rng);
	vector<int> move = moves[choice];
	(*board_matrix)[move[0]][move[1]] = 0;
	(*board_matrix)[move[2]][move[3]] = 1;
}


