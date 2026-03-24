

#ifndef AI_H

#define AI_H



#include <vector>

#include "Grid.h"



namespace td {



class Enemy;

class Tower;



class AIController {

public: //All of the AI functions (spawning and difficulty)

    AIController() = default;





    Position chooseSpawnPos(

        const Grid& grid,

        const std::vector<Tower>& towers,

        const std::vector<Enemy>& enemies

    ) const;



    Enemy createEnemy(

        const Position& spawnPos,

        int baseEnemyHealth

    ) const;



    int updateDifficultyAfterWave(

        int waveNumber,

        int waveScore,

        int currentBaseEnemyHealth

    ) const;





};



}



#endif





