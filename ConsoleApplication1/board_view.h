#pragma once
#include "stdafx.h"
#include "board_model.h"

class board_view
{
public:
	board_view();
	~board_view();
	void print_board(int user_x, int user_y);
	void set_board_model(board_model model);
	void flip_selected();
	void print_board_with_moves();
private:
	board_model model;
	bool selected;
};