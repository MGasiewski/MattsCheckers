#pragma once
#include "stdafx.h"
#include "board_model.h"
#include <vector>

class board_view
{
public:
	board_view(board_model* model);
	board_view();
	~board_view();
	void print_board(int user_x, int user_y);
	void set_board_model(board_model* model);
	void print_board_with_moves(vector<vector<int>> moves, int user_x, int user_y);
	void clear_move_data(vector<vector<int>> moves);
	void flip_selected();
private:
	board_model* model;
	bool selected;
};