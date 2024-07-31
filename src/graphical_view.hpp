#ifndef GRAPHICAL_VIEW_H
#define GRAPHICAL_VIEW_H

#include "render_view.hpp"
#include <memory>
#include <X11/Xlib.h>
#include <unordered_map>

class GraphicalView : public ViewChild {
    Display *d;
    Window w;
    int s;
    GC gc;
    std::unordered_map<char, std::pair<Pixmap, Pixmap>> piecePixmaps;

    unsigned long colors[10];

    void drawRect(int x, int y, int width, int height, unsigned long color);
    void drawString(int, int, char);
    void drawPiece(int, int, char, bool);

public:
    void draw() override;
    void notify() override;
    GraphicalView(std::shared_ptr<Board> board);
};

#endif
