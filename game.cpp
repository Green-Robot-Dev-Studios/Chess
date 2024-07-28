#include "game.hpp"
#include "move.hpp"
#include "pieces.hpp"
#include <cmath>
#include <memory>

bool withinBoard(int row, int col) {
    return row >= 0 && col >= 0 && row < 8 && col < 8;
}

// computes stalemate
void ChessGame::computeState(){
    if (gameState != (turn == White ? CheckForBlack : CheckForWhite) && generateLegalMoves().size() == 0) {
        gameState = Stalemate;
    }
}

std::pair<int, int> ChessGame::findKing(PieceColor color,
                                        const Board &board) const {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            std::shared_ptr<Piece> piece = board.getPieceAt(i, j);
            if (std::dynamic_pointer_cast<King>(piece) &&
                piece->getColor() == color) {
                return std::make_pair(i, j);
            }
        }
    }

    return std::make_pair(-1, -1);
}

bool ChessGame::isKingInCheck(PieceColor kingColor, const Board &board) const {
    std::vector<Move> opponentMoves =
        generateLegalMovesInternal(kingColor == White ? Black : White, board);

    std::pair<int, int> king = findKing(kingColor, board);
    for (const auto &m : opponentMoves) {
        if (isCheckInternal(m, king)) {
            return true;
        }
    }

    return false;
}

bool ChessGame::isValidMove(PieceColor turn, const Move &move,
                            const Board &board) const {
    std::shared_ptr<Piece> piece = board.getPieceAt(move.oldRow, move.oldCol);

    if (!withinBoard(move.newRow, move.newCol) || !piece->isMoveValid(move) ||
        piece->getColor() != turn) {
        return false;
    }

    std::shared_ptr<Piece> nextPiece =
        board.getPieceAt(move.newRow, move.newCol);

    // can't capture a piece of player's own color; also checks for self moves
    if (piece->getColor() == nextPiece->getColor()) {
        return false;
    }

    int dy = abs(move.newRow - move.oldRow);
    int dx = abs(move.newCol - move.oldCol);

    // all pieces that can move more than one cell at a time in a direction
    // excludes knights that can "jump" over other pieces
    if (std::dynamic_pointer_cast<Bishop>(piece) ||
        std::dynamic_pointer_cast<Queen>(piece) ||
        std::dynamic_pointer_cast<Rook>(piece) ||
        std::dynamic_pointer_cast<Pawn>(piece)) {
        for (int i = move.oldRow; i != move.newRow;
             i += (move.newRow - move.oldRow) / dy) {
            for (int j = move.oldCol; j != move.newCol;
                 j += (move.newCol - move.oldCol) / dx) {
                // none of the positions between source and destination can be
                // occupied
                if (i != move.newRow && j != move.newCol &&
                    board.getPieceAt(i, j) != nullptr) {
                    return false;
                }

                // pawn can't move forward into another piece
                if (std::dynamic_pointer_cast<Pawn>(piece) && dx == 0) {
                    return false;
                }
            }
        }
    }

    if (std::dynamic_pointer_cast<Pawn>(piece)) {
        // check that two cell advance only occurs on first move
        if (dy > 1 && piece->getMoveCount() > 0) {
            return false;
        }

        // check that only a capture move may be diagonal
        if (dy > 0 && dx > 0 && nextPiece == nullptr) {
            return false;
        }

        // TODO: en passant
    }

    if (std::dynamic_pointer_cast<King>(piece)) {
        // check castling conditions
        if (dx == 2) {
            bool direction = (move.newCol - move.oldCol) < 0;
            std::shared_ptr<Piece> nextPiece =
                turn == White ? (direction ? board.getPieceAt(7, 0)
                                           : board.getPieceAt(7, 7))
                              : (direction ? board.getPieceAt(0, 0)
                                           : board.getPieceAt(0, 7));

            // check that rook exists
            if (nextPiece == nullptr ||
                !std::dynamic_pointer_cast<Rook>(nextPiece)) {
                return false;
            }

            // check that king and rook haven't moved
            if (piece->getMoveCount() > 0 || nextPiece->getMoveCount() > 0) {
                return false;
            }

            // check that there are no pieces in between
            for (int j = move.oldCol; j != nextPiece->getCol();
                 j += (move.newCol - move.oldCol) / dx) {
                if (j != nextPiece->getCol() &&
                    board.getPieceAt(move.oldRow, j) != nullptr) {
                    return false;
                }
            }
        }
    }

    return true;
}

