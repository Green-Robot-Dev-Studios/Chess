#include "graphical_view.hpp"

void GraphicalView::notify() { draw(); }

void GraphicalView::draw() {
    // if (d == NULL) d = XOpenDisplay(NULL);
    // if (d == NULL) {
    //     fprintf(stderr, "Cannot open display\n");
    //     exit(1);
    // }

    // s = DefaultScreen(d);
    // if (w == NULL) {
    //     w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 100, 100, 1,
    //                             BlackPixel(d, s), WhitePixel(d, s));
    //     XSelectInput(d, w, ExposureMask | KeyPressMask);
    //     XMapWindow(d, w);
    // }
}
