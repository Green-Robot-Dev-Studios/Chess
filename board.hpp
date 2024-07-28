#ifndef BOARD_H
#define BOARD_H

#include "pieces.hpp"
#include "square.hpp"
#include "move.hpp"
#include "subject.hpp"

#include <vector>

class Board: public Subject {
    std::vector<std::vector<Square>> board;
public:
    void resetBoard();
    void move(const Move &move);
    std::shared_ptr<Piece> getPieceAt(int, int) const;
    std::vector<std::vector<Square>> getState() const;
};

#endif
