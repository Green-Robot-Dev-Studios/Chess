#ifndef GAME_H
#define GAME_H

#include "board.hpp"
#include "move.hpp"

#include <vector>

class Player;

enum GameState {
    Ongoing = 0,
    Check = 1,
    CheckmateWhite = 2,
    CheckmateBlack = 3,
    Stalemate = 4,
    ResignedWhite = 5,
    ResignedBlack = 6
};

class ChessGame {
    std::shared_ptr<Board> board;
    std::shared_ptr<Player> whitePlayer;
    std::shared_ptr<Player> blackPlayer;
    PieceColor turn;
    std::vector<Move> moveList;
    GameState gameState;

    void calculateState();
    std::pair<int, int> findKing(PieceColor color);
    std::vector<Move> generateLegalMovesInternal(PieceColor color);

public:
    ChessGame(std::shared_ptr<Board> board): board(board) {};
    ChessGame(std::shared_ptr<Board> board, std::shared_ptr<Player> whitePlayer, std::shared_ptr<Player> blackPlayer) : board(board), whitePlayer(whitePlayer), blackPlayer(blackPlayer) {};
    void setPlayers(std::shared_ptr<Player> white, std::shared_ptr<Player> black);
    void startGame();
    /* ****************** */
    // TODO: why do we need this?
    // void endGame();
    /* ****************** */
    void resign();
    bool move(const Move &move);
    GameState getState();
    PieceColor getTurn();
    void changeTurn();
    std::vector<Move> generateLegalMoves();
    bool isCapture(const Move &move);
    bool isCheck(const Move &move);
    bool isMoveSafe(const Move &move);
};

#endif
