#ifndef MOVE_H
#define MOVE_H

enum PieceColor {
    Black,
    White
};

struct Move {
    int oldRow;
    int oldCol;
    int newRow;
    int newCol;
    PieceColor color;
};



#endif
