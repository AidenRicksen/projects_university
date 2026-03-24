#ifndef TD_BLOCK_H

#define TD_BLOCK_H



#include <FL/Fl_Box.H>

#include <FL/fl_draw.H>



namespace td {



class Block : public Fl_Box {

public:

	//makes a cell with a neutral background and centered bold label by default

    Block(int x, int y, int w, int h)

    : Fl_Box(x, y, w, h) {

        box(FL_FLAT_BOX);

        color(fl_rgb_color(230,230,230));

        labelsize(16);

        labelfont(FL_HELVETICA_BOLD);

        align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE);

    }



    //updates the cell background color, redraws and does the same for the symbol

    void setColor(Fl_Color c)     { color(c); redraw(); }

    void setSymbol(const char* s) { label(s); redraw(); }

};



}

#endif



