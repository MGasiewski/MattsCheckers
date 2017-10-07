#pragma once
#include <vector>
#include "board_model.h"
#include "board_view.h"

using namespace std;

class game_logic
{
public:
	game_logic(board_model* model, board_view view);
	game_logic();	
	~game_logic();
	void handle_movement(vector<vector<int>> moves, int& user_x, int& user_y);
private:
	void execute_move(vector<int> move, int& user_x, int& user_y);
	board_model* model;
	board_view view;
};