#pragma once
#include "board_model.h"
#include "king_module.h"
#include "regular_piece_module.h"
#include "board_view.h"

using namespace std;

class artificial_intelligence 
{
public:
	artificial_intelligence();
	~artificial_intelligence();
	vector<vector<int>> get_pieces(vector<vector<int>> board_matrix, bool king, bool white);
	vector<vector<int>> get_all_possible_moves(bool white, vector<vector<int>> board_matrix);
	vector<int> get_random_move(vector<vector<int>> moves);
	int board_score(vector<vector<int>> board_matrix);
	int get_best_move(vector<vector<int>> board_matrix, int depth, int alpha, int beta, bool max);
	vector<vector<int>> execute_move(vector<int> move, vector<vector<int>> board_matrix, int color);
	void do_move(board_model* model);
private:
	board_view view;
	board_model* model;
	vector<int> final_move;
	king_module km;
	regular_piece_module rpm;
};