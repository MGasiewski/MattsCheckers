#pragma once
#include <vector>

using namespace std;

class board_model
{
public:
	board_model();
	~board_model();
	void update_board_state(int player, int key);
	vector<vector<int>>* get_board_matrix();
private:
	vector<vector<int>>* board_matrix;
};



