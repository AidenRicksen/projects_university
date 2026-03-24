

#ifndef GRIDVIEW_H_

#define GRIDVIEW_H_



#include <FL/Fl_Widget.H>

#include <FL/fl_draw.H>

#include <string>

#include <vector>

#include <functional>



class GridView : public Fl_Widget {

public:



    GridView(int x, int y, int rows, int cols, int cellSize);



    void clearAll();

    void paint(int row, int col, const char* symbol, Fl_Color color);

    bool pixelToCell(int px, int py, int& row, int& col) const;

    void setClickHandler(std::function<void(int,int)> handler);



private:

    int rows_;

    int cols_;

    int cell_;



    struct Cell {

        std::string symbol;

        Fl_Color color{FL_WHITE};

    };



    std::vector<Cell> cells_;

    std::function<void(int,int)> clickHandler_;



    void draw() override;

    int handle(int event) override;

};



#endif











