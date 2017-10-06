#pragma once
#include "board_model.h"
#include "board_view.h"
#include <vector>

using namespace std;

class game_controller
{
public:
	game_controller();
	~game_controller();
	vector<vector<int>> get_valid_moves_black(board_model board, int player_x, int player_y);
	vector<vector<int>> get_valid_moves_white(board_model board, int player_x, int player_y);
	void handle_user_input(int input, int& user_x, int& user_y);
	void set_board_view(board_view view);
	void set_board_model(board_model board);
	void handle_key_up(int& user_x, int& user_y);
	void handle_key_down(int& user_x, int& user_y);
	void handle_key_left(int& user_x, int& user_y);
	void handle_key_right(int& user_x, int& user_y);
	void handle_space(int& user_x, int& user_y);
private:
	board_view view;
	board_model board;
};