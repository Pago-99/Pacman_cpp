#pragma once
#include "Pacman.h"
#include "mazeCoordinate.h"
#include "Ghost.h"

Pacman pacman(4.5, 2);
// Start as Eaten
Ghost blinky(1, 5, 5); // room(5,5)
Ghost pinky(2, 4, 5);  // room(4,5)
Ghost inky(3, 5, 4);   // room(5,4)
Ghost clyde(4,4, 4);   // room(4,4)
bool Character::frightened = false;
int Character::frightenTime = 0;
bool start = true; // start=true means paused
int elapsedTime = 0;
int ghostMoveStartTime = 0;

bool shouldScatter() {
    int sec = elapsedTime / 1000;
    int tens = (sec / 10) % 10;
    return (tens < 5);
}


BASELINE baseline;
enum screenMode { initialScreen, gameScreen, gameOverScreen, gameWinScreen, Shutdown };
screenMode screenCheck = initialScreen;
screenMode* screenDictionary = &screenCheck;
totalCoordinate totalcoordinate(0,0);

void projection() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void startFace() {

	/// 미로 및 격자
	baseline.setSize(startSIZE);
	baseline.setSpacing(startSPACING);
	baseline.setColor(0.3f, 0.7f, 0.9f);
	baseline.setCoordinate();
	baseline.drawMaze();
	baseline.drawGrid();

	/// PACMAN 헤드라인
	baseline.setCharacters("PACMAN");
	baseline.setColor(1.0f, 0.0f, 0.0f);
	baseline.setHeadlineWidth(7.0f);
	baseline.setHeadlinePosition(-45.0f, 50.0f, 0.0f);
	baseline.setHeadlineFontsize(0.15f, 0.15f, 0.1f);
	baseline.writeHeadline();

	/// 시작 헤드라인 박스
	baseline.setColor(0.0f, 0.5f, 0.5f);
	baseline.setsquare(-50.0f, -68.0f);
	baseline.setsquaresize(50.0f, 8.0f);
	baseline.pointbox();

	/// 시작 헤드라인
	baseline.setCharacters("START");
	baseline.setColor(0.0f, 1.0f, 0.0f);
	baseline.setHeadlineWidth(5.0f);
	baseline.setHeadlinePosition(-70.0f, -70.0f, 0.0f);
	baseline.setHeadlineFontsize(0.05f, 0.05f, 0.05f);
	baseline.writeHeadline();

	/// 종료 헤드라인 박스
	baseline.setColor(0.8f, 0.1f, 0.2f);
	baseline.setsquare(50.0f, -68.0f);
	baseline.setsquaresize(50.0f, 8.0f);
	baseline.pointbox();

	/// 종료 헤드라인
	baseline.setCharacters("Log Out");
	baseline.setColor(0.0f, 1.0f, 0.0f);
	baseline.setHeadlineWidth(5.0f);
	baseline.setHeadlinePosition(45.0f, -70.0f, 0.0f);
	baseline.setHeadlineFontsize(0.05f, 0.05f, 0.05f);
	baseline.writeHeadline();
}

