#ifndef TEXT_VIEW_H
#define TEXT_VIEW_H

#include "render_view.hpp"
#include <memory>

class TextView : public ViewChild {
public:
    void draw() override;
    void notify() override;
    TextView(std::shared_ptr<Board> board) : ViewChild(board) {};
};

#endif
