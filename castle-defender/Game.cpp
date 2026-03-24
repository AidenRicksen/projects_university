

#include "Game.h"

#include <iostream>

#include <sstream>

#include <algorithm>

#include <cstdlib>

#include <ctime>

#include "fltk/Gamewindow.h"







namespace td {



static int countAliveEnemies(const std::vector<td::Enemy>& enemies) { //a count that is used to show in the GUI summary during the game

    int count = 0;                                                    //by checking the vector of enemies and counting which ones are not dead

    for (const td::Enemy& e : enemies) {

        if (!e.isDead()) {

            count++;

        }

    }

    return count;

}





Game::Game() //The constructor of the game where all of the basics are being set

    : grid(20,20),

      castle(Position{19,10}, 100),

      currentWave(1),

      enemiesSpawnedThisWave(0),

      baseEnemyHealth(3),

      playerScore(0),

      waveScore(0),

	  enemiesDestroyedTotal(0),

	  enemiesBreachedTotal(0),

      gameOver(false)

{

    std::srand(static_cast<unsigned>(std::time(nullptr))); //random number seed so that the random functions (like parts in the AI) don't repeat the same pattern



}





bool Game::positionOccupiedByTower(const Position& p) const { //checks is a certain place is already being occopied by a tower

    for (const Tower& t : towers) {

        if (t.getPos().row == p.row &&

            t.getPos().col == p.col) {

            return true;

        }

    }

    return false;

}







bool Game::towerPlacementAllowed(const Position& p) const { //a function that goes through all of the rules to check if the tower can be placed



    if (!grid.inBounds(p)) return false;

    if (p.row < 2) return false;

    Position cpos = castle.getPos();

    if (p.row == cpos.row && p.col == cpos.col) return false;

    if (positionOccupiedByTower(p)) return false;



    return true;

}







void Game::spawnIfNeeded() { //a function to control when new enemies can be spawned

    if (gameOver) return;

    if (currentWave > TOTAL_WAVES) return;

    if (enemiesSpawnedThisWave < ENEMIES_PER_WAVE) {

        Position spawnPos = ai.chooseSpawnPos(grid, towers, enemies);

        Enemy newEnemy = ai.createEnemy(spawnPos, baseEnemyHealth);

        enemies.push_back(newEnemy);

        enemiesSpawnedThisWave++;

    }

}





void Game::towersAttack() { //uses the attack function in the tower files in the game

    for (const Tower& t : towers) {

        t.attack(enemies);

    }

}



void Game::enemiesAct() { //updating the enemy and also including the movement

    for (Enemy& e : enemies) {

        if (!e.isDead()) {

            e.update(

                castle.getPos(),

                grid,

                enemies,

                towers,

                castle

            );

        }

    }

}





void Game::resolveCastleHitsAndDeaths() { //A large function that will do all of the hits and deaths

    const int castleRow = castle.getPos().row;



    int towerKillsThisTick = 0;

    int breachedThisTick   = 0;



    std::vector<Enemy> survivors;

    survivors.reserve(enemies.size());



    for (Enemy &e : enemies) { //going through the enemies and check if it hit the castle row and breached the castle

        const Position &p = e.getPos();



        if (e.isDead()) {

            if (p.row < castleRow) {

                towerKillsThisTick++;

            } else {

                breachedThisTick++;

            }



            continue;

        }



        if (p.row >= castleRow) { //resolving the damage to the castle

            castle.takeDamage(10);

            breachedThisTick++;

        } else {

            survivors.push_back(e);

        }

    }



    enemies.swap(survivors);





    if (towerKillsThisTick > 0) { //updating the summary

        const int pointsPerKill = 10;

        playerScore           += towerKillsThisTick * pointsPerKill;

        waveScore             += towerKillsThisTick * pointsPerKill;

        enemiesDestroyedTotal += towerKillsThisTick;



        std::cout << "Towers killed " << towerKillsThisTick

                  << " enemy(ies) this turn.\n";

    }



    if (breachedThisTick > 0) {

        enemiesBreachedTotal += breachedThisTick;

        std::cout << breachedThisTick

                  << " enemy(ies) reached the castle this turn.\n";

    }

}







//three bools used in functions to go to the next wave or later end the game

bool Game::waveFinished() const {



    return (enemiesSpawnedThisWave >= ENEMIES_PER_WAVE &&

            enemies.empty());

}



bool Game::allWavesFinished() const {

    return currentWave > TOTAL_WAVES;

}



bool Game::noEnemiesAlive() const {

    for (const Enemy& e : enemies) {

        if (!e.isDead()) return false;

    }

    return true;

}





void Game::endWaveIfNeeded() {



	if (!waveFinished()){

		return;

	}



    //Ai adaptive difficulty

    baseEnemyHealth = ai.updateDifficultyAfterWave(

        currentWave,

        waveScore,

        baseEnemyHealth

    );

    //Updating the console

    std::cout << "Wave " << currentWave << " complete.\n";

    std::cout << "Wave score: " << waveScore << "\n";

    std::cout << "Player total score: " << playerScore << "\n";

    std::cout << "Next wave base HP: " << baseEnemyHealth << "\n";



    // Prepare next wave

    currentWave++;

    enemiesSpawnedThisWave = 0;

    waveScore = 0;



}







void Game::renderState() const {

    //Decide winner text

    std::string winnerText = "In progress";

    if (gameOver) {

        if (castle.isDestroyed()) {

            winnerText = "Enemies";

        } else if (allWavesFinished() && noEnemiesAlive()) {

            winnerText = "Player";

        } else {

            winnerText = "Game ended early";

        }

    }



    //Console HUD

    std::cout << "\n===== GAME STATE =====\n";

    std::cout << "Wave: " << currentWave << " / " << TOTAL_WAVES

              << "  |  Spawned this wave: " << enemiesSpawnedThisWave

              << " / " << ENEMIES_PER_WAVE << "\n";

    std::cout << "Wave score (this wave): " << waveScore << "\n";

    std::cout << "Total score: " << playerScore << "\n";

    std::cout << "Castle HP: " << castle.getHealth() << "\n";

    std::cout << "Enemies alive: " << countAliveEnemies(enemies) << "\n";

    std::cout << "Enemies killed (total): " << enemiesDestroyedTotal << "\n";

    std::cout << "Enemies breached (reached castle): " << enemiesBreachedTotal << "\n";

    std::cout << "Winner: " << winnerText << "\n\n";



    //GUI HUD

    if (gw) {

        std::ostringstream oss;

        oss << "Wave " << currentWave << " / " << TOTAL_WAVES << "\n"

            << "Spawned: " << enemiesSpawnedThisWave << " / " << ENEMIES_PER_WAVE << "\n"

            << "Wave score: " << waveScore << "\n"

            << "Total score: " << playerScore << "\n"

            << "Castle HP: " << castle.getHealth() << "\n"

            << "Enemies alive: " << countAliveEnemies(enemies) << "\n"

            << "Kills: " << enemiesDestroyedTotal << "\n"

            << "Enemies Breached: " << enemiesBreachedTotal << "\n"

            << "Winner: " << winnerText << "\n";



        const std::string summaryText = oss.str();



        gw->updateSummary(summaryText);

        gw->syncFrom(enemies, towers, castle);

        gw->setGameOverUI(gameOver);

        gw->redraw();

    } else



    std::cout << "=======================\n";

}







void Game::tick() {

    if (gameOver) return;



    //Including all the steps that need to take place every tick

    enemiesAct();                    // Movement of the enemies + updating the enemies

    spawnIfNeeded();                 // AI spawns 1 enemy for this wave (if any left)

    towersAttack();                  // Towers shoot

    resolveCastleHitsAndDeaths();    // Castle takes damage, dead enemies removed

    endWaveIfNeeded();               // Check if we finished a wave + scale difficulty



    // Update gameOver

    if (castle.isDestroyed()) {

        gameOver = true;

    }

    if (allWavesFinished() && noEnemiesAlive()) {

        gameOver = true;

    }

}





void Game::run() {

    std::cout << "\nStarting game...\n";



    for (int turn = 0; turn < 300; ++turn) {

        std::cout << "\n--- TURN " << turn << " ---\n";

        tick();

        if (gameOver) break;

    }



    std::string winner;

    if (castle.isDestroyed()) {

        winner = "Enemies";

    } else if (allWavesFinished() && noEnemiesAlive()) {

        winner = "Player";

    } else {

        winner = "Game ended early (debug stop)";

    }





    std::cout << "\nGAME OVER\n";

    std::cout << "Player Score: "      << playerScore << "\n";

    std::cout << "Enemies Destroyed: " << enemiesDestroyedTotal << "\n";

    std::cout << "Castle Health: "     << castle.getHealth() << "\n";

    std::cout << "Winner: "            << winner << "\n";

}



bool Game::tryPlaceTowerAt(const Position& p) { //function for the placement of the towers and their rules (in the grid, not in top 2 rows, max 5 towers)



    if (!grid.inBounds(p)) return false;



    if (p.row == 0 || p.row == 1) return false;

    if (p.row == castle.getPos().row && p.col == castle.getPos().col) return false;



    if (towers.size() >= 5) {

        std::cout << "Max number of towers reached.\n";

        return false;

    }



    for (const Tower& t : towers) {

        if (t.getPos().row == p.row && t.getPos().col == p.col) {

            return false;

        }

    }



    towers.emplace_back(p);



    std::cout << "Placed tower at (" << p.row << "," << p.col << ")\n";

    return true;

}



void Game::reset() { //function to reset everything, used in the GUI button



    towers.clear();

    enemies.clear();



    Position cpos = castle.getPos();

    castle = Castle(cpos, 100);



    currentWave             = 1;

    enemiesSpawnedThisWave  = 0;

    baseEnemyHealth         = 3;

    waveScore               = 0;

    playerScore             = 0;

    enemiesDestroyedTotal   = 0;

    enemiesBreachedTotal    = 0;

    gameOver                = false;

}







}