void interface() {
	// 기본 인터페이스 생성
	BASELINE baseline;

	/// 미로 및 격자
	baseline.setSize(mainSIZE);
	baseline.setSpacing(mainSPACING);
	baseline.setColor(0.3f, 0.7f, 0.9f);
	baseline.setCoordinate();
	baseline.drawMaze();
	//// 전체 모드 완성시 격자 제거할 것
	baseline.drawGrid();

	/// PACMAN 헤드라인
	baseline.setCharacters("PACMAN");
	baseline.setColor(1.0f, 0.0f, 0.0f);
	baseline.setHeadlineWidth(7.0f);
	baseline.setHeadlinePosition(-32.0f, 80.0f, 0.0f);
	baseline.setHeadlineFontsize(0.1f, 0.1f, 0.1f);
	baseline.writeHeadline();

	/// 포인트 헤드라인
	baseline.setCharacters("POINT");
	baseline.setColor(0.0f, 1.0f, 0.0f);
	baseline.setHeadlineWidth(5.0f);
	baseline.setHeadlinePosition(-83.0f, 70.0f, 0.0f);
	baseline.setHeadlineFontsize(0.05f, 0.05f, 0.05f);
	baseline.writeHeadline();

	/// 모드 헤드라인
	baseline.setCharacters("MODE");
	baseline.setColor(0.0f, 1.0f, 0.0f);
	baseline.setHeadlineWidth(5.0f);
	baseline.setHeadlinePosition(-10.0f, 70.0f, 0.0f);
	baseline.setHeadlineFontsize(0.05f, 0.05f, 0.05f);
	baseline.writeHeadline();

	/// 시간 헤드라인
	baseline.setCharacters("TIME");
	baseline.setColor(0.0f, 1.0f, 0.0f);
	baseline.setHeadlineWidth(5.0f);
	baseline.setHeadlinePosition(60.0f, 70.0f, 0.0f);
	baseline.setHeadlineFontsize(0.05f, 0.05f, 0.05f);
	baseline.writeHeadline();

	/// 포인트 박스
	baseline.setColor(0.0f, 0.5f, 0.5f);
	baseline.setsquare(-70.0f, 60.0f);
	baseline.setsquaresize(15.0f, 5.0f);
	baseline.pointbox();
	string score = to_string(pacman.getScore());
	baseline.writePoint(score);

	baseline.setsquare(0.0f, 60.0f);
	baseline.setsquaresize(15.0f, 5.0f);
	baseline.pointbox();
	string ghostState;
	int gs = blinky.getGhostState();
	if (gs == 3) gs = pinky.getGhostState();
	if (gs == 3) gs = inky.getGhostState();
	if (gs == 3) gs = clyde.getGhostState();
	switch (gs) {
	case 0: ghostState = "Chase"; break;
	case 1: ghostState = "Scatter"; break;
	case 2: ghostState = "Frightened"; break;
	case 3:ghostState = "Ready"; break;
	}
	baseline.writePoint(ghostState);

	baseline.setsquare(70.0f, 60.0f);
	baseline.setsquaresize(15.0f, 5.0f);
	baseline.pointbox();
	string timeStr = to_string(elapsedTime / 1000);
	baseline.writePoint(timeStr);

	// 포인트
	pacman.drawPoint();

}

void gameOver(bool victory) {
	// Game Over
	baseline.setsquare(-10.0f, -10.0f);
	baseline.writePoint("Accumated Point: ");
	string score = to_string(pacman.getScore());
	baseline.setsquare(20.0f, -10.0f);
	baseline.writePoint(score);
	baseline.setsquare(-10.0f, -15.0f);
	baseline.writePoint("PlayTime: ");
	baseline.setsquare(20.0f, -15.0f);
	string timeStr = to_string(elapsedTime / 1000);
	baseline.writePoint(timeStr);

	if (victory) { //이겼을때
		baseline.setCharacters("You Win!!");
		baseline.setColor(0.0f, 1.0f, 1.0f);
	}
	else { //졌을때
		baseline.setCharacters("GAME OVER");
		baseline.setColor(1.0f, 0.0f, 0.0f);
	}
	baseline.setHeadlineWidth(8.0f);
	baseline.setHeadlinePosition(-48.0f, 0.0f, 0.0f);
	baseline.setHeadlineFontsize(0.1f, 0.1f, 0.1f);
	baseline.writeHeadline();

	// continue
	baseline.setColor(1.0f, 0.0f, 0.0f);
	baseline.setsquare(-50.0f, -50.0f);
	baseline.setsquaresize(30.0f, 10.0f);
	baseline.pointbox();
	baseline.setCharacters("Restart?");
	baseline.setColor(1.0f, 1.0f, 1.0f);
	baseline.setHeadlineWidth(3.0f);
	baseline.setHeadlinePosition(-73.0f, -52.0f, 0.0f);
	baseline.setHeadlineFontsize(0.05f, 0.05f, 0.05f);
	baseline.writeHeadline();

	// EXIT
	baseline.setColor(1.0f, 1.0f, 1.0f);
	baseline.setsquare(50.0f, -50.0f);
	baseline.setsquaresize(30.0f, 10.0f);
	baseline.pointbox();
	baseline.setCharacters("EXIT");
	baseline.setColor(1.0f, 0.0f, 0.0f);
	baseline.setHeadlineWidth(3.0f);
	baseline.setHeadlinePosition(40.0f, -52.0f, 0.0f);
	baseline.setHeadlineFontsize(0.05f, 0.05f, 0.05f);
	baseline.writeHeadline();
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		float openglX = (float)x;
		float openglY = (float)y;

		switch (*screenDictionary){
		case initialScreen:
			if (openglX >= 0 && openglX <= 400 && openglY >= 640 && openglY <= 700) {
				*screenDictionary = gameScreen;
			}
			if (openglX >= 401 && openglX <= 800 && openglY >= 640 && openglY <= 700) {
				*screenDictionary = Shutdown;
			}
			break;
		case gameOverScreen:
		case gameWinScreen:
			if (openglX >= 80 && openglX <= 320 && openglY >= 560 && openglY <= 640) {
				*screenDictionary = gameScreen;
				// 객체 전부 초기화
				pacman = Pacman(4.5, 2);
				blinky = Ghost(1, 5, 5); // room(5,5)
				pinky = Ghost(2, 4, 5);  // room(4,5)
				inky = Ghost(3, 5, 4);   // room(5,4)
				clyde = Ghost(4, 4, 4);   // room(4,4)
				elapsedTime = 0;
				ghostMoveStartTime = 0;
				blinky.changeStateEaten();
				pinky.changeStateEaten();
				clyde.changeStateEaten();
				inky.changeStateEaten();
				start = true;
				pacman.resetStaticVariables();
			}
			if (openglX >= 478 && openglX <= 800 && openglY >= 560 && openglY <= 640) {
				*screenDictionary = Shutdown;
			}
		}
	}

}

