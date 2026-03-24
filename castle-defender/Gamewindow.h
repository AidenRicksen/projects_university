

#ifndef GAMEWINDOW_H_

#define GAMEWINDOW_H_





#include <FL/Fl_Window.H>

#include <FL/Fl_Button.H>

#include <FL/Fl_Box.H>



#include "Gridview.h"



#include <vector>

#include <string>



namespace td {



class Enemy;

class Tower;

class Castle;

class Game;



// FLTK window that shows the grid, handles mouse clicks, "Next turn" button and a "restart" button.

class Gamewindow : public Fl_Window {

public:

    Gamewindow(int W, int H, int rows, int cols, int cellSize, Game* game);



    void syncFrom(const std::vector<Enemy>& enemies,

                  const std::vector<Tower>& towers,

                  const Castle&              castle);



    void updateSummary(const std::string& txt);

    void setGameOverUI(bool over);



    static void nextTurn_cb(Fl_Widget*, void* userdata);

    void        nextTurn();



    static void restart_cb(Fl_Widget*, void* userdata);

    void        restart();



private:

    int rows;

    int cols;

//pointers to GUI and game model. All start as nullptr and are set in the gamewindow constructor

    GridView*  grid       { nullptr };

    Fl_Button* nextTurnBtn{ nullptr };

    Fl_Box*    hudBox     { nullptr };

    Fl_Button* restartBtn { nullptr };

    Game*      game       { nullptr };

};

}

#endif



