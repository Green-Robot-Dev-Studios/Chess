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
    Board();
    Board(const Board &other);
    void resetBoard();
    void clearObservers();
    void placeDefault();
    void move(const Move &move);
    void enPassantMove(const Move &move);
    void promotionMove(const Move &move, std::shared_ptr<Piece> promotedPiece);
    std::shared_ptr<Piece> getPieceAt(int, int) const;
    std::vector<std::vector<Square>>& getState();
};

#endif
