#ifndef GRAPHICAL_VIEW_H
#define GRAPHICAL_VIEW_H

#include "render_view.hpp"
#include <memory>
#include <string>
#include <X11/Xlib.h>
#include <map>

class GraphicalView : public ViewChild {
    Display *d;
    Window w;
    int s;
    GC gc;
    std::unordered_map<char, Pixmap> piecePixmaps;

    unsigned long colors[10];


    void draw() override;
    void notify() override;

    void drawRect(int x, int y, int width, int height, unsigned long color);
    void drawString(int, int, char);
public:
    GraphicalView(std::shared_ptr<Board> board);
};

#endif
