#include "text_view.hpp"

void TextView::draw() {
    printf("=============== Printing Chess Board ===============\n");
    auto currentState = board->getState();
    for (auto i : currentState) {
        for (auto j : i) {
            if (j.isOccupied())
                printf("%c", j.getPiece()->getLetter());
            else 
                printf(" ");
        }
        printf("\n");
    }
    printf("================ End of Chess Board ================\n");
}
