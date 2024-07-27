#ifndef GRAPHICAL_VIEW_H
#define GRAPHICAL_VIEW_H

#include "render_view.hpp"
#include <memory>
// #include <X11/Xlib.h>

class GraphicalView : public ViewChild {
    // Display *d;
    // Window w;

    void draw() override;
    void notify() override;
public:
    GraphicalView(std::shared_ptr<Board> board) : ViewChild(board) {
        board->attach(std::shared_ptr<Observer>(this));
    };
};

#endif
