

#include <iostream>

#include "Gamewindow.h"



#include "../Game.h"

#include "../Enemy.h"

#include "../Tower.h"

#include "../Castle.h"



namespace td {







void Gamewindow::syncFrom(const std::vector<Enemy>& enemies, //takes the position of the castle, towers, and enemies and syncs it to the

                          const std::vector<Tower>& towers, // GUI with a color and symbol

                          const Castle& castle)

{

    if (!grid) return;



    grid->clearAll();



    Position cp = castle.getPos();

    grid->paint(cp.row, cp.col, "ð°", fl_rgb_color(60,120,255));



    for (const Tower& t : towers) {

        Position tp = t.getPos();

        grid->paint(tp.row, tp.col, "ð«", fl_rgb_color(40,170,80));

    }



    for (const Enemy& e : enemies) {

        if (e.isDead()) continue;

        Position ep = e.getPos();

        grid->paint(ep.row, ep.col, "ð¾", fl_rgb_color(220,60,60));

    }



    redraw();

}





void Gamewindow::setGameOverUI(bool over) // creates the game over button that can not be pressed if the game is over

{

    if (over) {

        nextTurnBtn->label("Game Over");

        nextTurnBtn->deactivate();

    } else {

        nextTurnBtn->label("Next Turn");

        nextTurnBtn->activate();

    }

}



void Gamewindow::nextTurn_cb(Fl_Widget*, void* userdata) { //static callback for the next turn button

    auto* gw = static_cast<Gamewindow*>(userdata);

    if (gw) gw->nextTurn();

}



Gamewindow::Gamewindow(int W, int H, //creates the window for the game

                       int rows_, int cols_, int cellSize,

                       Game* g)

    : Fl_Window(W, H, "Castle Defender GUI"),

      rows(rows_), cols(cols_), game(g)

{

    begin();



    grid = new GridView(20, 20, rows, cols, cellSize);



    grid->setClickHandler([this](int r, int c) {

        if (!game) return;

        Position p{r, c};

        if (game->tryPlaceTowerAt(p)) {

            game->renderState();

        }

    });

    //positions and size of the next turn, restart button and the summary

    nextTurnBtn = new Fl_Button(W - 150, 20, 120, 40, "Next Turn");

    nextTurnBtn->callback(nextTurn_cb, this);



    restartBtn = new Fl_Button(W - 150, 70, 120, 40, "Restart");

    restartBtn->callback(restart_cb, this);



    hudBox = new Fl_Box(W - 180, 120, 160, 250, "");

    hudBox->box(FL_FLAT_BOX);

    hudBox->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE | FL_ALIGN_TOP);



    syncFrom(game->getEnemies(), game->getTowers(), game->getCastle());



    end();

    resizable(this);

}



void Gamewindow::restart_cb(Fl_Widget*, void* userdata) //static callback for the restart button

{

    auto* gw = static_cast<Gamewindow*>(userdata);

    if (!gw || !gw->game) return;



    gw->game->reset();



    gw->grid->clearAll();

    gw->syncFrom(gw->game->getEnemies(),

                 gw->game->getTowers(),

                 gw->game->getCastle());

    gw->redraw();

}





void Gamewindow::restart() { //logic for the restart button

    if (!game) return;



    game->reset();

    game->renderState();



    setGameOverUI(false);

}



void Gamewindow::nextTurn() { //next turn for the game loop

    if (!game) return;



    game->tick();

    game->renderState();

    if (game -> isOver() && nextTurnBtn){

    	nextTurnBtn->deactivate();

    	nextTurnBtn->label("Game Over");

    }

}



void Gamewindow::updateSummary(const std::string& text) { //updates the summary on the right side of the gamewindow

    if (!hudBox) return;

    hudBox->copy_label(text.c_str());

    redraw();

}











}





