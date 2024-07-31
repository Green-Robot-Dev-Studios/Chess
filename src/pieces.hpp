#ifndef PIECES_H
#define PIECES_H

#include "move.hpp"
#include <memory>
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
    virtual ~Piece() {}
    bool isMoveValid(const Move &move);
    void move(const Move &move);
    void capture();

    PieceColor getColor();
    int getRow();
    int getCol();
    int getMoveCount();
    char getLetter();

    virtual std::shared_ptr<Piece> clone() const = 0;
};

class Bishop : public Piece {
public:
    Bishop(PieceColor color, int r, int c) : Piece(color, r, c) {
        letter = 'b';
    }
    std::shared_ptr<Piece> clone() const override {
        return std::make_shared<Bishop>(*this);
    }

    bool isMoveValidInternal(const Move &move) override;
};

class Knight : public Piece {
public:
    Knight(PieceColor color, int r, int c) : Piece(color, r, c) {
        letter = 'n';
    }
    std::shared_ptr<Piece> clone() const override {
        return std::make_shared<Knight>(*this);
    }

    static std::vector<int> dy;
    static std::vector<int> dx;
    bool isMoveValidInternal(const Move &move) override;
};

class Pawn : public Piece {
public:
    Pawn(PieceColor color, int r, int c) : Piece(color, r, c) { letter = 'p'; }
    std::shared_ptr<Piece> clone() const override {
        return std::make_shared<Pawn>(*this);
    }

    bool isMoveValidInternal(const Move &move) override;
};

class King : public Piece {
public:
    King(PieceColor color, int r, int c) : Piece(color, r, c) { letter = 'k'; }
    std::shared_ptr<Piece> clone() const override {
        return std::make_shared<King>(*this);
    }

    bool isMoveValidInternal(const Move &move) override;
};

class Queen : public Piece {
public:
    Queen(PieceColor color, int r, int c) : Piece(color, r, c) { letter = 'q'; }
    std::shared_ptr<Piece> clone() const override {
        return std::make_shared<Queen>(*this);
    }

    bool isMoveValidInternal(const Move &move) override;
};

class Rook : public Piece {
public:
    Rook(PieceColor color, int r, int c) : Piece(color, r, c) { letter = 'r'; }
    std::shared_ptr<Piece> clone() const override {
        return std::make_shared<Rook>(*this);
    }

    bool isMoveValidInternal(const Move &move) override;
};

#endif
