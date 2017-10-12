#include "stdafx.h"
#include "board_view.h"
#include <vector>
#include <iostream>

using namespace std;

board_view::board_view(board_model* model) {
	this->model = model;
	this->selected = false;
}

board_view::board_view(){}

board_view::~board_view() {

}

void board_view::flip_selected() {
	this->selected = !this->selected;
}

void board_view::print_board_with_moves(vector<vector<int>> moves, int user_x, int user_y) {
	vector<vector<int>>* board_matrix = model->get_board_matrix();
	for (auto move : moves) {
		if (move.size() < 5) {
			(*board_matrix)[move[1]][move[0]] = 99;
		}
		else {
			for (int i = 0; i < move.size(); i += 4) {
				(*board_matrix)[move[i + 1]][move[i]] = 99;
			}
		}
	}
	print_board(user_x, user_y);
}

void board_view::clear_move_data(vector<vector<int>> moves) {
	vector<vector<int>>* board_matrix = model->get_board_matrix();
	for (auto move : moves) {
		for (int i = 0; i < move.size(); i += 2) {
			if ((*board_matrix)[move[i + 1]][move[i]] == 99) {
				(*board_matrix)[move[i + 1]][move[i]] = 0;
			}
		}
	}
}

void board_view::print_board(int user_x, int user_y) {
	system("cls");
	vector<vector<int>>* board_matrix = model->get_board_matrix();
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (j % 2 == i % 2) {
				cout << (char)254u << (char)254u << (char)254u;
			}
			else {
				if (i == user_y && j == user_x) {
					cout << ">";
				}
				else {
					cout << " ";
				}
				switch ((*board_matrix).at(i).at(j)) {
				case 0:
					cout << " ";
					break;
				case 1:
					cout << "W";
					break;
				case 11:
					cout << "W!";
					break;
				case 2:
					cout << "B";
					break;
				case 12:
					cout << "B!";
					break;
				case 99:
					cout << "X";
					break;
				default:
					break;
				}
				if ((*board_matrix).at(i).at(j) != 11 && (*board_matrix).at(i).at(j) != 12) {
					cout << " ";
				}
			}
		}
		cout << endl;
	}
}

void board_view::set_board_model(board_model* model) {
	this->model = model;
}