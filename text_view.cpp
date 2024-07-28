#include "text_view.hpp"
#include <cstdio>

void TextView::draw() {
    printf("=============== Printing Chess Board ===============\n");
    auto currentState = board->getState();
    int row = 8;
    for (auto i : currentState) {
        printf("%d  ", row);
        row--;

        int col = 8;
        for (auto j : i) {
            if (j.isOccupied()) {
                printf("%c", j.getPiece()->getLetter());
            } else {
                if ((row % 2 == 0 && col % 2 == 0) ||
                    (row % 2 != 0 && col % 2 != 0)) { 
                    // black
                    printf("░");
                } else { 
                    // white
                    printf("▓");
                }
            }

            col--;
        }
        printf("\n");
    }
    printf("\n   abcdefgh\n");
    printf("================ End of Chess Board ================\n");
}

void TextView::notify() { draw(); }