void mouseMove(int x, int y) {
	float openglX = (float)x;
	float openglY = (float)y;
}

void mousePassiveMove(int x, int y) {
	float openglX = (float)x;
	float openglY = (float)y;
}

int modeTimerMs = 0;
bool inChaseMode = false;
void switchGhostModes() {
    // If Chase, switch to Scatter
	// Make sure this doesn't happen in frigtened or eaten state
    if (inChaseMode) {
		if(blinky.getGhostState() == 0 || blinky.getGhostState() == 1)
        	blinky.changeStateScatter();
		if(pinky.getGhostState() == 0 || pinky.getGhostState() == 1)
        	pinky.changeStateScatter();
		if(inky.getGhostState() == 0 || inky.getGhostState() == 1)
        	inky.changeStateScatter();
        if(clyde.getGhostState() == 0 || clyde.getGhostState() == 1)
        	clyde.changeStateScatter();
        inChaseMode = false;
    } else {
        // If Scatter, switch to Chase
		if(blinky.getGhostState() == 0 || blinky.getGhostState() == 1)
        	blinky.changeStateChase();
		if(pinky.getGhostState() == 0 || pinky.getGhostState() == 1)
        	pinky.changeStateChase();
		if(inky.getGhostState() == 0 || inky.getGhostState() == 1)
        	inky.changeStateChase();
        if(clyde.getGhostState() == 0 || clyde.getGhostState() == 1)
        	clyde.changeStateChase();
        inChaseMode = true;
    }
}

void Timer(int value) {
    modeTimerMs += 20;
    elapsedTime += 20;

    if (modeTimerMs >= 5000) {
        switchGhostModes();
        modeTimerMs = 0; 
    }

    glutPostRedisplay();
    int game = pacman.getSpecial();
    switch (game) {
    case 0: 
        break; // normal
    case 1: // victory
        *screenDictionary = gameWinScreen;
        return;
    case 2: // Pacman died but still has life
		pacman.restart(4.5, 2);
		blinky.changeStateEaten();
		pinky.changeStateEaten();
		inky.changeStateEaten();
		clyde.changeStateEaten();
		start = true; // paused
		return;
    case 3: // game over
        *screenDictionary = gameOverScreen;
        return;
    }

    glutTimerFunc(20, Timer, 0);
}

void specialKey(int key, int x, int y) {
    if (start && *screenDictionary == gameScreen) {
        if (key == GLUT_KEY_LEFT || key == GLUT_KEY_RIGHT) {
            start = false; // resume
            pacman.setKeyboard(key);
            pacman.startMoving(key);
			ghostMoveStartTime = elapsedTime + 3000; 

            glutTimerFunc(100, Timer, 0);
        }
    }
    if (!start)
        pacman.setKeyboard(key);
}


