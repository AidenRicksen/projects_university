

#include <iostream>

#include <FL/Fl.H>

#include "Game.h"

#include "fltk/Gamewindow.h"



using namespace td;

//main.cpp:

// - Sets up board dimensions, creates the Game logic and FLTK window,

// - connects them, renders the initial state, and starts the GUI event loop.



int main() {





    const int ROWS = 20;

    const int COLS = 20;

    const int CELL = 28;



    Game game;



    int winW = 20 + COLS * CELL + 200; //grid + space for the buttons and summaries

    int winH = 20 + ROWS * CELL + 40; // grid + extra space on the top and bottom





    Gamewindow win(winW, winH, ROWS, COLS, CELL, &game);

    game.attachWindow(&win);



    win.show();



    game.renderState();





    return Fl::run();

}



