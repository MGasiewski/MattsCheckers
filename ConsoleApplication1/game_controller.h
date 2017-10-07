#pragma once
#include "board_model.h"
#include "board_view.h"
#include <vector>
#include "game_logic.h"
using namespace std;

class game_controller
{
public:
	game_controller(game_logic logic, board_model* model, board_view view);
	~game_controller();
	vector<vector<int>> get_valid_moves_black(int player_x, int player_y);
	vector<vector<int>> get_valid_moves_white(board_model* board, int player_x, int player_y);
	void handle_user_input(int input, int& user_x, int& user_y);
	void handle_key_up(int& user_x, int& user_y);
	void handle_key_down(int& user_x, int& user_y);
	void handle_key_left(int& user_x, int& user_y);
	void handle_key_right(int& user_x, int& user_y);
	void handle_space(int& user_x, int& user_y);
private:
	board_view view;
	board_model* model;
	game_logic logic;
};