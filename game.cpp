#include "game.hpp"
#include "move.hpp"
#include "pieces.hpp"
#include <memory>

void ChessGame::startGame() {
    gameState = Ongoing;
    moveList.clear();
    turn = White;
    board->resetBoard();
}

void ChessGame::resign() {
    if (turn == White) {
        gameState = ResignedWhite;
    } else {
        gameState = ResignedBlack;
    }
}

bool ChessGame::move(const Move &move) {
    std::shared_ptr<Piece> piece = board->getPieceAt(move.oldRow, move.oldCol);
    if (!piece->isMoveValid(move) || piece->getColor() != turn) {
        return false;
    }

    // TODO: check move logic
    // TODO: set game state

    board->move(move);
    return true;
}

GameState ChessGame::getState() { return gameState; }

PieceColor ChessGame::getTurn() { return turn; }

void ChessGame::changeTurn() {
    if (turn == White) {
        turn = Black;
    } else {
        turn = White;
    }
}

// TODO: refactor this into a stored pointer
std::pair<int, int> ChessGame::findKing(PieceColor color) {
    std::pair<int, int> loc;

    bool found = false;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            std::shared_ptr<Piece> piece = board->getPieceAt(i, j);
            if(std::dynamic_pointer_cast<King>(piece) && piece->getColor() == color) {
                loc = std::make_pair(i, j);
                found = true;
                break;
            }
        }

        if(found) {
            break;
        }
    }

    return loc;
}

void ChessGame::determineState() {
    
}

std::vector<Move> ChessGame::generateLegalMovesInternal(PieceColor color) {
    return {};
}

std::vector<Move> ChessGame::generateLegalMoves() {
    return turn == White ? generateLegalMovesInternal(White)
                         : generateLegalMovesInternal(Black);
}
