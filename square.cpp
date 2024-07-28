#include "square.hpp"

Square::Square(int r, int c) : row(r), col(c), piece(nullptr) {}

bool Square::isOccupied() const { return piece != nullptr; }

void Square::setPiece(const std::shared_ptr<Piece> &p) { piece = p; }

std::shared_ptr<Piece> Square::getPiece() const { return piece; }

void Square::removePiece() {
    // TODO: does setting a shared pointer to nullptr work?
    // piece = nullptr;
    piece.reset();
}
