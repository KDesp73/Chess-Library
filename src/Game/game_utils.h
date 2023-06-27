#pragma once

#include "../Pieces/Pieces.h"
#include "../Board/board.h"
#include "../Board/board_utils.h"


#include <string>

using namespace std;

namespace GameUtils {
	Move prompt(Pieces* p, Board *board, string type);
	Move turn(Pieces *p, Board *board);
	bool isMate(Board *board);
	bool isDraw(Board *board);
	void gameLoop(Board *board);
};