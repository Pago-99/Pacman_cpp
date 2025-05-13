#pragma once
#include "Character.h"

class Pacman : public Character {
private:
	int movingState; //0: 정지, 1: 상, 2: 하, 3: 좌, 4: 우
	int keyboard, heading, open, score, life, kill;
	int specialState; //0: 평소 1: 승리 2: 죽음(목숨있음) 3: 죽어서 게임 종료(목숨 없음)
	vector<pair<float, float>> point;
	vector<pair<float, float>> bigPoint;

	void reset() {
		movingState = 0;
		keyboard = 0;
		heading = 3;
		open = 10;
		specialState = 0;
		kill = 1;
	}

public:
	Pacman(float startX, float startY) : Character(startX, startY) {
		score = 0;
		life = 4;
		specialState = 0;
		point = path();
		bigPoint = {
			{ -mainSIZE + mainSPACING / 2.0f, -mainSIZE + mainSPACING / 2.0f },
			{ -mainSIZE + mainSPACING / 2.0f, -mainSIZE + mainSPACING / 2.0f + mainSPACING * 7 },
			{ -mainSIZE + mainSPACING / 2.0f + mainSPACING * 9, -mainSIZE + mainSPACING / 2.0f },
			{ -mainSIZE + mainSPACING / 2.0f + mainSPACING * 9, -mainSIZE + mainSPACING / 2.0f + mainSPACING * 7 }
		};
		reset();
	}

	//setter
	void setKeyboard(int key) {
		switch (key) {
		case GLUT_KEY_UP:
			keyboard = 1;
			break;
		case GLUT_KEY_DOWN:
			keyboard = 2;
			break;
		case GLUT_KEY_LEFT:
			keyboard = 3;
			break;
		case GLUT_KEY_RIGHT:
			keyboard = 4;
			break;
		case 0:
			keyboard = 0;
			break;
		}
	}

	void startMoving(int key) {
		if (key == GLUT_KEY_LEFT) movingState = 3;
		else movingState = 4;
	}

	int getHeadDir() {
		return heading;
	}

	int getScore() {
		return score;
	}

	int getSpecial() {
		return specialState;
	}

	void moving() {
		pair<float, float> Pos = position;
		if (find(path().begin(), path().end(), Pos) == path().end()) movingState = move(movingState); 
		else { //칸의 중심에 있을 때
			movingState = move(keyboard);
			auto isPoint = find(point.begin(), point.end(), Pos); //이 자리에 먹이가 있으면 먹음
			if (isPoint != point.end()) {
				point.erase(isPoint);
				score += 10;
				if (point.empty()) specialState = 1; //먹이를 다 먹으면 승리
			}
			isPoint = find(bigPoint.begin(), bigPoint.end(), Pos); //이 자리에 큰 먹이가 있으면 frighten true로 변경
			if (isPoint != bigPoint.end()) {
				bigPoint.erase(isPoint);
				score += 20; //큰 먹이는 30점
				frightenTime = 300; //큰 먹이를 먹으면 300프레임동안 frightened 유지
			}
		}
		if (movingState) heading = movingState;
		if (frightenTime) frightened = --frightenTime; //frighten time동안 true로 유지, frighten time 1씩 줄이기
		else kill = 1; //frighten time이 끝나면 고스트 먹을 때 점수 초기화
	}

	void impactGhost() {
    if (frightened) {
        // Eat ghost, increase score
        score += 50 * kill++;
        // DO NOT reduce life or set specialState here!
    } else {
        // Not frightened = Pac-Man dies
        if (life--) specialState = 2; 
        else specialState = 3;
    }
}

	
	void restart(float startX, float startY) { //다시시작 함수
		position = { -size + spacing / 2.0f + startX * spacing, -size + spacing / 2.0f + startY * spacing };
		reset();
	}

	void drawPacman() {
		glColor3f(1.0f, 1.0f, 0.0f);
		const int triangleAmount = 90;
		const float twicePi = 2.0f * 3.14159f;
		const int angle[4] = {90, 270, 180, 0};
		glPushMatrix();
		glTranslatef(position.first, position.second, 0.0f);
		glRotatef(angle[heading-1], 0.0f, 0.0f, 1.0f);
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(0, 0);

		for (int i = abs(open); i <= triangleAmount-abs(open); i++) {
			glVertex2f(
				mainSPACING * cos(i * twicePi / triangleAmount) * 0.25,
				mainSPACING * sin(i * twicePi / triangleAmount) * 0.25
			);
		}
		glEnd();
		glPopMatrix();

		if (open == 10) open = -10;
		open++; //입 움직이기

		glPushMatrix(); //남은 life 그리기
		glTranslatef(-mainSIZE, -mainSIZE - mainSPACING / 2.0f, 0.0f);
		for (int i = 0; i < life; i++) {
			glTranslatef(mainSPACING / 2.0f, 0.0f, 0.0f);
			glBegin(GL_TRIANGLE_FAN);
			glVertex2f(0, 0);

			for (int j= 2; j < 19; j++) {
				glVertex2f(
					mainSPACING * cos(j * twicePi / 20) * 0.2,
					mainSPACING * sin(j * twicePi / 20) * 0.2
				);
			}
			glEnd();
		}
		glPopMatrix();

	}

	void drawPoint()const {
		//일반 먹이
		glColor3f(1.0f, 1.0f, 1.0f);
		glPointSize(5.0f);
		glBegin(GL_POINTS);
		for (const auto& coord : point) {
			float x = coord.first;
			float y = coord.second;
			glVertex3f(x, y, 1.0f);
		}
		glEnd();
		//큰 먹이
		glColor3f(1.0f, 0.0f, 1.0f);
		glPointSize(15.0f);
		glBegin(GL_POINTS);
		for (const auto& coord : bigPoint) {
			float x = coord.first;
			float y = coord.second;
			glVertex3f(x, y, 0.5f);
		}
		glEnd();
	}
};
