#ifndef PLAYERS_H
#define PLAYERS_H

#include "move.hpp"

class Player {
    PieceColor color;
    int score;
private:
    virtual Move getMove() = 0;
};

class Human : public Player {};

class Computer : public Player {

};

class Level1 : public Computer {

};

class Level2 : public Computer {

};

class Level3 : public Computer {

};

class Level4 : public Computer {

};

#endif
