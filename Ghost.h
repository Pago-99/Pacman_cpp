#pragma once
#include "Character.h"
#include <cmath>

extern int elapsedTime;

class Ghost : public Character {
private:
    enum State { Chase, Scatter, Frightened, Eaten };
    State ghostState;
    int ghostName;
    int targetX, targetY; 
    float color[3];
    int force; // 0 = ignore walls, 1 = normal movement
    
    int currentDirection; // Store current direction (0:stop, 1:up, 2:down, 3:left, 4:right)
    int lastDirection; // Previous direction
    int reentryTime;

    void updateColor() {
        switch (ghostState) {
        case Chase:
        case Scatter:
            if (ghostName == 1) { color[0] = 1.0f; color[1] = 0.0f; color[2] = 0.0f; }      // Blinky: Red
            else if (ghostName == 2) { color[0] = 1.0f; color[1] = 0.8f; color[2] = 0.8f; } // Pinky: Light Pink
            else if (ghostName == 3) { color[0] = 0.5f; color[1] = 1.0f; color[2] = 1.0f; } // Inky: Light Blue
            else if (ghostName == 4) { color[0] = 1.0f; color[1] = 0.5f; color[2] = 0.0f; } // Clyde: Orange
            break;
        case Frightened:
            color[0] = 0.5f; color[1] = 0.0f; color[2] = 0.5f;
            break;
        case Eaten:
            color[0] = 1.0f; color[1] = 1.0f; color[2] = 1.0f;
            break;
        }
    }

    bool isCellCenter() {
        float devX = (position.first + size - spacing/2.0f) / spacing;
        float devY = (position.second + size - spacing/2.0f) / spacing;
        float eps = 0.0001f;
        return (fabs(devX - round(devX)) < eps && fabs(devY - round(devY)) < eps);
    }

    void alignToCell() {
        float devX = round((position.first + size - spacing/2.0f) / spacing);
        float devY = round((position.second + size - spacing/2.0f) / spacing);
        position.first = devX * spacing - size + spacing/2.0f;
        position.second = devY * spacing - size + spacing/2.0f;
    }

    bool canMove(int dir) {
        int gx = (int)round((position.first + size - spacing/2.0f) / spacing);
        int gy = (int)round((position.second + size - spacing/2.0f) / spacing);

        switch (dir) {
        case 1: gy += 1; break; // up
        case 2: gy -= 1; break; // down
        case 3: gx -= 1; break; // left
        case 4: gx += 1; break; // right
        default: return false;
        }

        pair<float,float> cellCenter = { -size + spacing/2.0f + gx*spacing, -size + spacing/2.0f + gy*spacing };
        if (find(wall().begin(), wall().end(), cellCenter) != wall().end()) return false;
        return true;
    }

public:
    Ghost(int name, float roomX, float roomY)
        : Character(roomX, roomY), ghostName(name), ghostState(Eaten), force(0), currentDirection(0), lastDirection(0) {
        updateColor();
    }

    void changeStateFrightened() {
    ghostState = Frightened;
    updateColor();
    force = 1;
}
    void changeStateChase() {
    ghostState = Chase;
    updateColor();
    force = 1;
    }
    void changeStateScatter() {
    ghostState = Scatter;
    updateColor();
    force = 1;
    }
    void changeStateEaten() {
    ghostState = Eaten;

    if (ghostName == 1) position = { -size + spacing/2.0f + 5*spacing, -size + spacing/2.0f + 5*spacing };
    else if (ghostName == 2) position = { -size + spacing/2.0f + 4*spacing, -size + spacing/2.0f + 5*spacing };
    else if (ghostName == 3) position = { -size + spacing/2.0f + 5*spacing, -size + spacing/2.0f + 4*spacing };
    else if (ghostName == 4) position = { -size + spacing/2.0f + 4*spacing, -size + spacing/2.0f + 4*spacing };

    // Align the ghost to the cell center
    alignToCell();

    force = 0;
    currentDirection = 0;
    lastDirection = 0;
    updateColor();

    reentryTime = elapsedTime + 3000; 

    }


    
    bool shouldScatter() {
    int sec = elapsedTime / 1000;
    int tens = (sec / 10) % 10;
    return (tens < 3); 
}

