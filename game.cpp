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
    if(turn == White) {
        gameState = ResignedWhite;
    } else {
        gameState = ResignedBlack;
    }
}

bool ChessGame::move(const Move &move) {
    std::shared_ptr<Piece> piece = board.getPieceAt(move.oldRow, move.oldCol);
    if(!piece -> isMoveValid(move)) {
        return false;
    }

    board.move(move);
    return true;
}

GameState ChessGame::getState() {
    return gameState;
}

GameState ChessGame::isCheck() {
    
}

GameState ChessGame::isCheckmate() {

}

GameState ChessGame::isStalemate() {

}
