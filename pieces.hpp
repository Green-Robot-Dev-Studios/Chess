#ifndef PIECES_H
#define PIECES_H

#include "move.hpp"
#include <vector>

class Piece {
    PieceColor color;
    int row;
    int col;
    int moveCount = 0;
    bool captured = false;

protected:
    char letter;
    virtual bool isMoveValidInternal(const Move &move) = 0;

public:
    Piece(PieceColor c, int r, int col);
    bool isMoveValid(const Move &move);
    void move(const Move &move);
    void capture();

    PieceColor getColor();
    int getRow();
    int getCol();
    int getMoveCount();
    char getLetter();
};

class Bishop : public Piece {
    Bishop() { letter = 'b'; };
    bool isMoveValidInternal(const Move &move) override;
};

class Knight : public Piece {
    Knight() { letter = 'n'; };
    static std::vector<int> dy;
    static std::vector<int> dx;
    bool isMoveValidInternal(const Move &move) override;
};

class Pawn : public Piece {
    Pawn() { letter = 'p'; };
    bool isMoveValidInternal(const Move &move) override;
};

class King : public Piece {
    King() { letter = 'k'; };
    bool isMoveValidInternal(const Move &move) override;
};

class Queen : public Piece {
    Queen() { letter = 'q'; };
    bool isMoveValidInternal(const Move &move) override;
};

class Rook : public Piece {
    Rook() { letter = 'r'; };
    bool isMoveValidInternal(const Move &move) override;
};

#endif