# Pacman_cpp
This is Pacman written in C++.

# Pacman Manual

## Contents

* Interface
* PACMAN Handling
* Ghost Mode Change
* Win & Lose Condition

---

## Interface

### Overview

* **Screens**: Start Screen, Game Screen, Win Screen, Lose Screen
* **Maze**: 8 × 10 matrix
* **Core Elements**: PACMAN, 4 Ghosts, Maze, 2 Types of Dots
* **Additional Features**:

  * Ghost Room
  * Scoreboard
  * Timer (seconds)

### Screenshots

1. **Start Screen**
2. **Game Screen**
3. **Win Screen**
4. **Lose Screen**

---

## PACMAN Handling

* **Movement**: Use the arrow keys (↑ ↓ ← →) to move PACMAN in the corresponding direction.
* **Movement Rules**:

  * PACMAN moves at a constant speed.
  * If PACMAN encounters a wall, it stops immediately.
  * While moving between walls, pressing a perpendicular direction key will cause PACMAN to stop (safety feature).

---

## Ghost Mode Change

* A mode window displays each Ghost’s current state:

  * **Frightened**
  * **Eaten**
  * Other states visualized by color.
* **Chase** and **Scatter** modes are distinguished by logic, not color.

---

## Ghost Mode Specification

### Frightened Mode

* Ghosts slow down.
* Ghosts move in the opposite direction of PACMAN.
* Visualized in **purple**.

### Ready Mode

* Activated when all Ghosts have been eaten.
* When PACMAN eats a Ghost, that Ghost respawns in the Ghost Home.
* After a set time, Ghosts exit the home and re-enter the maze.
* Visualized in **white**.

---

## Win & Lose Condition

### Win Condition

* Eat all points (both small and large) within the maze.

  * **Small Point**: 10 points
  * **Large Point**: 30 points
* Extra score for hunting Ghosts during Frightened mode:

  * 50 × (ghost-hunt count)
  * e.g., 50 points for the first hunting, 100 for the second, etc.

### Lose Condition

* Game over after losing all 5 lives.
* Lives decrease when PACMAN is caught by Ghosts in **Chase** or **Scatter** mode.
* Remaining lives are shown by PACMAN icons at the bottom of the screen.

