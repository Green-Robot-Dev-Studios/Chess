#ifndef RENDER_VIEW_H
#define RENDER_VIEW_H

#include "board.hpp"
class Subject {

};

class Observer {

};

class ViewChild {
public:
    Board *board;
    virtual void draw();
};

#endif
