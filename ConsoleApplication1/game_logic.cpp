#pragma once
#include "stdafx.h"
#include <vector>
#include "game_logic.h"
#include <conio.h>
#include <iostream>
#include "artificial_intelligence.h"
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define SPACE 32
#define ESC 27

using namespace std;

game_logic::game_logic(board_model* model, board_view view){
	this->model = model;
	this->view = view;
	artificial_intelligence ai;
	this->intelligence = ai;
}

game_logic::game_logic() {
}

void game_logic::make_kings() {
	vector<vector<int>>* board_matrix = model->get_board_matrix();
	for (int i = 0; i < 8; i++) {
		if ((*board_matrix).at(0).at(i) == 2) {
			(*board_matrix).at(0).at(i) = 12;
		}
		if ((*board_matrix).at(7).at(i) == 1) {
			(*board_matrix).at(7).at(i) = 11;
		}
	}
}

void game_logic::execute_move(vector<int> move, int& user_x, int& user_y) {
	vector<vector<int>>* board_matrix = (*model).get_board_matrix();
	int piece_value = (*board_matrix)[user_y][user_x];
	for (int i = 0; i < move.size() - 2; i += 2) {
		(*board_matrix)[move[i]][move[i+1]] = 0;
	}
	user_y = move[move.size() - 2];
	user_x = move[move.size() - 1];
	(*board_matrix)[user_y][user_x] = piece_value;
	
}

game_logic::~game_logic() {
}

void game_logic::handle_movement(vector<vector<int>> moves, int& user_x, int& user_y) {
	bool selected = true;
	vector<vector<int>>::iterator it = moves.begin();
	vector<int> move = *it;
	int move_y = move[move.size() - 2];
	int move_x = move[move.size() - 1];
	view.print_board_with_moves(moves, move_x, move_y);
	cout << "Press LEFT and RIGHT to cycle through moves. Press space to execute move, or escape to select another piece";
	int c = _getch();
	while (selected) {
		switch (c)
		{
		case KEY_RIGHT:
			if (it == moves.end()-1) {
				it = moves.begin();
				vector<int> move = *it;
				int move_y = move[move.size() - 2];
				int move_x = move[move.size() - 1];
				view.print_board_with_moves(moves, move_x, move_y);
			}
			else {
				it++;
				vector<int> move = *it;
				int move_y = move[move.size() - 2];
				int move_x = move[move.size() - 1];
				view.print_board_with_moves(moves, move_x, move_y);
			}
			break;
		case KEY_LEFT:
			if (it == moves.begin()) {
				it = moves.end()-1;
				vector<int> move = *it;
				int move_y = move[move.size() - 2];
				int move_x = move[move.size() - 1];
				view.print_board_with_moves(moves, move_x, move_y);
			}
			else {
				it--;
				vector<int> move = *it;
				int move_y = move[move.size() - 2];
				int move_x = move[move.size() - 1];
				view.print_board_with_moves(moves, move_x, move_y);
			}
			break;
		case ESC:
			selected = false;
			view.clear_move_data(moves);
			view.print_board(user_x, user_y);
			break;
		case SPACE:
			execute_move(*it, user_x, user_y);
			view.clear_move_data(moves);
			make_kings();
			this->intelligence.do_move(model);
			make_kings();
			view.print_board(user_x, user_y);
			selected = false;
			break;
		default:
			break;
		}
		if(c!=SPACE && c!=ESC)
			c = _getch();
	}
}