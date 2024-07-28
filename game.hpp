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

    void computeState() const;
    std::pair<int, int> findKing(PieceColor color, const Board &board) const;

    bool isValidMove(PieceColor turn, const Move &move, const Board &board) const;

    bool isCaptureInternal(const Move &move, const Board &board) const;
    bool isCheckInternal(const Move &move, const Board &board) const;
    std::vector<Move> generateLegalMovesInternal(PieceColor color, const Board &board) const;

public:
    ChessGame(std::shared_ptr<Board> board) : board(board) {};
    ChessGame(std::shared_ptr<Board> board, std::shared_ptr<Player> whitePlayer,
              std::shared_ptr<Player> blackPlayer)
        : board(board), whitePlayer(whitePlayer), blackPlayer(blackPlayer) {};

    void startGame();
    void changeTurn();
    bool move(const Move &move);
    void resign();

    GameState getState() const;
    PieceColor getTurn() const;
    std::vector<Move> generateLegalMoves() const;

    void setPlayers(std::shared_ptr<Player> white,
                    std::shared_ptr<Player> black);

    bool isCapture(const Move &move) const;
    bool isCheck(const Move &move) const;
    bool isMoveSafe(const Move &move) const;
    std::pair<int, int> findKing(PieceColor color) const;  
    int evaluateBoard(PieceColor color) const;
};

#endif
