#pragma once
#include "board_model.h"

using namespace std;

class artificial_intelligence
{
public:
	artificial_intelligence();
	~artificial_intelligence();
	void do_move(board_model* model);
private:
	vector<vector<int>> get_moves(vector<vector<int>> positions);
	board_model* model;
};