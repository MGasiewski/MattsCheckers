#include "stdafx.h"
#include "board_model.h"
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define WHITE 1
#define BLACK 2

board_model::board_model()
{
	for (int i = 0; i < 8; i++) {
		vector<int> vec;
		board_matrix.push_back(vec);
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (i == 0 || i==2) {
				if (j % 2 == 1) {
					board_matrix.at(i).push_back(WHITE);
				}
				else {
					board_matrix.at(i).push_back(0);
				}
			}
			else if (i == 1) {
				if (j % 2 == 1) {
					board_matrix.at(i).push_back(0);
				}
				else {
					board_matrix.at(i).push_back(WHITE);
				}
			}
			else if (i == 5 || i==7) {
				if (j % 2 == 0) {
					board_matrix.at(i).push_back(BLACK);
				}
				else {
					board_matrix.at(i).push_back(0);
				}
			}
			else if (i == 6) {
				if (j % 2 == 0) {
					board_matrix.at(i).push_back(0);
				}
				else {
					board_matrix.at(i).push_back(BLACK);
				}
			}
			else {
				board_matrix.at(i).push_back(0);
			}
		}
	}
}

vector<vector<int>> board_model::get_board_matrix()
{
	return this->board_matrix;
}

void board_model::update_board_state(int player, int key)
{

}

board_model::~board_model()
{
}