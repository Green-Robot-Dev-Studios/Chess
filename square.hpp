#ifndef SQUARE_H
#define SQUARE_H

#include "pieces.hpp"

#include <memory>

class Square {
    int row;
    int col;
    std::shared_ptr<Piece> piece;
public:
    Square(int r, int c);
    bool isOccupied() const;
    std::shared_ptr<Piece> getPiece() const;
    void setPiece(const std::shared_ptr<Piece>& p);
    void removePiece();
};

#endif
