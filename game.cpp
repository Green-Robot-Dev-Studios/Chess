#include "game.hpp"

void ChessGame::startGame() {
    gameState = Ongoing;
    moveList.clear();
    turn = White;
    board.resetBoard();
}
