



#include "Gridview.h"

#include <FL/Fl.H>



GridView::GridView(int x, int y, int rows, int cols, int cellSize)

    : Fl_Widget(x, y, cols * cellSize, rows * cellSize),

      rows_(rows),

      cols_(cols),

      cell_(cellSize),

      cells_(rows * cols)

{

}



// Clear all cells to default color & no symbol

void GridView::clearAll() {

    for (auto& c : cells_) {

        c.symbol.clear();

        c.color = FL_WHITE;

    }

    redraw();

}



// Paint a  cell

void GridView::paint(int row, int col, const char* symbol, Fl_Color color) {

    if (row < 0 || row >= rows_ || col < 0 || col >= cols_) return;

    Cell& cell = cells_[row * cols_ + col];

    cell.symbol = symbol ? symbol : "";

    cell.color  = color;

    redraw();

}



// convert (px, py) to (row, col)

bool GridView::pixelToCell(int px, int py, int& row, int& col) const {

    int localX = px - x();

    int localY = py - y();

    if (localX < 0 || localY < 0) return false;



    col = localX / cell_;

    row = localY / cell_;



    if (row < 0 || row >= rows_ || col < 0 || col >= cols_) return false;

    return true;

}



void GridView::setClickHandler(std::function<void(int,int)> handler) {

    clickHandler_ = std::move(handler);

}



// drawing of the grid

void GridView::draw() {

    fl_push_clip(x(), y(), w(), h());



    for (int r = 0; r < rows_; ++r) {

        for (int c = 0; c < cols_; ++c) {

            int px = x() + c * cell_;

            int py = y() + r * cell_;



            const Cell& cell = cells_[r * cols_ + c];



            // Background

            Fl_Color bg = cell.color;

            if (bg == 0) bg = fl_rgb_color(240, 240, 240);

            fl_draw_box(FL_FLAT_BOX, px, py, cell_, cell_, bg);



            // Grid border

            fl_color(FL_BLACK);

            fl_rect(px, py, cell_, cell_);



            // Symbol in the center

            if (!cell.symbol.empty()) {

                fl_color(FL_BLACK);

                fl_font(FL_HELVETICA, 14);



                int tw = 0, th = 0;

                fl_measure(cell.symbol.c_str(), tw, th, 0);



                int tx = px + (cell_ - tw) / 2;

                int ty = py + (cell_ + th) / 2 - 2;



                fl_draw(cell.symbol.c_str(), tx, ty);

            }

        }

    }



    fl_pop_clip();

}



// handle mouse clicks

int GridView::handle(int event) {

    switch (event) {

    case FL_PUSH: {

        if (!clickHandler_) return 1;



        int mx = Fl::event_x();

        int my = Fl::event_y();

        int r, c;

        if (pixelToCell(mx, my, r, c)) {

            clickHandler_(r, c);

        }

        return 1;

    }

    default:

        return Fl_Widget::handle(event);

    }

}





