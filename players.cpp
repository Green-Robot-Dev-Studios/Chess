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
    int oldRow = 8 - (answer[0] - '0');
    int oldColumn = answer[1] - 'a';
    int newRow = 8 - (answer[2] - '0');
    int newColumn = answer[3] - 'a';
    
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
        
    }
    return {0, 0, 0, 0};
}