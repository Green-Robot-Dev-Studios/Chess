#ifndef TEXT_VIEW_H
#define TEXT_VIEW_H

#include "render_view.hpp"

class TextView : public ViewChild {
    void draw() override;
    void notify();
};

#endif
