#include <iostream>
#include <string>
#include "players.hpp"

using namespace std;


#include <string>
#include "players.hpp"

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
    
    return Move{ oldRow, oldColumn, newRow, newColumn };
}
