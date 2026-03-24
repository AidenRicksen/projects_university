

#ifndef TOWER_H

#define TOWER_H



#include "Grid.h"

#include <vector>



namespace td {



class Enemy;



class Tower {

public:

    Tower(const Position& p, int dmg = 1, int rng = 2); //Tower attributes

    const Position& getPos() const; //tower position

    void attack(std::vector<Enemy>& enemies) const; //Attack enemy function of the tower



private:

    Position pos;

    int damage;

    int range;

};



}



#endif



