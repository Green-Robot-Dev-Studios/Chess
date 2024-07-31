#include "graphical_view.hpp"
#include "bitmaps.hpp"

#include <iostream>
#include <memory>
#include <unistd.h>
#include <map>
#include <cstring>
#include <utility>

GraphicalView::GraphicalView(std::shared_ptr<Board> board) : ViewChild(board) {
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
    
    XColor white, black;
    white.pixel = 0xffffffff;
    black.pixel = 0x00000000;

    unsigned long yellow = colors[2];
    unsigned long brown = colors[3];


    piecePixmaps['K'] = {
        XCreatePixmapFromBitmapData(d, w, (char*)king, size, size, yellow, white.pixel, depth),
        XCreatePixmapFromBitmapData(d, w, (char*)king, size, size, brown, white.pixel, depth)
    };
    piecePixmaps['Q'] = {
        XCreatePixmapFromBitmapData(d, w, (char*)queen, size, size, yellow, white.pixel, depth),
        XCreatePixmapFromBitmapData(d, w, (char*)queen, size, size, brown, white.pixel, depth)
    };
    piecePixmaps['R'] = {
        XCreatePixmapFromBitmapData(d, w, (char*)rook, size, size, yellow, white.pixel, depth),
        XCreatePixmapFromBitmapData(d, w, (char*)rook, size, size, brown, white.pixel, depth)
    };
    piecePixmaps['N'] = {
        XCreatePixmapFromBitmapData(d, w, (char*)knight, size, size, yellow, white.pixel, depth),
        XCreatePixmapFromBitmapData(d, w, (char*)knight, size, size, brown, white.pixel, depth)
    };
    piecePixmaps['B'] = {
        XCreatePixmapFromBitmapData(d, w, (char*)bishop, size, size, yellow, white.pixel, depth),
        XCreatePixmapFromBitmapData(d, w, (char*)bishop, size, size, brown, white.pixel, depth)
    };
    piecePixmaps['P'] = {
        XCreatePixmapFromBitmapData(d, w, (char*)pawn, size, size, yellow, white.pixel, depth),
        XCreatePixmapFromBitmapData(d, w, (char*)pawn, size, size, brown, white.pixel, depth)
    };
    piecePixmaps['k'] = {
        XCreatePixmapFromBitmapData(d, w, (char*)king, size, size, yellow, black.pixel, depth),
        XCreatePixmapFromBitmapData(d, w, (char*)king, size, size, brown, black.pixel, depth)
    };
    piecePixmaps['q'] = {
        XCreatePixmapFromBitmapData(d, w, (char*)queen, size, size, yellow, black.pixel, depth),
        XCreatePixmapFromBitmapData(d, w, (char*)queen, size, size, brown, black.pixel, depth)
    };
    piecePixmaps['r'] = {
        XCreatePixmapFromBitmapData(d, w, (char*)rook, size, size, yellow, black.pixel, depth),
        XCreatePixmapFromBitmapData(d, w, (char*)rook, size, size, brown, black.pixel, depth)
    };
    piecePixmaps['n'] = {
        XCreatePixmapFromBitmapData(d, w, (char*)knight, size, size, yellow, black.pixel, depth),
        XCreatePixmapFromBitmapData(d, w, (char*)knight, size, size, brown, black.pixel, depth)
    };
    piecePixmaps['b'] = {
        XCreatePixmapFromBitmapData(d, w, (char*)bishop, size, size, yellow, black.pixel, depth),
        XCreatePixmapFromBitmapData(d, w, (char*)bishop, size, size, brown, black.pixel, depth)
    };
    piecePixmaps['p'] = {
        XCreatePixmapFromBitmapData(d, w, (char*)pawn, size, size, yellow, black.pixel, depth),
        XCreatePixmapFromBitmapData(d, w, (char*)pawn, size, size, brown, black.pixel, depth)
    };



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

void GraphicalView::drawPiece(int x, int y, char letter, bool isYellow) {
    if (letter == ' ') return;

    XCopyArea(d, isYellow ? piecePixmaps[letter].first : piecePixmaps[letter].second, w, gc, 0, 0, 48, 48, x + 8, y + 8);
    XFlush(d);
}

void GraphicalView::drawString(int x, int y, char letter) {
    char str[2] = {letter, '\0'};
    XDrawString(d, w, gc, x, y, str, (int)strlen(str));
    XFlush(d);
}

void GraphicalView::draw() {
    XClearWindow(d, w);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            unsigned long color;
            if ((i % 2 == 0 && j % 2 != 0) || (i % 2 != 0 && j % 2 == 0)) {
                color = colors[3];
                drawRect(i * 64, j * 64, 64, 64, color);
            }
            else {
                color = colors[2];
                drawRect(i * 64, j * 64, 64, 64, color);
            }

            if (i == 0) {
                drawString(0, j * 64 + 10, '8' - j);
            }

            if (!board->getPieceAt(j, i)) continue;
            drawPiece(i * 64, j * 64, board->getPieceAt(j, i)->getLetter(), color == colors[2]);
        }

        drawString(i * 64, 64*8, 'a' + i);
    }
}
