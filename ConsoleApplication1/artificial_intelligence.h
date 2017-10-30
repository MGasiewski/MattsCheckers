#pragma once
#include "board_model.h"
#include "king_module.h"
#include "regular_piece_module.h"

using namespace std;

class artificial_intelligence 
{
public:
	artificial_intelligence();
	~artificial_intelligence();
	void do_move(board_model* model);
private:
	board_model* model;
	king_module km;
	regular_piece_module rpm = nullptr;
};