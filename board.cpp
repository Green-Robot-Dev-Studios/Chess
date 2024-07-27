#include "board.hpp"
#include <iostream>

void Board::resetBoard() {
    // Initialize the board with empty squares
    board.resize(8, std::vector<Square>(8));
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            board[row][col] = Square(row, col);
        }
    }

    // Place pieces on the board
    // Black pieces
    board[0][0].setPiece(Rook(Black, 0, 0));
    board[0][1].setPiece(Knight(Black, 0, 1));
    board[0][2].setPiece(Bishop(Black, 0, 2));
    board[0][3].setPiece(Queen(Black, 0, 3));
    board[0][4].setPiece(King(Black, 0, 4));
    board[0][5].setPiece(Bishop(Black, 0, 5));
    board[0][6].setPiece(Knight(Black, 0, 6));
    board[0][7].setPiece(Rook(Black, 0, 7));
    for (int col = 0; col < 8; ++col) {
        board[1][col].setPiece(Pawn(Black, 1, col));
    }

    // White pieces
    board[7][0].setPiece(Rook(White, 7, 0));
    board[7][1].setPiece(Knight(White, 7, 1));
    board[7][2].setPiece(Bishop(White, 7, 2));
    board[7][3].setPiece(Queen(White, 7, 3));
    board[7][4].setPiece(King(White, 7, 4));
    board[7][5].setPiece(Bishop(White, 7, 5));
    board[7][6].setPiece(Knight(White, 7, 6));
    board[7][7].setPiece(Rook(White, 7, 7));
    for (int col = 0; col < 8; ++col) {
        board[6][col].setPiece(Pawn(White, 6, col));
    }
}