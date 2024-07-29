#ifndef PLAYERS_H
#define PLAYERS_H

#include "move.hpp"
#include "game.hpp"

const int MAX_DEPTH = 3;

class Player {
// protected:
public:
    PieceColor color;
    int score;
    ChessGame* game;
// public:
    Player(PieceColor color, ChessGame* game) : color(color), score(0), game(game) {}
    virtual Move getMove() = 0;
};

class Human : public Player {
public:
    Human(PieceColor color, ChessGame* game) : Player(color, game) {}
    Move getMove() override;
};

class Computer : public Player {
public:
    Computer(PieceColor color, ChessGame* game) : Player(color, game) {}
};

class Level1 : public Computer {
public:
    Level1(PieceColor color, ChessGame* game) : Computer(color, game) {}
    Move getMove() override;
};

class Level2 : public Computer {
public:
    Level2(PieceColor color, ChessGame* game) : Computer(color, game) {}
    Move getMove() override;
};

class Level3 : public Computer {
public:
    Level3(PieceColor color, ChessGame* game) : Computer(color, game) {}
    Move getMove() override;
};

class Level4 : public Computer {
    Move bestMove;
    int minimax(ChessGame& game, int depth, int alpha, int beta, bool maximizingPlayer);
public:
    Level4(PieceColor color, ChessGame* game) : Computer(color, game) {}
    Move getMove() override;
};

#endif
