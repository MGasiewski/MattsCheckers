#pragma once
#include <vector>
#include "board_model.h"
#include "board_view.h"
#include "artificial_intelligence.h"

using namespace std;

class game_logic
{
public:
	game_logic(board_model* model, board_view view);
	game_logic();
	bool can_jump(int player_x, int player_y);
	~game_logic();
	void handle_movement(vector<vector<int>> moves, int& user_x, int& user_y);
	vector<vector<int>> get_valid_moves(int player_x, int player_y, bool player_white);
private:
	void execute_move(vector<int> move, int& user_x, int& user_y);
	artificial_intelligence intelligence;
	board_model* model;
	board_view view;
};