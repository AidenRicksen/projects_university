# Castle Defender

A turn-based tower defense game developed in C++17 as part of the Programming with C/C++ course at Tilburg University (Fall 2025/2026).

---

## Overview

Castle Defender is a grid-based tower defense game with a graphical user interface built using the FLTK library. The player strategically places towers on a grid to defend a castle against incoming waves of enemies. The game features an adaptive AI system that adjusts enemy behaviour and difficulty based on player performance.

---

## Features

- **Grid-based gameplay** — Players place towers on a tile grid to block and damage approaching enemies.
- **Adaptive enemy AI** — Enemies select spawn positions using a heatmap that tracks where players are least defended, increasing strategic challenge over time.
- **Dynamic difficulty scaling** — Enemy strength and wave composition scale based on the player's performance in previous rounds.
- **Wave-based progression** — Each wave introduces new enemies, requiring players to continually adapt their tower placement strategy.
- **MVC architecture** — Game logic, data, and GUI are cleanly separated using a Model-View-Controller pattern, making the codebase maintainable and extensible.

---

## Project Structure

```
castle-defender/
├── main.cpp                       # Entry point
├── Game.h / Game.cpp              # Core game loop and state management
├── Gamewindow.h / Gamewindow.cpp  # Main FLTK application window
├── Grid.h / Grid.cpp              # Grid data model
├── GridView.h / GridView.cpp      # Grid rendering (View layer)
├── Block.h                        # Individual grid cell representation
├── Tower.h / Tower.cpp            # Tower logic and attributes
├── Enemy.h / Enemy.cpp            # Enemy logic and movement
├── Castle.h / Castle.cpp          # Castle health and state
├── Ai.h / Ai.cpp                  # Enemy AI and heatmap logic
└── README.md
```

---

## Requirements

- C++17 or later
- [FLTK](https://www.fltk.org/) (Fast Light Toolkit) — graphical user interface library

---

## Building

1. Install FLTK. On most Linux systems:
   ```bash
   sudo apt install libfltk1.3-dev
   ```
   On macOS with Homebrew:
   ```bash
   brew install fltk
   ```

2. Compile the project using g++:
   ```bash
   g++ -std=c++17 -o castle_defender main.cpp Game.cpp Gamewindow.cpp Grid.cpp GridView.cpp Tower.cpp Enemy.cpp Castle.cpp Ai.cpp $(fltk-config --cxxflags --ldflags)
   ```

3. Run the executable:
   ```bash
   ./castle_defender
   ```

---

## Architecture

The project follows a Model-View-Controller (MVC) design pattern:

| Layer | Files | Responsibility |
|---|---|---|
| Model | Grid, Block, Tower, Enemy, Castle | Game state and data |
| View | GridView, Gamewindow | Rendering and UI |
| Controller | Game, Ai | Game logic, turn management, AI |

---

## Course

**Programming with C/C++** — Tilburg University, BSc Cognitive Science and Artificial Intelligence, Fall 2025/2026
