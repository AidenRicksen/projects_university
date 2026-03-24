# ð° Castle Defender

> A tower-defense game with adaptive enemy AI, built in C++17 with an FLTK GUI.
> University project â Programming with C/C++, Fall 2025â2026 (Tilburg University)

---

## Overview

Castle Defender is a turn-based tower defense game played on a 20Ã20 grid. Enemies spawn at the top row and march toward your castle at the bottom. You place up to five defensive towers before the first wave and then advance through five waves of increasingly difficult enemies. The enemy AI adapts its spawn strategy based on your tower placement and scales difficulty based on your performance each wave.

---

## Features

- **Turn-based gameplay** â advance the game one tick at a time via a "Next Turn" button
- **Tower placement** â click on the grid to place up to 5 towers before the first wave begins
- **Adaptive AI** â enemies use a heatmap to prefer lanes not covered by towers, and difficulty scales dynamically after each wave
- **FLTK GUI** â live grid rendering with color-coded towers (green), enemies (red), and the castle (blue), plus a side panel showing wave, score, castle HP, kills, and breach count
- **Clean MVC architecture** â game logic (`Game`, `Grid`, `Enemy`, `Tower`, `Castle`, `AIController`) is fully separated from the view (`Gamewindow`, `GridView`)
- **Restart** â full game reset without restarting the application

---

## Architecture

```
CastleDefender/
âââ main.cpp            # Entry point â sets up Game + Gamewindow, starts FLTK loop
âââ Game.h / .cpp       # Core game loop: spawn, move, attack, resolve
âââ Grid.h / .cpp       # 20Ã20 grid with bounds checking and cell queries
âââ Enemy.h / .cpp      # Enemy entity: position, health, movement logic
âââ Tower.h / .cpp      # Tower entity: position, range, attack logic
âââ Castle.h / .cpp     # Castle entity: position and HP tracking
âââ Ai.h / Ai.cpp       # AIController: heatmap-based spawning + adaptive difficulty
âââ Block.h             # Shared Position struct and block types
âââ Gamewindow.h / .cpp # FLTK window, input handling, side panel
âââ Gridview.h / .cpp   # FLTK widget for rendering the grid
```

**Game loop per tick:**
1. Spawn an enemy (if quota for this wave not yet met) â AI chooses the column
2. Move all enemies one step toward the castle
3. Each tower attacks the first enemy in range (Manhattan distance â¤ 2)
4. Resolve deaths (tower kills â +10 pts) and castle breaches (â10 HP)
5. End wave if all enemies are spawned and none are alive; update difficulty

---

## Getting Started

### Prerequisites

- C++17 compiler (tested with MinGW g++ 6.3.0 on Windows 10)
- [FLTK 1.3.5](https://www.fltk.org/) installed and `fltk-config` available on your PATH

### Build

```bash
g++ -std=c++17 main.cpp Game.cpp Gamewindow.cpp \
    Grid.cpp Gridview.cpp Enemy.cpp Tower.cpp Castle.cpp Ai.cpp \
    `fltk-config --cxxflags --ldflags` \
    -o CastleDefender
```

> If `fltk-config` is not available, add the FLTK include and library paths manually.

### Run

```bash
./CastleDefender
```

---

## How to Play

1. The game starts with an empty 20Ã20 grid and your castle (blue) at the bottom center.
2. **Place towers** by clicking any valid cell (not the top 2 rows, not the castle cell). You may place up to 5.
3. Click **"Next Turn"** to advance the game. Each turn spawns, moves, and resolves one tick.
4. Survive **5 waves** of 10 enemies each. Your score is based on tower kills (10 pts each).
5. The winner is determined by the castle's remaining HP at the end of wave 5.
6. Click **"Restart"** to start a fresh game at any time.

---

## AI Design

The `AIController` uses two mechanisms:

**Heatmap-based spawning** â before each spawn, a score is computed for every column of the top row. Columns close to towers receive a penalty (scaled by distance). Columns already occupied by an enemy score 0. The AI samples a column weighted by these scores, so enemies prefer gaps in your defense without being fully deterministic.

**Adaptive difficulty** â after each wave, the AI compares your wave score against the theoretical maximum (enemies Ã 10 pts). If you performed strongly, base enemy health increases by a factor of 1.3; average performance keeps it the same; struggling reduces it slightly (Ã0.9), keeping the game fair.

---

## Technical Notes

- Tested on **Windows 10 (22H2)** with **MinGW g++ 6.3.0** and **FLTK 1.3.5**
- Model and view are fully decoupled; all GUI updates flow through `Game::renderState()` â `Gamewindow::syncFrom()`
- The `reset()` function recreates all state from scratch (same behavior as the constructor), ensuring a clean restart

---

*Fall 2025 â Programming with C/C++ â Tilburg University*
