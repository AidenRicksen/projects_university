#include "Enemy.h"

#include "Tower.h"

#include "Castle.h"

#include "Grid.h"



namespace td {



Enemy::Enemy(Position startPos, int hp)

    : pos(startPos), health(hp) {}



const Position& Enemy::getPos() const {

    return pos;

}



bool Enemy::isDead() const {

    return health <= 0;

}



int Enemy::getHealth() const {

    return health;

}



void Enemy::takeHit(int dmg) {

    health -= dmg;

}



bool Enemy::reachedCastle(const Position& castlePos) const {

    return pos.row == castlePos.row && pos.col == castlePos.col;

}



Position Enemy::chooseStepToward(const Position& target,

                                 const Grid& grid,

                                 const std::vector<Enemy>& enemies,

                                 const std::vector<Tower>& towers,

                                 const Castle& castle) const

{

    //initialize the movements then first try straight down, then down-left, and then down-right

    Position down      = { pos.row + 1, pos.col     };

    Position downLeft  = { pos.row + 1, pos.col - 1 };

    Position downRight = { pos.row + 1, pos.col + 1 };



    if (grid.inBounds(down) &&

        grid.isEmpty(down, enemies, towers, castle)) {

        return down;

    }

    if (grid.inBounds(downLeft) &&

        grid.isEmpty(downLeft, enemies, towers, castle)) {

        return downLeft;

    }

    if (grid.inBounds(downRight) &&

        grid.isEmpty(downRight, enemies, towers, castle)) {

        return downRight;

    }



    return pos;

}



void Enemy::update(const Position& castlePos,

                   const Grid& grid,

                   const std::vector<Enemy>& enemies,

                   const std::vector<Tower>& towers,

                   const Castle& castle)

{

    if (isDead()) return;



    if (reachedCastle(castlePos)) {

        return;

    }



    Position next = chooseStepToward(castlePos, grid, enemies, towers, castle);

    pos = next;

}



}

