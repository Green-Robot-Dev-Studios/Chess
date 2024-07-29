#include "graphical_view.hpp"
#include "bitmaps.cpp"

#include <iostream>
#include <memory>
#include <unistd.h>
#include <map>

GraphicalView::GraphicalView(std::shared_ptr<Board> board) : ViewChild(board) {
    board->attach(std::shared_ptr<Observer>(this));

    constexpr int WIDTH = 64*8;
    constexpr int HEIGHT = 64*8;

    d = XOpenDisplay(NULL);
    if (d == NULL) {
        std::cerr << "Cannot open display" << std::endl;
        exit(1);
    }
    s = DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, WIDTH, HEIGHT, 1,
                            BlackPixel(d, s), WhitePixel(d, s));
    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapRaised(d, w);

    gc = XCreateGC(d, w, 0, NULL);

    XFlush(d);
    XFlush(d);

    XColor xcolour;
    Colormap cmap;
    char color_vals[7][20] = {"white", "black", "goldenrod", "saddle brown", "blue"};

    cmap = DefaultColormap(d, DefaultScreen(d));
    for (int i = 0; i < 5; ++i) {
        XParseColor(d, cmap, color_vals[i], &xcolour);
        XAllocColor(d, cmap, &xcolour);
        colors[i] = xcolour.pixel;
    }

    XSetForeground(d, gc, colors[0]);
    XSynchronize(d, True);
    sleep(1);

    int size = 48;
    unsigned int depth = DefaultDepth(d, DefaultScreen(d));
    unsigned long black = XBlackPixel(d, s);
    unsigned long white = XWhitePixel(d, s);
    piecePixmaps['K'] = XCreatePixmapFromBitmapData(d, w, (char*)king, size, size, black, white, depth);
    piecePixmaps['Q'] = XCreatePixmapFromBitmapData(d, w, (char*)queen, size, size, black, white, depth);
    piecePixmaps['R'] = XCreatePixmapFromBitmapData(d, w, (char*)rook, size, size, black, white, depth);
    piecePixmaps['B'] = XCreatePixmapFromBitmapData(d, w, (char*)bishop, size, size, black, white, depth);
    piecePixmaps['N'] = XCreatePixmapFromBitmapData(d, w, (char*)knight, size, size, black, white, depth);
    piecePixmaps['P'] = XCreatePixmapFromBitmapData(d, w, (char*)pawn, size, size, black, white, depth);
    piecePixmaps['k'] = XCreatePixmapFromBitmapData(d, w, (char*)king, size, size, white, black, depth);
    piecePixmaps['q'] = XCreatePixmapFromBitmapData(d, w, (char*)queen, size, size, white, black, depth);
    piecePixmaps['r'] = XCreatePixmapFromBitmapData(d, w, (char*)rook, size, size, white, black, depth);
    piecePixmaps['b'] = XCreatePixmapFromBitmapData(d, w, (char*)bishop, size, size, white, black, depth);
    piecePixmaps['n'] = XCreatePixmapFromBitmapData(d, w, (char*)knight, size, size, white, black, depth);
    piecePixmaps['p'] = XCreatePixmapFromBitmapData(d, w, (char*)pawn, size, size, white, black, depth);
    XFlush(d);
    sleep(1);
};

void GraphicalView::notify() { draw(); }

void GraphicalView::drawRect(int x, int y, int width, int height, unsigned long color) {
    XSetForeground(d, gc, color);
    XFillRectangle(d, w, gc, x, y, width, height);
    XSetForeground(d, gc, colors[0]);

    XFlush(d);
}

void GraphicalView::drawString(int x, int y, char letter) {
    if (letter == ' ') return;

    XCopyArea(d, piecePixmaps[letter], w, gc, 0, 0, 48, 48, x + 8, y + 8);
    XFlush(d);
}

void GraphicalView::draw() {
    XClearWindow(d, w);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i % 2 == 0 && j % 2 != 0 || i % 2 != 0 && j % 2 == 0) {
                drawRect(i * 64, j * 64, 64, 64, colors[3]);
            }
            else {
                drawRect(i * 64, j * 64, 64, 64, colors[2]);
            }
            if (!board->getPieceAt(j, i)) continue;
            drawString(i * 64, j * 64, board->getPieceAt(j, i)->getLetter());
        }
    }
}
