#include "stdafx.h"
#include "game_controller.h"
#include "board_view.h"
#include "game_logic.h"
#include "king_module.h"
#include "regular_piece_module.h"
#include <iostream>
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define SPACE 32

using namespace std;

game_controller::game_controller(game_logic logic, board_model* model, board_view view) {
	this->logic = logic;
	this->model = model;
	this->view = view;
}

game_controller::~game_controller() {
}

void game_controller::handle_key_down(int& user_x, int& user_y) {
	if (user_y == 7) {
		return;
	}
	else if (user_y % 2 == 0){
		user_y += 1;
		user_x -= 1;
		view.print_board(user_x, user_y);
	}
	else if (user_y % 2 == 1) {
		user_y += 1;
		user_x += 1;
		view.print_board(user_x, user_y);
	}
}

void game_controller::handle_key_up(int& user_x, int& user_y) {
	if (user_y == 0) {
		return;
	}
	else if (user_y % 2 == 1){
		user_y -= 1;
		user_x += 1;
		view.print_board(user_x, user_y);
	}
	else if (user_y % 2 == 0) {
		user_y -= 1;
		user_x -= 1;
		view.print_board(user_x, user_y);
	}
}

void game_controller::handle_key_left(int& user_x, int& user_y) {
	if (user_x == 0){
		return;
	}
	else if (user_x == 1 && user_y % 2 == 0){
		return;
	}
	else
	{
		user_x -= 2;
		view.print_board(user_x, user_y);
	}
}

void game_controller::handle_key_right(int& user_x, int& user_y) {
	if (user_x == 7 || user_x == 6)
	{
		return;
	}
	else
	{
		user_x += 2;
		view.print_board(user_x, user_y);
	}
}

void game_controller::handle_space(int& user_x, int& user_y) {
	vector<vector<int>>* board_matrix = model->get_board_matrix();
	rpm = regular_piece_module();
	rpm.set_opposing_color(1);
	vector<int> position;
	position.push_back(user_y);
	position.push_back(user_x);
	if ((*board_matrix).at(user_y).at(user_x) == 2) {
		vector<vector<int>> valid_moves = rpm.get_moves(position, *board_matrix);
		vector<vector<int>> jumps = rpm.get_jumps(position, *board_matrix);
		for (auto jump : jumps) {
			valid_moves.push_back(jump);
		}
		if (valid_moves.empty()) {
			cout << "No moves available for this piece";
			return;
		}
		logic.handle_movement(valid_moves, user_x, user_y);
	}
	else if ((*board_matrix).at(user_y).at(user_x) == 12) {
		vector<vector<int>> moves = km.get_moves(board_matrix, user_y, user_x);
		if (moves.empty()) {
			cout << "No moves available for this piece";
			return;
		}
		logic.handle_movement(moves, user_x, user_y);
	}
}

void game_controller::handle_user_input(int input, int& user_x, int& user_y) {
	switch (input)
	{
	case KEY_UP:
		handle_key_up(user_x, user_y);
		break;
	case KEY_DOWN:
		handle_key_down(user_x, user_y);
		break;
	case KEY_LEFT:
		handle_key_left(user_x, user_y);
		break;
	case KEY_RIGHT:
		handle_key_right(user_x, user_y);
		break;
	case SPACE:
		handle_space(user_x, user_y);
		break;
	default:
		break;
	}
}