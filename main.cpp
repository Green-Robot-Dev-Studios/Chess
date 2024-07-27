#include "game.hpp"
#include <iostream>
#include <vector>
#include <string>

int main() {
    ChessGame game{};
    game.startGame();

    // CHORE: refactor getState calls

    while (game.getState() == Ongoing || game.getState() == Check) {
        if (game.getState() == Check) 
            std::cout << "Warning, you are in check!";

        std::string answer;
        std::cout << "Where would you like to move: ";
        std::cin >> answer;

        // <oldRow><oldColumn><newRow><newColumn>
        int oldRow = answer[0] - '0';
        int oldColumn = answer[1] - '0';
        int newRow = answer[2] - '0';
        int newColumn = answer[3] - '0';
        if (game.move(Move{ oldRow, oldColumn, newRow, newColumn })) {
            std::cout << "Moved!\n";
        } else {
            std::cout << "Invalid move!\n";
        }
    }

    if (game.getState() == CheckmateWhite) std::cout << "White checkmate!\n";
    if (game.getState() == CheckmateBlack) std::cout << "Black checkmate!\n";
    if (game.getState() == ResignedWhite) std::cout << "White resignation!\n";
    if (game.getState() == ResignedBlack) std::cout << "Black resignation!\n";
    if (game.getState() == Stalemate) std::cout << "Stalemate!\n";

    return 0;
}
