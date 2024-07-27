#ifndef RENDER_VIEW_H
#define RENDER_VIEW_H

#include "board.hpp"
class Subject {

};

class Observer {

};

class View {
public:
    Board *board;
    virtual void draw();
};

#endif
