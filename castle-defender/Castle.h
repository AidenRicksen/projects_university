#ifndef CASTLE_H

#define CASTLE_H



#include "Grid.h"



namespace td {



class Castle {

public:

    Castle(const Position& p, int hp);



    const Position& getPos() const;

    int  getHealth() const;

    bool isDestroyed() const;



    void takeDamage(int dmg);



private:

    Position pos;

    int health;

};



}



#endif



