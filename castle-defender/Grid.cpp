

#include "Grid.h"

#include "Enemy.h"

#include "Tower.h"

#include "Castle.h"

#include <iostream>

#include <vector>



namespace td {



Grid::Grid(int r, int c) : rows(r), cols(c) {}



int Grid::getRows() const { return rows; }

int Grid::getCols() const { return cols; }



bool Grid::inBounds(const Position& p) const { //checks if the tower is within the grid (especially important in the old code using the console)

    return p.row >= 0 && p.row < rows &&

           p.col >= 0 && p.col < cols;

}





bool Grid::isEmpty(const Position& p, //checks if an enemy or tower is already at a certain place in the grid

                   const std::vector<Enemy>& enemies,

                   const std::vector<Tower>& towers,

                   const Castle& castle) const

{

    if (!inBounds(p)) return false;



    for (const Tower& t : towers) {

        if (t.getPos().row == p.row && t.getPos().col == p.col)

            return false;

    }



    for (const Enemy& e : enemies) {

        if (!e.isDead() &&

            e.getPos().row == p.row && e.getPos().col == p.col)

            return false;

    }



    return true;

}





}











