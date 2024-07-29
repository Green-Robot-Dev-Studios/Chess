#include "board.hpp"
#include <iostream>

void Board::resetBoard() {
    // Define board dimensions
    const int boardSize = 8;

    board.clear();

    // Initialize squares
    for (int r = 0; r < boardSize; ++r) {
        board.push_back({});
        for (int c = 0; c < boardSize; ++c) {
            board[r].push_back(
                Square(r, c)); // Create Square at position (r, c)
        }
    }

    // Place Pawns
    for (int c = 0; c < boardSize; ++c) {
        board[1][c].setPiece(
            std::make_shared<Pawn>(Black, 1, c)); // Black pawns on the 2nd row
        board[6][c].setPiece(
            std::make_shared<Pawn>(White, 6, c)); // White pawns on the 7th row
    }

    // Place Rooks
    board[0][0].setPiece(std::make_shared<Rook>(Black, 0, 0)); // Black Rooks
    board[0][7].setPiece(std::make_shared<Rook>(Black, 0, 7));
    board[7][0].setPiece(std::make_shared<Rook>(White, 7, 0)); // White Rooks
    board[7][7].setPiece(std::make_shared<Rook>(White, 7, 7));

    // Place Knights
    board[0][1].setPiece(
        std::make_shared<Knight>(Black, 0, 1)); // Black Knights
    board[0][6].setPiece(std::make_shared<Knight>(Black, 0, 6));
    board[7][1].setPiece(
        std::make_shared<Knight>(White, 7, 1)); // White Knights
    board[7][6].setPiece(std::make_shared<Knight>(White, 7, 6));

    // Place Bishops
    board[0][2].setPiece(
        std::make_shared<Bishop>(Black, 0, 2)); // Black Bishops
    board[0][5].setPiece(std::make_shared<Bishop>(Black, 0, 5));
    board[7][2].setPiece(
        std::make_shared<Bishop>(White, 7, 2)); // White Bishops
    board[7][5].setPiece(std::make_shared<Bishop>(White, 7, 5));

    // Place Queens
    board[0][3].setPiece(std::make_shared<Queen>(Black, 0, 3)); // Black Queen
    board[7][3].setPiece(std::make_shared<Queen>(White, 7, 3)); // White Queen

    // Place Kings
    board[0][4].setPiece(std::make_shared<King>(Black, 0, 4)); // Black King
    board[7][4].setPiece(std::make_shared<King>(White, 7, 4)); // White King
}

void Board::move(const Move &move) {
    // Get the piece at the source square
    std::shared_ptr<Piece> piece = board[move.oldRow][move.oldCol].getPiece();

    // Update piece fields
    piece->move(move);

    // Move the piece to the destination square
    board[move.newRow][move.newCol].setPiece(piece);

    // Clear the source square
    board[move.oldRow][move.oldCol].removePiece();

    notifyObservers();
}

std::shared_ptr<Piece> Board::getPieceAt(int row, int col) const {
    return board[row][col].getPiece();
}

std::vector<std::vector<Square>> Board::getState() const { return board; }
