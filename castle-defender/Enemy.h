#ifndef ENEMY_H

#define ENEMY_H



#include <vector>

#include "Grid.h"



namespace td {



class Tower;

class Castle;

class Grid;



class Enemy {

public:

    Enemy(Position startPos, int hp);



    const Position& getPos() const;

    bool isDead() const;

    int  getHealth() const;



    void takeHit(int dmg);

    bool reachedCastle(const Position& castlePos) const;



    Position chooseStepToward(const Position& target,

                              const Grid& grid,

                              const std::vector<Enemy>& enemies,

                              const std::vector<Tower>& towers,

                              const Castle& castle) const;



    void update(const Position& castlePos,

                const Grid& grid,

                const std::vector<Enemy>& enemies,

                const std::vector<Tower>& towers,

                const Castle& castle);



private:

    Position pos;

    int health;

};



}



#endif



