#include <iostream>
#include <string>
#include "players.hpp"
#include "game.hpp"

using namespace std;

Move Human::getMove() {
    std::string answer;
    std::cout << "Where would you like to move: ";
    std::cin >> answer;

    // <oldRow><oldcolumn><newRow><newColumn>
    int oldColumn = answer[1] - 'a';
    int oldRow = 8 - (answer[0] - '0');
    int newColumn = answer[3] - 'a';
    int newRow = 8 - (answer[2] - '0');
    
    return Move{oldRow, oldColumn, newRow, newColumn};
}

Move Level1::getMove() {
    auto legalMoves = game->generateLegalMoves();
    return legalMoves[rand() % legalMoves.size()];
}

Move Level2::getMove() {
    auto legalMoves = game->generateLegalMoves();
    
    std::vector<Move> preferredMoves;

    // capturing moves and checks
    for (const auto& move: legalMoves) {
        if (game->isCapture(move) || game->isCheck(move)) {
            preferredMoves.push_back(move);
        }
    }

    if (preferredMoves.size() > 0) {
        return preferredMoves[rand() % preferredMoves.size()];
    }

    return legalMoves[rand() % legalMoves.size()];
}

Move Level3::getMove() {
    auto legalMoves = game->generateLegalMoves();
    
    std::vector<Move> preferredMoves;

    // check moves prioritized 
    for (const auto& move: legalMoves) {
        if (game->isCheck(move)) {
            preferredMoves.push_back(move);
        }
    }

    if (preferredMoves.size() > 0) {
        return preferredMoves[rand() % preferredMoves.size()];
    }

    // capturing moves
    for (const auto& move: legalMoves) {
        if (game->isCapture(move)) {
            preferredMoves.push_back(move);
        }
    }

    // avoid captures checks
    for (const auto& move: legalMoves) {
        if (game->isMoveSafe(move)) {
            preferredMoves.push_back(move);
        }
    }

    if (preferredMoves.size() > 0) {
        return preferredMoves[rand() % preferredMoves.size()];
    }

    return legalMoves[rand() % legalMoves.size()];
}

int Level4::minimax(ChessGame& game, int depth, int alpha, int beta, bool maximizingPlayer) {
    if (depth == 0 || game.getState() != Ongoing) {
        return game.evaluateBoard(color);
    }

    auto legalMoves = game.generateLegalMoves();
    if (maximizingPlayer) {
        int maxEval = -1000000;
        for (const auto& move: legalMoves) {
            ChessGame tempGame = game;
            tempGame.move(move);
            int eval = minimax(tempGame, depth - 1, alpha, beta, false);
            if (eval > maxEval) {
                maxEval = eval;
                if (depth == MAX_DEPTH) {
                    bestMove = move;
                }
            }
            alpha = std::max(alpha, eval);
            if (beta <= alpha) {
                break;
            }
        }
        return maxEval;
    } else {
        int minEval = 1000000;
        for (const auto& move: legalMoves) {
            ChessGame newGame = game;
            newGame.move(move);
            int eval = minimax(newGame, depth - 1, alpha, beta, true);
            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            if (beta <= alpha) {
                break;
            }
        }
        return minEval;
    }
}

Move Level4::getMove() {
    bestMove = Move{0, 0, 0, 0};
    minimax(*game, MAX_DEPTH, -1000000, 1000000, true);
    return bestMove;
}