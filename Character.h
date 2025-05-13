#pragma once
#include <iostream>
#include <vector>
#include <GL/freeglut.h>
#include "Definition.h"
using namespace std;

class Character {
protected:
	pair<float, float> position;
	static bool frightened; //false: normal, true: frightened
	static int frightenTime;

	static constexpr float spacing = mainSPACING;
	static constexpr float speed = spacing / 32.0f;
	static constexpr float size = mainSIZE;

	inline static vector<pair<float, float>>& wall() { //미로, 테두리, ghost's room
		static vector<pair<float, float>> wall;
		wall.resize(64);
		int i = 0;
		float half = spacing / 2.0f;
		float x_start = -size + half;
		float y_start = size - 2 * spacing - half;

		vector<pair<float, float>> maze = {
			//square1
		   { x_start + spacing * 1, y_start - spacing * 1},
		   { x_start + spacing * 1, y_start - spacing * 2},
		   //maze
		  { x_start + spacing * 3, y_start - spacing * 2},
		  { x_start + spacing * 4, y_start - spacing * 4}, //미로 수정한 부분
		  { x_start + spacing * 5, y_start - spacing * 4}, //미로 수정한 부분
		  { x_start + spacing * 6, y_start - spacing * 2},
		  { x_start + spacing * 3, y_start - spacing * 3},
		  { x_start + spacing * 3, y_start - spacing * 4},
		  { x_start + spacing * 6, y_start - spacing * 3},
		  { x_start + spacing * 6, y_start - spacing * 4},
		  // square2
		 { x_start + spacing * 1, y_start - spacing * 6},
		 { x_start + spacing * 2, y_start - spacing * 6},
		 // square3
		 { x_start + spacing * 4, y_start - spacing * 6},
		 { x_start + spacing * 5, y_start - spacing * 6},
		 // square4
		 { x_start + spacing * 7, y_start - spacing * 6},
		 { x_start + spacing * 8, y_start - spacing * 6},
		 // square5
		 { x_start + spacing * 8, y_start - spacing * 1},
		 { x_start + spacing * 8, y_start - spacing * 2},
		 // 추가한 미로
		 // square6
		 { x_start + spacing * 3, y_start - spacing * 0},
		 { x_start + spacing * 4, y_start - spacing * 0},
		 { x_start + spacing * 5, y_start - spacing * 0},
		 { x_start + spacing * 6, y_start - spacing * 0},
		 // square7
		 { x_start + spacing * 1, y_start - spacing * 4},
		 // square8
		 { x_start + spacing * 8, y_start - spacing * 4}
		};

		while (i < 10) wall.at(i-1) = { -size + half + i++ * spacing, -size - half }; //아랫변
		while (i < 20) wall.at(i-1) = { -size + half + (i++ - 10) * spacing, size - 2 * spacing + half }; //윗변
		while (i < 28) wall.at(i-1) = { -size - half, -size + half + (i++ - 20) * spacing }; //좌변
		while (i < 36) wall.at(i-1) = { size + half, -size + half + (i++ - 28) * spacing }; //우변
		wall.at(i++) = { -size + half + 4 * spacing, -size + half + 5 * spacing };
		wall.at(i++) = { -size + half + 5 * spacing, -size + half + 5 * spacing };
		wall.at(i++) = { -size + half + 4 * spacing, -size + half + 4 * spacing };
		wall.at(i++) = { -size + half + 5 * spacing, -size + half + 4 * spacing };
		copy(maze.begin(), maze.end(), wall.begin() + 40);

		return wall;
	}
	inline static vector<pair<float, float>>& path() {
		static vector<pair<float, float>> path;
		path.resize(52);
		float x_start = -size + spacing / 2.0f;
		float y_start = -size + spacing / 2.0f;

		int i = 0;
		for (int j = 0; j < 8; j++)
			for (int k = 0; k < 10; k++) {
				pair<float, float> v = { x_start + k * spacing, y_start + j * spacing };
				if (find(wall().begin() + 36, wall().end(), v) == wall().end()) path.at(i++) = v;
			}

		return path;
	}

	int move(int dir, int force = 1) { //1: 상, 2: 하, 3: 좌, 4: 우 return값은 어디로 움직였는지(1,2,3,4) 또는 움직이지 않았는지(0)를 알려준다.
		pair<float, float> v = position;
		switch (dir) {
		case 1: //위로 움직일 때
			v.second += spacing;
			if (find(wall().begin(), wall().end(), v) != wall().end() && force) return 0; //위쪽이 벽이면 이동하지 않는다. force == 0이면 강제로 이동
			position.second += speed;
			return 1;
		case 2: //아래로 움직일 때
			v.second -= spacing;
			if (find(wall().begin(), wall().end(), v) != wall().end()) return 0;
			position.second -= speed;
			return 2;
		case 3: //왼쪽으로 움직일 때
			v.first -= spacing;
			if (find(wall().begin(), wall().end(), v) != wall().end()) return 0;
			position.first -= speed;
			return 3;
		case 4: //오른쪽으로 움직일 때
			v.first += spacing;
			if (find(wall().begin(), wall().end(), v) != wall().end()) return 0;
			position.first += speed;
			return 4;
		default:
			return 0;
		}
	}

	bool isClose(float a, float b) { //a랑 b의 차가 0.5칸보다 작은지 확인하는 함수(impact 함수에서 쓰임)
		return (-0.5f * spacing < a - b) && (a - b < 0.5f * spacing);
	}

public:
	//initialize
	Character(float startX, float startY) { //왼쪽 아래를 0,0으로 생각했을 때 좌표
		position = { -size + spacing / 2.0f + startX * spacing, -size + spacing / 2.0f + startY * spacing };
	}
	//getter
	float getX()const {
		return position.first;
	}
	float getY()const {
		return position.second;
	}

	int getIdxX() const {
		return (position.first + size) / spacing;
	}

	int getIdxY() const {
		return (position.second + size + spacing) / spacing;
	}

	bool areGhostsFrightened() const {
		return frightened;
	}

	void resetStaticVariables() {
		frightened = false;
		frightenTime = 0;
	}

	bool impact(Character enemy) { //enemy와 충돌하면 true, 아니면 false를 리턴한다.
		if (isClose(position.first, enemy.getX()) && (position.second == enemy.getY())) return 1; //X 축 방향으로 가까울때
		if (isClose(position.second, enemy.getY()) && (position.first == enemy.getX())) return 1; //Y 축 방향으로 가까울때
		return 0;
	}
};

