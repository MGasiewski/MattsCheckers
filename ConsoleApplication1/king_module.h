#pragma once
#include <vector>

using namespace std;

class king_module
{
public:
	king_module();
	~king_module();
	vector<vector<int>> get_moves(vector<vector<int>>* board_matrix, int king_y, int king_x);
private:
	vector<vector<int>> get_jumps(vector<vector<int>>* board_matrix, int king_y, int king_x, int direction);
	vector<vector<int>> combine(vector<int> jump, vector<vector<int>> additional_jumps);
};