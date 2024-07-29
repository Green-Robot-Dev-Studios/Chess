#ifndef TEXT_VIEW_H
#define TEXT_VIEW_H

#include "render_view.hpp"
#include <memory>

class TextView : public ViewChild {
    void draw() override;
    void notify() override;
public:
    TextView(std::shared_ptr<Board> board) : ViewChild(board) {};
};

#endif
