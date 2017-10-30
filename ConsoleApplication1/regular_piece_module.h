#pragma once
#include <vector>
#include "board_model.h"

class regular_piece_module
{
public:
	regular_piece_module(board_model* model);
	~regular_piece_module();
	bool under_limit_for_move(vector<int> position);
	vector<vector<int>> get_moves(vector<int> position);
	vector<vector<int>> get_jumps(vector<int> position);
	void set_opposing_color(int color);
private:
	vector<vector<int>> combine(vector<int> jump, vector<vector<int>> additional_jumps);
	board_model* model = nullptr;
	bool under_limit_for_jump(vector<int> position);
	int opposing_color = 2;
	int direction = 1;
};