int state;
float pacDirX, pacDirY;
// Collision check
bool collided = false;
Ghost* collidedGhost = nullptr;
void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    projection();

    switch (*screenDictionary) {
    case initialScreen:
        startFace();
        break;

    case gameScreen:
        interface(); 

        if (start) {
            // Game paused, just draw locations
            pacman.drawPacman();
            blinky.drawGhost();
            pinky.drawGhost();
            inky.drawGhost();
            clyde.drawGhost();
            break;
        }

        pacman.moving();

		if (!pacman.areGhostsFrightened()) {
		// When ghost iss frightened, change to Scatter or Chase
			if (blinky.getGhostState() == 2) { if (shouldScatter()) blinky.changeStateScatter(); else blinky.changeStateChase(); }
			if (pinky.getGhostState() == 2) { if (shouldScatter()) pinky.changeStateScatter(); else pinky.changeStateChase(); }
			if (inky.getGhostState() == 2)  { if (shouldScatter()) inky.changeStateScatter(); else inky.changeStateChase(); }
			if (clyde.getGhostState() == 2) { if (shouldScatter()) clyde.changeStateScatter(); else clyde.changeStateChase(); }
		} else {
		// Change to Frightened when the ghost is Chase or Scatter
			if (blinky.getGhostState() == 0 || blinky.getGhostState() == 1) blinky.changeStateFrightened();
			if (pinky.getGhostState() == 0 || pinky.getGhostState() == 1) pinky.changeStateFrightened();
			if (inky.getGhostState() == 0  || inky.getGhostState() == 1)  inky.changeStateFrightened();
			if (clyde.getGhostState() == 0 || clyde.getGhostState() == 1) clyde.changeStateFrightened();
		}


        // Collision check
        collided = false;
        collidedGhost = nullptr;
        if (pacman.impact(blinky)) { collided = true; collidedGhost = &blinky; }
        else if (pacman.impact(pinky)) { collided = true; collidedGhost = &pinky; }
        else if (pacman.impact(inky)) { collided = true; collidedGhost = &inky; }
        else if (pacman.impact(clyde)) { collided = true; collidedGhost = &clyde; }

        if (collided) {
            if (pacman.areGhostsFrightened()) {
                // Eat ghost
                pacman.impactGhost(); 
                collidedGhost->changeStateEaten();
            } else {
                // Pac-Man loses life
                pacman.impactGhost(); 
            }
			collided = false;
    		collidedGhost = nullptr;
        }

        pacman.drawPacman();

        state = pacman.getHeadDir();
        pacDirX = 0.0f; pacDirY = 0.0f;
        switch (state) {
        case 1: pacDirY = 1.0f; break;
        case 2: pacDirY = -1.0f; break;
        case 3: pacDirX = -1.0f; break;
        case 4: pacDirX = 1.0f; break;
        }

        blinky.setTarget(pacman.getX(), pacman.getY(), pacDirX, pacDirY);
        pinky.setTarget(pacman.getX(), pacman.getY(), pacDirX, pacDirY);
        inky.setTarget(pacman.getX(), pacman.getY(), pacDirX, pacDirY, blinky.getX(), blinky.getY());
        clyde.setTarget(pacman.getX(), pacman.getY(), pacDirX, pacDirY);

        if (elapsedTime >= ghostMoveStartTime) {
        blinky.moveAI();
        pinky.moveAI();
        inky.moveAI();
        clyde.moveAI();
    }

        blinky.drawGhost();
        pinky.drawGhost();
        inky.drawGhost();
        clyde.drawGhost();
        break;

    case gameOverScreen:
        gameOver(false);
        break;
    case gameWinScreen:
        gameOver(true);
        break;
    case Shutdown:
        exit(0);
        break;
    }

    glFlush();
}



int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutCreateWindow("PACMAN_PLAY");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMove);
	glutPassiveMotionFunc(mousePassiveMove);
	glutSpecialFunc(specialKey);
	glutMainLoop();
	return 0;
}
