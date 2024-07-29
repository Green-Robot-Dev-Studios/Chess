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
    std::shared_ptr<Player> playerBlack = std::make_shared<Level1>(PieceColor::Black, &game); 
    game.setPlayers(playerWhite, playerBlack); 

    game.startGame();

    std::shared_ptr<TextView> textView = std::make_shared<TextView>(board);
    board->attach(textView);

    std::shared_ptr<GraphicalView> graphicalView = std::make_shared<GraphicalView>(board);
    board->attach(graphicalView);
    
    board->notifyObservers();

    std::string command;
    while (std::cin >> command) {
        if (command == "game") {
            break;
        } else if (command == "text") {

        } else if (command == "graphical") {

        } else {
            std::cout << "Invalid command." << std::endl;
        }
    }

    GameState state = game.getState();
    while (state == Ongoing || state == CheckForBlack || state == CheckForWhite) {
        if (state == (game.getTurn() == White ? CheckForBlack : CheckForWhite)) {
            if(game.getTurn() == White) {
                std::cout << "White is in check." << std::endl;
            } else {
                std::cout << "Black is in check." << std::endl;
            }
        }

        PieceColor currentColor = game.getTurn();
        std::shared_ptr<Player> &currentPlayer = currentColor == White ? playerWhite : playerBlack;

        Move move = currentPlayer->getMove();
        move.color = currentColor;
        
        std::cout<<"HI"<<std::endl;
        std::cout<<"current color: "<<currentColor<<std::endl;
        std::cout<<"current player: "<<currentPlayer->color<<std::endl;

        if (game.move(move)) {
            std::cout << "Moveda!" << std::endl;
            game.changeTurn();
        } else {
            std::cout << "Invalid move!" << std::endl;
        }

        state = game.getState();
    }

    if (state == CheckmateForWhite) std::cout << "Checkmate! White wins!" << std::endl;
    if (state == CheckmateForBlack) std::cout << "Checkmate! Black wins!" << std::endl;
    if (state == ResignedWhite) std::cout << "Black wins!" << std::endl;
    if (state == ResignedBlack) std::cout << "White wins!" << std::endl;
    if (state == Stalemate) std::cout << "Stalemate!" << std::endl;

    return 0;
}
