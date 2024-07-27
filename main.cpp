#include "game.hpp"
#include "text_view.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <string>

int main() {
    std::shared_ptr<Board> board = std::make_shared<Board>();
    std::shared_ptr<Player> playerWhite = std::make_shared<Human>();
    std::shared_ptr<Player> playerBlack = std::make_shared<Human>();

    ChessGame game{board, playerWhite, playerBlack};
    game.startGame();

    TextView view = TextView(board);
    board->notifyObservers();

    // TODO: refactor getState calls

    while (game.getState() == Ongoing || game.getState() == Check) {
        if (game.getState() == Check) {
            std::cout << "Warning, you are in check!";
        }

        auto &current = game.getTurn() == White ? playerWhite : playerBlack;
        auto move = current->getMove();
        if (game.move(move)) {
            std::cout << "Moved!\n";
            game.changeTurn();
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
