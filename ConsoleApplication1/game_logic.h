#pragma once
#include <vector>
#include "board_model.h"
#include "board_view.h"
#include "artificial_intelligence.h"
#include "king_module.h"

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
	vector<vector<int>> get_jumps(int player_x, int player_y);
	bool is_game_over();
private:
	void execute_move(vector<int> move, int& user_x, int& user_y);
	void make_kings();
	artificial_intelligence intelligence;
	board_model* model;
	board_view view;
	king_module km;
	regular_piece_module rpm;
};