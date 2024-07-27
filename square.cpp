#include "square.hpp"

Square::Square(int r, int c) : row(r), col(c), piece(nullptr) {}

bool Square::isOccupied() {
    return piece != nullptr;
}

void Square::setPiece(Piece piece) {
    this->piece = std::make_shared<Piece>(piece);
}

std::shared_ptr<Piece> Square::getPiece() { 
    return piece;
}
