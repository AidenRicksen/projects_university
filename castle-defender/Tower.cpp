

#include "Tower.h"

#include "Enemy.h"

#include <iostream>

#include <cmath>



namespace td {



Tower::Tower(const Position& p, int dmg, int rng)

    : pos(p), damage(dmg), range(rng) {}



const Position& Tower::getPos() const { return pos; }



static int distance(const Position& a, const Position& b) // Function for the Chebyshev distance so that it can also attack diagonally

{

    int dr = std::abs(a.row - b.row);

    int dc = std::abs(a.col - b.col);

    return std::max(dr, dc);

}





void Tower::attack(std::vector<Enemy>& enemies) const { //Tower attack if the enemy is in range

    for (Enemy& e : enemies) {

        if (e.isDead()) continue;

        if (distance(pos, e.getPos()) <= range) {

            e.takeHit(damage);

            std::cout << "Tower hit enemy! Enemy HP now: "

                      << e.getHealth() << "\n";

            break;

        }

    }

}



}







