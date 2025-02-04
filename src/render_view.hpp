#ifndef RENDER_VIEW_H
#define RENDER_VIEW_H

#include "board.hpp"
#include "observer.hpp"
#include <memory>

class ViewChild : public Observer {
protected:
    std::shared_ptr<Board> board;
public:
    ViewChild(std::shared_ptr<Board> board) : board{board} {};
    virtual ~ViewChild() {}
    virtual void draw() = 0;
};

#endif
