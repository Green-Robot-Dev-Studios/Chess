#include "pieces.hpp"
#include "move.hpp"
#include <cmath>
#include <vector>

bool Piece::isMoveValid(const Move &move) {
    if (move.oldCol != col || move.oldRow != row) {
        return false;
    }

    return isMoveValidInternal(move);
}

void Piece::move(const Move &move) {
    col = move.newCol;
    row = move.newRow;
    ++moveCount;
}

void Piece::capture() { captured = true; }

PieceColor Piece::getColor() { return color; }

int Piece::getCol() { return col; }

int Piece::getRow() { return row; }

int Piece::getMoveCount() { return moveCount; }

char Piece::getLetter() { return color == White ? letter : ::toupper(letter); }

// Bishop should move same magnitude in both axes
bool Bishop::isMoveValidInternal(const Move &move) {
    int dx = abs(move.newCol - move.oldCol);
    int dy = abs(move.newRow - move.oldRow);
    return dx == dy;
}

/*
    Knight should move:
    - up 2 and left 1
    - up 2 and right 1
    - right 2 and up 1
    - right 2 and down 1
    - down 2 and left 1
    - down 2 and right 1
    - left 2 and up 1
    - left 2 and down 1
*/
std::vector<int> Knight::dy = {-2, -2, -1, 1, 2, 2, -1, 1};
std::vector<int> Knight::dx = {-1, 1, 2, 2, -1, 1, -2, -2};

bool Knight::isMoveValidInternal(const Move &move) {
    for (int i = 0; i < 8; ++i) {
        int nx = move.oldCol + dx[i];
        int ny = move.oldRow + dy[i];

        if (nx == move.newCol && ny == move.newRow) {
            return true;
        }
    }

    return false;
}

/*
    Pawn should move one unit vertically or diagonally in the direction relative to its color 
    (unless it is the first move, in which case it can move two units vertically)
*/
bool Pawn::isMoveValidInternal(const Move &move) {
    PieceColor color = getColor();

    int dx = abs(move.newCol - move.oldCol);
    int dy = abs(move.newRow - move.oldRow);

    if (color == PieceColor::Black) {
        // check that it has moved forward
        if(move.newCol <= move.oldCol) {
            return false;
        }

        // check for two unit advance
        if(getMoveCount() == 0 && move.newCol == move.oldCol + 2 && move.newRow == move.oldRow) {
            return true;
        }
    } else {
        // check that it has moved forward
        if(move.newCol >= move.oldCol) {
            return false;
        }

        // check for two unit advance
        if(getMoveCount() == 0 && move.newCol == move.oldCol - 2 && move.newRow == move.oldRow) {
            return true;
        }
    }

    // check that pawn has only moved one unit
    return dx <= 1 && dy <= 1;
}

// King should move one unit in any direction
bool King::isMoveValidInternal(const Move &move) {
    int dx = abs(move.newCol - move.oldCol);
    int dy = abs(move.newRow - move.oldRow);

    return dx <= 1 && dy <= 1;
}

// Queen should EITHER move same magnitude in both axes, or only moved in one axis
bool Queen::isMoveValidInternal(const Move &move) {
    int dx = abs(move.newCol - move.oldCol);
    int dy = abs(move.newRow - move.oldRow);

    return ((dx == 0 || dy == 0) || (dx == dy));
}

// Rook should move only in one axis
bool Rook::isMoveValidInternal(const Move &move) {
    int dx = abs(move.newCol - move.oldCol);
    int dy = abs(move.newRow - move.oldRow);
    
    return dx == 0 || dy == 0;
}