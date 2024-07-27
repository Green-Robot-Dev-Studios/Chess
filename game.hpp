#ifndef GAME_H
#define GAME_H

#include "board.hpp"
#include "players.hpp"
#include "move.hpp"

#include <vector>

enum GameState {
    Ongoing,
    Check,
    CheckmateWhite,
    CheckmateBlack,
    Stalemate,
    ResignedWhite,
    ResignedBlack
};

class ChessGame {
    Board board;
    std::shared_ptr<Player> whitePlayer;
    std::shared_ptr<Player> blackPlayer;
    PieceColor turn;
    std::vector<Move> moveList;
    GameState gameState;

public:
    void startGame();
    /* ****************** */
    // TODO: why do we need this?
    // void endGame();
    /* ****************** */
    void resign();
    bool move(const Move &move);
    GameState getState();
    GameState isCheck();
    GameState isCheckmate();
    GameState isStalemate();
    PieceColor getTurn();
    void changeTurn();
    std::vector<Move> generateLegalMoves();
};

#endif