bool ChessGame::isCaptureInternal(const Move &move, const Board &board) const {
    return board.getPieceAt(move.newRow, move.newCol) != nullptr;
}

bool ChessGame::isCheckInternal(const Move &move,
                                std::pair<int, int> king) const {
    return move.newRow == king.first && move.newCol == king.second;
}

std::vector<Move>
ChessGame::generateLegalMovesInternal(PieceColor color,
                                      const Board &board) const {
    std::vector<Move> legalMoves = {};

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            for (int k = 0; k < 8; ++k) {
                for (int l = 0; l < 8; l++) {
                    Move move = Move{i, j, k, l, color};
                    if (isValidMove(color, move, board)) {
                        legalMoves.push_back(move);
                    }
                }
            }
        }
    }
}

void ChessGame::startGame() {
    gameState = Ongoing;
    moveList.clear();
    turn = White;
    board->resetBoard();
}

void ChessGame::changeTurn() { turn = turn == White ? Black : White; }

bool ChessGame::move(const Move &move) {
    if (!isValidMove(turn, move, *board)) {
        return false;
    }

    Board preliminaryBoard = Board(*board);
    preliminaryBoard.move(move);

    // check if move puts king in check
    if (isKingInCheck(turn, preliminaryBoard)) {
        return false;
    }

    // TODO: castling
    // TODO: en passant
    // TODO: pawn promotion

    // compute game state

    // check if move puts opponents king in check
    if (isKingInCheck(turn == White ? Black : White, preliminaryBoard)) {
        gameState = turn == White ? CheckForWhite : CheckForBlack;

        std::vector<Move> opponentMoves = generateLegalMovesInternal(
            turn == White ? Black : White, preliminaryBoard);

        // if none of these moves result in opponent being out of check ->
        // checkmate
        bool outOfCheck = false;
        for (const auto &m : opponentMoves) {
            Board preliminaryOpponentBoard = Board(preliminaryBoard);
            preliminaryOpponentBoard.move(m);

            if (!isKingInCheck(turn == White ? Black : White,
                               preliminaryOpponentBoard)) {
                outOfCheck = true;
                break;
            }
        }

        if (!outOfCheck) {
            gameState = turn == White ? CheckmateForWhite : CheckmateForBlack;
        }
    }

    board->move(move);
    return true;
}

void ChessGame::resign() {
    gameState = turn == White ? ResignedWhite : ResignedBlack;
}

GameState ChessGame::getState() const {
    return gameState;
}

PieceColor ChessGame::getTurn() const { return turn; }

std::vector<Move> ChessGame::generateLegalMoves() const {
    std::vector<Move> legalMoves =
        turn == White ? generateLegalMovesInternal(White, *board)
                      : generateLegalMovesInternal(Black, *board);

    std::vector<Move> nonCheckLegalMoves = {};

    // remove moves that put king into check
    for (const auto &m : legalMoves) {
        Board preliminaryBoard = Board(*board);
        preliminaryBoard.move(m);

        if (!isKingInCheck(turn, preliminaryBoard)) {
            nonCheckLegalMoves.push_back(m);
        }
    }

    return nonCheckLegalMoves;
}

void ChessGame::setPlayers(std::shared_ptr<Player> white,
                           std::shared_ptr<Player> black) {
    this->whitePlayer = white;
    this->blackPlayer = black;
}

bool ChessGame::isCapture(const Move &move) const {
    return isCaptureInternal(move, *board);
}

bool ChessGame::isCheck(const Move &move) const {
    return isCheckInternal(
        move, findKing(move.color == White ? Black : White, *board));
}
