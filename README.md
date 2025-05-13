# Pacman_cpp
This is Pacman written in C++.
Explanation in Korean is available via:
[Pacman_Manual.pdf](https://github.com/user-attachments/files/20186591/Pacman_Manual.pdf)

# Pacman Manual

## Contents

* Interface
* Pacman Handling
* Ghost Mode Change
* Ghost Mode Specification
* Win & Lose Condition

---

## Interface

### Overview

* **Screens**: Start Screen, Game Screen, Win Screen, Lose Screen
* **Maze**: 8 × 10 matrix
* **Core Elements**: Pacman, 4 Ghosts, Maze, 2 Types of Dots
* **Additional Features**:

  * Ghost Room
  * Scoreboard
  * Timer (seconds)

---

## Pacman Handling

* **Movement**: Use the arrow keys (↑ ↓ ← →) to move Pacman in the corresponding direction.
* **Movement Rules**:

  * Pacman moves at a constant speed.
  * If Pacman encounters a wall, it stops immediately.
  * While moving between walls, pressing a perpendicular direction key will cause Pacman to stop (safety feature).

---

## Ghost Mode Change

* A mode window displays each Ghost’s current state:

  * **Frightened**
  * **Eaten**
  * **Chase**
  * **Scatter**
  * These states are also visualized by the ghosts' color. **Chase** and **Scatter** are distinguished by logic, not color.

---

## Ghost Mode Specification

### Frightened Mode

* Ghosts slow down.
* Ghosts move in the opposite direction of Pacman.
* Visualized in **purple**.

### Ready Mode

* Activated when all Ghosts have been eaten.
* When Pacman eats a Ghost, that Ghost respawns in the Ghost Home.
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
* Lives decrease when Pacman is caught by Ghosts in **Chase** or **Scatter** mode.
* Remaining lives are shown by Pacman icons at the bottom of the screen.

