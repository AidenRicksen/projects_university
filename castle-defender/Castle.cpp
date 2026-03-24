#include "Castle.h"



namespace td {



Castle::Castle(const Position& p, int hp)

    : pos(p), health(hp) {}



const Position& Castle::getPos() const { return pos; }

int Castle::getHealth() const { return health; }



bool Castle::isDestroyed() const { return health <= 0; }



void Castle::takeDamage(int dmg) {

    health -= dmg;

    if (health < 0) health = 0;

}



}







