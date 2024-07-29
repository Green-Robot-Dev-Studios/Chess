#include "game.hpp"
#include "graphical_view.hpp"
#include "text_view.hpp"
#include "players.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <string>

int main() {
    std::shared_ptr<Board> board = std::make_shared<Board>();
    ChessGame game{board}; 

    std::shared_ptr<Player> playerWhite = std::make_shared<Human>(PieceColor::White, &game); 
    std::shared_ptr<Player> playerBlack = std::make_shared<Human>(PieceColor::Black, &game); 
    game.setPlayers(playerWhite, playerBlack); 

    game.startGame();

    TextView view = TextView(board);
    GraphicalView graphical_view = GraphicalView(board);
    board->notifyObservers();

    while (game.getState() == Ongoing || game.getState() == CheckForBlack || game.getState() == CheckForWhite) {
        if (game.getState() == (game.getTurn() == White ? CheckForBlack : CheckForWhite)) {
            std::cout << "Warning, you are in check!" << std::endl;
        }

        PieceColor currentColor = game.getTurn();
        std::shared_ptr<Player> &currentPlayer = currentColor == White ? playerWhite : playerBlack;

        Move move = currentPlayer->getMove();
        move.color = currentColor;

        if (game.move(move)) {
            std::cout << "Moved!\n";
            game.changeTurn();
        } else {
            std::cout << "Invalid move!\n";
        }
    }

    if (game.getState() == CheckmateForWhite) std::cout << "Black in checkmate!\n";
    if (game.getState() == CheckmateForBlack) std::cout << "White in checkmate!\n";
    if (game.getState() == ResignedWhite) std::cout << "White resigns!\n";
    if (game.getState() == ResignedBlack) std::cout << "Black resigns!\n";
    if (game.getState() == Stalemate) std::cout << "Stalemate!\n";

    return 0;
}
