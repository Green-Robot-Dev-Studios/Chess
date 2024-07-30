#ifndef GAME_H
#define GAME_H

#include "board.hpp"
#include "move.hpp"
#include "pieces.hpp"

#include <vector>

class Player;

// for <color> means that <color> is in an advantageous position
enum GameState {
    Ongoing = 0,
    CheckForWhite = 1,
    CheckForBlack = 2,
    CheckmateForWhite = 3,
    CheckmateForBlack = 4,
    Stalemate = 5,
    ResignedWhite = 6,
    ResignedBlack = 7
};

class ChessGame {
    std::shared_ptr<Board> board;
    std::shared_ptr<Player> whitePlayer;
    std::shared_ptr<Player> blackPlayer;

    PieceColor turn = White;
    GameState gameState;

    std::vector<Move> moveList = {};

    bool isKingInCheckInternal(PieceColor kingColor, const Board &board) const;
    bool isValidMove(PieceColor turn, const Move &move, const Board &board) const;

    bool isCaptureInternal(const Move &move, const Board &board) const;
    bool isCaptureTargetInternal(const Move &move, std::pair<int, int> target) const;
    bool isCheckInternal(const Move &move, std::pair<int, int> king) const;

    bool moveInternal(const Move &move);
    std::vector<Move> generateLegalMovesInternal(PieceColor color, const Board &board) const;

public:
    ChessGame();
    ChessGame(std::shared_ptr<Board> board) : board(board) {};
    ChessGame(std::shared_ptr<Board> board, std::shared_ptr<Player> whitePlayer,
              std::shared_ptr<Player> blackPlayer)
        : board(board), whitePlayer(whitePlayer), blackPlayer(blackPlayer) {};
    ChessGame(const ChessGame &game);
    void startGame();
    void changeTurn();
    void resign();

    void computeStalemate();
    std::pair<int, int> findKing(PieceColor color, const Board &board) const;

    bool move(const Move &move);
    bool movePromotion(const Move &move, std::shared_ptr<Piece> promotedPiece);

    GameState getState() const;
    PieceColor getTurn() const;
    std::vector<Move> generateLegalMoves() const;

    void setPlayers(std::shared_ptr<Player> white,
                    std::shared_ptr<Player> black);
    void setTurn(PieceColor turn);

    bool isCapture(const Move &move) const;
    bool isCheck(const Move &move) const;
    bool isMoveSafe(const Move &move) const;
    bool isPromotion(const Move &move) const;

    bool kingIsInCheck(PieceColor kingColor) const;

    int evaluateBoard(PieceColor color) const;
};

#endif
