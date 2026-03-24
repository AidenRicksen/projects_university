



#include "AI.h"

#include "Enemy.h"

#include "Tower.h"

#include "Game.h"

#include <cstdlib>

#include <cmath>



namespace td {



Position AIController::chooseSpawnPos( //choosing the spawn positions by using a heatmap

    const Grid& grid,

    const std::vector<Tower>& towers,

    const std::vector<Enemy>& enemies

) const

{



    const int cols = grid.getCols();

    const int topRow = 0;



    // equal score for every column

    std::vector<double> score(cols, 1.0);



    //penalizes columns near towers (distance-based heatmap)

    for (const Tower& t : towers) {

        int tc = t.getPos().col;



        for (int c = 0; c < cols; ++c) {

            int dist = std::abs(c - tc);



            double penalty = 0.0;

            if (dist == 0)      penalty = 0.8;

            else if (dist == 1) penalty = 0.5;

            else if (dist == 2) penalty = 0.3;

            else if (dist == 3) penalty = 0.2;





            score[c] *= (1.0 - penalty);

        }

    }



    // removes columns whose spawn cell is blocked by an enemy

    for (int c = 0; c < cols; ++c) {

        bool blocked = false;

        for (const Enemy& e : enemies) {

            if (!e.isDead() &&

                e.getPos().row == topRow &&

                e.getPos().col == c) {

                blocked = true;

                break;

            }

        }

        if (blocked) {

            score[c] = 0.0;

        }

    }



    // to make sure there is at least one valid column

    double sum = 0.0;

    for (double s : score) sum += s;



    if (sum <= 0.0) {

        // fall back: choose any column whose spawn cell is not blocked

        // if everything is blocked, just pick a random column

        std::vector<int> freeCols;

        for (int c = 0; c < cols; ++c) {

            bool blocked = false;

            for (const Enemy& e : enemies) {

                if (!e.isDead() &&

                    e.getPos().row == topRow &&

                    e.getPos().col == c) {

                    blocked = true;

                    break;

                }

            }

            if (!blocked) {

                freeCols.push_back(c);

            }

        }



        if (!freeCols.empty()) {

            int idx = std::rand() % freeCols.size();

            return Position{ topRow, freeCols[idx] };

        } else {

            int randCol = std::rand() % cols;

            return Position{ topRow, randCol };

        }

    }



    // normalize scores into probabilities

    for (double &s : score) {

        s /= sum;

        s = std::max(s, 1e-6);

    }



    // randomly sample a column from the distribution

    double r = std::rand() / static_cast<double>(RAND_MAX);

    double cumulative = 0.0;

    int chosenCol = cols - 1;



    for (int c = 0; c < cols; ++c) {

        cumulative += score[c];

        if (r <= cumulative) {

            chosenCol = c;

            break;

        }

    }



    return Position{ topRow, chosenCol };

}









Enemy AIController::createEnemy(

    const Position& spawnPos,

    int baseEnemyHealth

) const {

    return Enemy(spawnPos, baseEnemyHealth);

}



int AIController::updateDifficultyAfterWave(int waveNumber,

                                            int waveScore,

                                            int currentBaseEnemyHealth) const

{

    const int POINTS_PER_KILL = 10;

    const int maxScoreThisWave =

        Game::ENEMIES_PER_WAVE * POINTS_PER_KILL;



    //performance of the player

    double performance = 0.0;

    if (maxScoreThisWave > 0) {

        performance = static_cast<double>(waveScore) / maxScoreThisWave;

    }



    // Decide how much to scale enemy HP based on performance

    double factor;

    if (performance >= 0.8) {

        factor = 1.3;

    } else if (performance >= 0.5) {

        factor = 1.1;

    } else if (performance >= 0.3) {

        factor = 1.0;

    } else {

        factor = 0.9;

    }



    int newHealth =

        static_cast<int>(std::round(currentBaseEnemyHealth * factor));



    // keeps enemy HP within a normal range

    const int MIN_ENEMY_HEALTH = 1;

    const int MAX_ENEMY_HEALTH = 10;



    newHealth = std::max(MIN_ENEMY_HEALTH,

                         std::min(MAX_ENEMY_HEALTH, newHealth));



    return newHealth;

}





}







