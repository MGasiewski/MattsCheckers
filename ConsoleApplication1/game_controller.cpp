#include "stdafx.h"
#include "game_controller.h"
#include "board_view.h"
#include <iostream>
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define SPACE 32

using namespace std;

game_controller::game_controller() {
}

game_controller::~game_controller() {
}

void game_controller::set_board_view(board_view view) {
	this->view = view;
}

void game_controller::set_board_model(board_model board) {
	this->board = board;
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
	if (board.get_board_matrix().at(user_y).at(user_x) == 2) {
		vector<vector<int>> valid_moves = get_valid_moves_black();
		view.flip_selected();
		view.print_board(user_x, user_y);
	}
}

vector<vector<int>> game_controller::get_valid_moves_black(board_model board, int player_x, int player_y) {
	vector<vector<int>> game_matrix = board.get_board_matrix();
	vector<vector<int>> valid_moves;
	if (player_y == 0) {
		return valid_moves;
	}
	else if (player_x == 0) {
		if (game_matrix.at(player_y - 1).at(player_x + 1) == 0) {
			vector<int> single_move;
			single_move.push_back(player_x + 1);
			single_move.push_back(player_y - 1);
			valid_moves.push_back(single_move);
			return valid_moves;
		}
		else {
			return valid_moves;
		}
	}
	else if (player_x == 7) {
		if (game_matrix.at(player_y - 1).at(player_x - 1) == 0) {
			vector<int> single_move;
			single_move.push_back(player_x - 1);
			single_move.push_back(player_y - 1);
			valid_moves.push_back(single_move);
			return valid_moves;
		}
		else {
			return valid_moves;
		}
	}
	else {
		if (game_matrix.at(player_y - 1).at(player_x - 1) == 0){
			vector<int> single_move;
			single_move.push_back(player_x - 1);
			single_move.push_back(player_y - 1);
			valid_moves.push_back(single_move);
		}
		if (game_matrix.at(player_y - 1).at(player_x + 1) == 0) {
			vector<int> single_move;
			single_move.push_back(player_x + 1);
			single_move.push_back(player_y - 1);
			valid_moves.push_back(single_move);
		}
		return valid_moves;
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
		cout << input << " is the number for the key you pressed" << endl;
		break;
	}
}