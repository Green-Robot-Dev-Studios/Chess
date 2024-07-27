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
    Stalemate
};

class ChessGame {
    Board board;
    Player whitePlayer;
    Player blackPlayer;
    PieceColor turn;
    std::vector<Move> moveList;
    GameState gameState;

public:
    void startGame();
    void endGame();
    void resign();
    void move(Move);
    GameState checkState();
    bool isCheck();
    bool isWhiteCheckmate();
    bool isBlackCheckmate();
    bool isStalemate();
    PieceColor getTurn();
    void changeTurn();
};

#endif
