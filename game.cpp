#include "game.hpp"
#include "move.hpp"
#include "pieces.hpp"
#include <memory>

void ChessGame::startGame() {
    gameState = Ongoing;
    moveList.clear();
    turn = White;
    board.resetBoard();
}

void ChessGame::resign() {
    if (turn == White) {
        gameState = ResignedWhite;
    } else {
        gameState = ResignedBlack;
    }
}

bool ChessGame::move(const Move &move) {
    std::shared_ptr<Piece> piece = board.getPieceAt(move.oldRow, move.oldCol);
    if (!piece->isMoveValid(move)) {
        return false;
    }

    board.move(move);
    return true;
}

GameState ChessGame::getState() { return gameState; }

GameState ChessGame::isCheck() {
    std::pair<int, int> loc = findKing(turn);
    
}

GameState ChessGame::isCheckmate() {

}

GameState ChessGame::isStalemate() {

}

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
            std::shared_ptr<Piece> piece = board.getPieceAt(i, j);
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

std::vector<Move> ChessGame::generateLegalMovesInternal(PieceColor color) {
    
}

std::vector<Move> ChessGame::generateLegalMoves() {
    return turn == White ? generateLegalMovesInternal(White)
                         : generateLegalMovesInternal(Black);
}
