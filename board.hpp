#ifndef BOARD_H
#define BOARD_H

#include "pieces.hpp"
#include "square.hpp"
#include "move.hpp"

#include <vector>

class Board {
    std::vector<std::vector<Square>> board;
public:
    void resetBoard();
    void move(Move);
    Piece getPieceAt(int, int);
    std::vector<std::vector<Square>> getState();
};

#endif