    void setTarget(float pacX, float pacY, float pacDirX=0, float pacDirY=0, float blinkyX=0, float blinkyY=0) {
        int pX = (int)round((pacX + size) / spacing);
        int pY = (int)round((pacY + size) / spacing);
        int bX = (int)round((blinkyX + size) / spacing);
        int bY = (int)round((blinkyY + size) / spacing);

        switch (ghostState) {
        case Chase:
        /*
        Since our grid is small, we have adjusted the missions as below
        : Blinky: Pac-Man
        : Pinky: 2 spaces ahead of Pac-Man
        : Inky: mirrored position of Blinky, centered 1 space ahead of Pac-Man
        : Clide:
            >> Pac-Man, if it is 4 spaces away from Pac-Man
            >> Target in Scatter state, otherwise
        */
            if (ghostName == 1) { // Blinky
                targetX = pX; targetY = pY;
            } else if (ghostName == 2) { // Pinky
                int aheadX = pX + (int)(2 * pacDirX);
                int aheadY = pY + (int)(2 * pacDirY);
                if (aheadX < 0) aheadX = 0; if (aheadX > 9) aheadX = 9;
                if (aheadY < 0) aheadY = 0; if (aheadY > 7) aheadY = 7;
                targetX = aheadX; targetY = aheadY;
            } else if (ghostName == 3) { // Inky
                int mirrorX = 2 * (pX + (int)pacDirX) - bX;
                int mirrorY = 2 * (pY + (int)pacDirY) - bY;
                if (mirrorX < 0) mirrorX = 0; if (mirrorX > 9) mirrorX = 9;
                if (mirrorY < 0) mirrorY = 0; if (mirrorY > 7) mirrorY = 7;
                targetX = mirrorX; targetY = mirrorY;
            } else { // Clyde
                float dist = std::sqrt(std::pow(getX()-pacX,2)+std::pow(getY()-pacY,2));
                if (dist < 4*spacing) {
                    targetX = 0; targetY = 0; // scatter corner
                } else {
                    targetX = pX; targetY = pY;
                }
            }
            break;
        case Scatter:
            if (ghostName == 1) { targetX = 9; targetY = 7; }
            else if (ghostName == 2) { targetX = 0; targetY = 7; }
            else if (ghostName == 3) { targetX = 9; targetY = 0; }
            else if (ghostName == 4) { targetX = 0; targetY = 0; }
            break;
        case Frightened:
            targetX = (getX() < pacX) ? 0 : 9;
            targetY = (getY() < pacY) ? 0 : 7;
            break;
        case Eaten:
            if (ghostName == 1) { targetX = 5; targetY = 5; }
            else if (ghostName == 2) { targetX = 4; targetY = 5; }
            else if (ghostName == 3) { targetX = 5; targetY = 4; }
            else if (ghostName == 4) { targetX = 4; targetY = 4; }
            break;
        }
    }

    void moveAI() {
    if (ghostState == Eaten) {
        if (elapsedTime < reentryTime) {
            // Wait
            return;
        }
        float targetYCoord = -size + spacing/2.0f + 6 * spacing;
        if (position.second < targetYCoord) {
        // Move up
        position.second += speed;
    } else {
        // Once the ghosts have crossed the wall
        alignToCell();
        force = 1;

        // Decide Scatter/Chase based on time
        if (shouldScatter()) changeStateScatter(); 
        else changeStateChase();
    }
        return;
    }

    if (isCellCenter()) {
        int gx = (int)round((position.first + size - spacing/2.0f) / spacing);
        int gy = (int)round((position.second + size - spacing/2.0f) / spacing);

        if ((ghostState == Scatter) && gx == targetX && gy == targetY) {
            currentDirection = 0;
        } else {
            float tx = -size + spacing/2.0f + targetX * spacing;
            float ty = -size + spacing/2.0f + targetY * spacing;
            float gxCoord = getX();
            float gyCoord = getY();

            float distX = tx - gxCoord;
            float distY = ty - gyCoord;
            float eps = 0.1f;
            int primaryDir, secondaryDir;
            if (fabs(distX) > fabs(distY) + eps) {
                primaryDir = (distX > 0) ? 4 : 3; 
                secondaryDir = (distY > 0) ? 1 : 2;
            } else if (fabs(distY) > fabs(distX) + eps) {
                primaryDir = (distY > 0) ? 1 : 2;
                secondaryDir = (distX > 0) ? 4 : 3;
            } else {
                primaryDir = (distX > 0) ? 4 : 3; 
                secondaryDir = (distY > 0) ? 1 : 2;
            }

            int chosenDir = 0;
            if (canMove(primaryDir)) {
                chosenDir = primaryDir;
            } else if (canMove(secondaryDir)) {
                chosenDir = secondaryDir;
            } else {
                if (lastDirection != 0 && canMove(lastDirection)) {
                    chosenDir = lastDirection;
                } else {
                    chosenDir = 0;
                }
            }
            currentDirection = chosenDir;
        }
    }

    if (frightenTime % 2) return;   // Reduce speed when frightened
    if (currentDirection != 0) {
        switch (currentDirection) {
            case 1: position.second += speed; break;
            case 2: position.second -= speed; break;
            case 3: position.first -= speed;  break;
            case 4: position.first += speed;  break;
        }
    }

    if (currentDirection != 0) {
        lastDirection = currentDirection;
    }
    }

    int getGhostState(){
        return (int)ghostState;
    }

    void drawGhost() const {
        glColor3f(color[0], color[1], color[2]);
        glPointSize(30.0f);
        glBegin(GL_POINTS);
        glVertex3f(position.first, position.second, 0.5f);
        glEnd();
    }
};