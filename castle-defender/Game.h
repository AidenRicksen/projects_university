

#ifndef GAME_H

#define GAME_H



#include <vector>

#include "Grid.h"

#include "Castle.h"

#include "Enemy.h"

#include "Tower.h"

#include "AI.h"



namespace td {

class Gamewindow;



class Game {

public:

    Game();

    //functions for the GUI and the loop of the game

    void attachWindow(Gamewindow* w) { gw = w; }

    void renderState() const;

    void run();

    void tick();

    bool tryPlaceTowerAt(const Position& p);

    bool isOver() const { return gameOver; }

    void reset();



    const std::vector<Enemy>& getEnemies() const { return enemies; }

    const std::vector<Tower>& getTowers() const { return towers; }

    const Castle&            getCastle()  const { return castle; }







private:

    Grid grid;

    Castle castle;

    std::vector<Tower> towers;

    std::vector<Enemy> enemies;

    AIController ai;



    Gamewindow* gw = nullptr;



    // Wave / difficulty / score tracking

    int currentWave;

    int enemiesSpawnedThisWave;

    int baseEnemyHealth;

    int playerScore;

    int waveScore;

    int enemiesDestroyedTotal;

    int enemiesBreachedTotal;

    bool gameOver;

    bool allWavesFinished() const;

    bool noEnemiesAlive() const;



public:

    static constexpr int TOTAL_WAVES      = 5;

    static constexpr int ENEMIES_PER_WAVE = 10;



private:

    //turn-by-turn helper functions

    void spawnIfNeeded();

    void towersAttack();

    void enemiesAct();

    void resolveCastleHitsAndDeaths();

    bool waveFinished() const;

    void endWaveIfNeeded();

    bool hasBreachedCastle(const Position& enemyPos) const;



    //tower placement helpers

    bool positionOccupiedByTower(const Position& p) const;

    bool towerPlacementAllowed(const Position& p) const;

};





}



#endif



