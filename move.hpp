#ifndef MOVE_H
#define MOVE_H

enum PieceColor {
    Black = 0,
    White = 1
};

struct Move {
    int oldRow;
    int oldCol;
    int newRow;
    int newCol;
    PieceColor color;
};

#endif
