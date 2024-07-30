#include "game.hpp"
#include "graphical_view.hpp"
#include "move.hpp"
#include "text_view.hpp"
#include "players.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <string>

int main() {
    std::string command;

    std::shared_ptr<Board> board = std::make_shared<Board>();
    ChessGame game{board}; 

    std::shared_ptr<TextView> textView = std::make_shared<TextView>(board);
    board->attach(textView);

    std::shared_ptr<GraphicalView> graphicalView = std::make_shared<GraphicalView>(board);
    board->attach(graphicalView);
    

    board->resetBoard();
    board->placeDefault();
    game.setTurn(White);

    int whiteCount = 0;
    int blackCount = 0;

    srand(time(0));

    while (std::cout << "\n> " && std::cin >> command) {
        if (command == "game") {
            board->notifyObservers();

            std::string player1, player2;
            std::cin >> player1 >> player2;

            std::shared_ptr<Player> playerWhite, playerBlack;

            if (player1 == "human") {
                playerWhite = std::make_shared<Human>(PieceColor::White, &game);
            } else if (player1 == "computer1") {
                playerWhite = std::make_shared<Level1>(PieceColor::White, &game);
            } else if (player1 == "computer2") {
                playerWhite = std::make_shared<Level2>(PieceColor::White, &game);
            } else if (player1 == "computer3") {
                playerWhite = std::make_shared<Level3>(PieceColor::White, &game);
            } else if (player1 == "computer4") {
                playerBlack = std::make_shared<Level4>(PieceColor::White, &game);
            } else {
                std::cout << "Invalid player for white." << std::endl;
                continue;
            }

            if (player2 == "human") {
                playerBlack = std::make_shared<Human>(PieceColor::Black, &game);
            } else if (player2 == "computer1") {
                playerBlack = std::make_shared<Level1>(PieceColor::Black, &game);
            } else if (player2 == "computer2") {
                playerBlack = std::make_shared<Level2>(PieceColor::Black, &game);
            } else if (player2 == "computer3") {
                playerBlack = std::make_shared<Level3>(PieceColor::Black, &game);
            } else if (player2 == "computer4") {
                playerBlack = std::make_shared<Level4>(PieceColor::Black, &game);
            } else {
                std::cout << "Invalid player for black." << std::endl;
                continue;
            }

            game.setPlayers(playerWhite, playerBlack); 

            game.startGame();

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

                if (!currentPlayer->isHuman) {
                    std::cout << "Computer to play. (type `move`) > ";

                    Move move = currentPlayer->getMove();
                    move.color = currentColor;

                    std::string subcommand;
                    std::cin >> subcommand;
                    if (subcommand != "move") {
                        std::cout << "Invalid command";
                        continue;
                    }

                    if (game.move(move)) {
                        std::cout << "Moved!" << std::endl;
                        game.changeTurn();
                    } else {
                        std::cout << "Invalid move by Computer!" << std::endl;
                        continue;
                    }
                } else {
                    std::cout << (currentColor == White ? "White" : "Black") << " to play. > ";

                    std::string subcommand;
                    std::cin >> subcommand;
                    if (subcommand == "resign") {
                        game.resign();
                        break;
                    } else if (subcommand == "move") {
                        Move move = currentPlayer->getMove();
                        move.color = currentColor;
                        
                        if (game.isPromotion(move)) {
                            std::string piece;
                            std::cin >> piece;

                            std::shared_ptr<Piece> p;
                            if (piece == "Q") p = std::make_shared<Queen>(White, move.newRow, move.newCol);
                            if (piece == "q") p = std::make_shared<Queen>(Black, move.newRow, move.newCol);
                            if (piece == "R") p = std::make_shared<Rook>(White, move.newRow, move.newCol);
                            if (piece == "r") p = std::make_shared<Rook>(Black, move.newRow, move.newCol);
                            if (piece == "N") p = std::make_shared<Knight>(White, move.newRow, move.newCol);
                            if (piece == "n") p = std::make_shared<Knight>(Black, move.newRow, move.newCol);
                            if (piece == "B") p = std::make_shared<Bishop>(White, move.newRow, move.newCol);
                            if (piece == "b") p = std::make_shared<Bishop>(Black, move.newRow, move.newCol);

                            if (game.movePromotion(move, p)) {
                                std::cout << "Moved!" << std::endl;
                                game.changeTurn();
                            } else {
                                std::cout << "Invalid move!" << std::endl;
                                continue;
                            }
                        } else {
                            if (game.move(move)) {
                                std::cout << "Moved!" << std::endl;
                                game.changeTurn();
                            } else {
                                std::cout << "Invalid move!" << std::endl;
                                continue;
                            }
                        }

                    } else {
                        std::cout << "Invalid command." << std::endl;
                        continue;
                    }
                }

                state = game.getState();
            }

            if (state == CheckmateForWhite) {
                std::cout << "Checkmate! White wins!" << std::endl;
                whiteCount++;
            }
            if (state == CheckmateForBlack) {
                std::cout << "Checkmate! Black wins!" << std::endl;
                blackCount++;
            }
            if (state == ResignedWhite) std::cout << "Black wins!" << std::endl;
            if (state == ResignedBlack) std::cout << "White wins!" << std::endl;
            if (state == Stalemate) std::cout << "Stalemate!" << std::endl;

            board->resetBoard();
            board->placeDefault();
            game.setTurn(White);
        } else if (command == "setup") {
            
            board->resetBoard();
            std::string subcommand; 
            std::cout << "Entering Setup Mode. \n";

            // board->notifyObservers();

            while (std::cout << "\nsetup > " && std::cin >> subcommand) {
                if (subcommand == "+") {
                    std::string piece, spot;
                    std::cin >> piece >> spot;
                    std::shared_ptr<Piece> p;
                    int row = 8 - (spot[1] - '0');
                    int col = spot[0] - 'a';

                    if (piece == "K") p = std::make_shared<King>(White, row, col);
                    if (piece == "k") p = std::make_shared<King>(Black, row, col);
                    if (piece == "Q") p = std::make_shared<Queen>(White, row, col);
                    if (piece == "q") p = std::make_shared<Queen>(Black, row, col);
                    if (piece == "R") p = std::make_shared<Rook>(White, row, col);
                    if (piece == "r") p = std::make_shared<Rook>(Black, row, col);
                    if (piece == "N") p = std::make_shared<Knight>(White, row, col);
                    if (piece == "n") p = std::make_shared<Knight>(Black, row, col);
                    if (piece == "B") p = std::make_shared<Bishop>(White, row, col);
                    if (piece == "b") p = std::make_shared<Bishop>(Black, row, col);
                    if (piece == "P") p = std::make_shared<Pawn>(White, row, col);
                    if (piece == "p") p = std::make_shared<Pawn>(Black, row, col);

                    if (game.findKing(White, *board).first != -1 && piece == "K") {
                        std::cout << "Invalid setup." << std::endl;
                        continue;
                    } else if (game.findKing(Black, *board).first != -1 && piece == "k") {
                        std::cout << "Invalid setup." << std::endl;
                        continue;
                    }

                    if (piece == "P" && row == 0) {
                        std::cout << "Invalid setup." << std::endl;
                        continue;
                    } else if (piece == "p" && row == 7) {
                        std::cout << "Invalid setup." << std::endl;
                        continue;
                    }

                    if (board->board[row][col].isOccupied()) board->board[row][col].removePiece();
                    board->board[row][col].setPiece(p);
                } else if (subcommand == "-") {
                    std::string spot;
                    std::cin >> spot;
                    if (board->board[8 - (spot[1] - '0')][spot[0] - 'a'].isOccupied()) {
                        board->board[8 - (spot[1] - '0')][spot[0] - 'a'].removePiece();
                    }
                } else if (subcommand == "=") {
                    std::string color;
                    std::cin >> color;

                    game.setTurn(color == "white" ? White : Black);
                    std::cout<<game.getTurn()<<std::endl;
                } else if (subcommand == "done") {
                    break;
                } else {
                    std::cout << "Invalid command." << std::endl;
                }

                board->notifyObservers();
            }

        } else {
            std::cout << "Invalid command." << std::endl;
        }

    }

    std::cout << "Final Score: \n" << "White: " << whiteCount << "\nBlack: " << blackCount << std::endl;
    std::cout << "Goodbye!" << std::endl;
    
    return 0;
}
