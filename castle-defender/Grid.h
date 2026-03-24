#ifndef GRID_H

#define GRID_H



#include <vector>



namespace td {



struct Position {

    int row;

    int col;

};



class Enemy;

class Tower;

class Castle;



class Grid { //getting everything the grid needs: getter functions for the rows and columns, bools for if a position is in the grid and if it is empty or used

public:

    Grid(int rows = 20, int cols = 20);



    int getRows() const;

    int getCols() const;

    bool inBounds(const Position& p) const;



    bool isEmpty(const Position& p,

                 const std::vector<Enemy>& enemies,

                 const std::vector<Tower>& towers,

                 const Castle& castle) const;





private:

    int rows;

    int cols;

};



}



#endif





