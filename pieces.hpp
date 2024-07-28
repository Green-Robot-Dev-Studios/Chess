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
    Piece(PieceColor color, int r, int c) : color(color), row(r), col(c) {}
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
    public:
    Bishop(PieceColor color, int r, int c) : Piece(color, r, c) { letter = 'b'; }
    bool isMoveValidInternal(const Move &move) override;
};

class Knight : public Piece {
    public:
    Knight(PieceColor color, int r, int c) : Piece(color, r, c) { letter = 'n'; }
    static std::vector<int> dy;
    static std::vector<int> dx;
    bool isMoveValidInternal(const Move &move) override;
};

class Pawn : public Piece {
    public:
    Pawn(PieceColor color, int r, int c) : Piece(color, r, c) { letter = 'p'; }
    bool isMoveValidInternal(const Move &move) override;
};

class King : public Piece {
    public:
    King(PieceColor color, int r, int c) : Piece(color, r, c) { letter = 'k'; }
    bool isMoveValidInternal(const Move &move) override;
};

class Queen : public Piece {
    public:
    Queen(PieceColor color, int r, int c) : Piece(color, r, c) { letter = 'q'; }
    bool isMoveValidInternal(const Move &move) override;
};

class Rook : public Piece {
    public:
    Rook(PieceColor color, int r, int c) : Piece(color, r, c) { letter = 'r'; }
    bool isMoveValidInternal(const Move &move) override;
};

#endif
