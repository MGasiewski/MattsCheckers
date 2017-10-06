#include "stdafx.h"
#include "board_view.h"
#include <vector>
#include <iostream>

using namespace std;

board_view::board_view() {
	selected = false;
}

board_view::~board_view() {

}

void board_view::flip_selected() {
	this->selected = !this->selected;
}

void board_view::print_board_with_moves() {

}

void board_view::print_board(int user_x, int user_y) {
	system("cls");
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (j % 2 == i % 2) {
				if (i == user_y && j == user_x) {
					cout << ">";
				}
				else {
					cout << (char)254u;
				}
				switch (model.get_board_matrix().at(i).at(j)) {
				case 0:
					cout << (char)254u;
					break;
				case 1:
					cout << "B";
					break;
				case 2:
					cout << "W";
					break;
				default:
					break;
				}
				if (i == user_y && j == user_x && selected) {
					cout << "<";
				}
				else {
					cout << (char)254u;
				}
			}
			else {
				if (i == user_y && j == user_x) {
					cout << ">";
				}
				else {
					cout << " ";
				}
				switch (model.get_board_matrix().at(i).at(j)) {
				case 0:
					cout << " ";
					break;
				case 1:
					cout << "B";
					break;
				case 2:
					cout << "W";
					break;
				default:
					break;
				}
				if (i == user_y && j == user_x && selected) {
					cout << "<";
				}
				else {
					cout << " ";
				}
			}
		}
		cout << endl;
	}
}

void board_view::set_board_model(board_model model) {
	this->model = model;
}