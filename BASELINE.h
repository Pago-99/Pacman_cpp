#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <GL/freeglut.h>
using namespace std;

class BASELINE {
protected:
	string characters;
	float size;
	float spacing;
	float LineWidth;
	float translate[3];
	float fontSize[3];
	float lineColor[3];
	float squareSize[2];
	float squarePosition[2];
	vector<pair<float, float>> MazeVector;

public:
	// Initialize
	BASELINE(string inputCharacters = "PACMAN", float gridSize = 0.8f, float gridSpacing = 0.02f, float HeadLineWidth = 7.0f, float r = 1.0f, float g = 1.0f, float b = 1.0f)
		: LineWidth(HeadLineWidth), characters(inputCharacters), size(gridSize), spacing(gridSpacing) {
		setColor(r, g, b), setHeadlinePosition(r, g, b);
	}

	// ���� INPUT �Լ� ����
	void setCharacters(string inputCharacters) { characters = inputCharacters; }
	void setHeadlineWidth(float HeadLineWidth) {
		LineWidth = HeadLineWidth;
	}
	void setHeadlinePosition(float r, float g, float b) {
		translate[0] = r;
		translate[1] = g;
		translate[2] = b;
	}
	void setHeadlineFontsize(float r, float g, float b) {
		fontSize[0] = r;
		fontSize[1] = g;
		fontSize[2] = b;
	}
	void setSize(float gridSize) { size = gridSize; }
	void setSpacing(float gridSpacing) { spacing = gridSpacing; }
	void setColor(float r, float g, float b) {
		lineColor[0] = r;
		lineColor[1] = g;
		lineColor[2] = b;
	}
	void setsquare(float r, float g) {
		squarePosition[0] = r;
		squarePosition[1] = g;
	}
	void setsquaresize(float w, float h) {
		squareSize[0] = w;
		squareSize[1] = h;
	}

	// GRID ����
	void drawGrid() const {
		glColor3f(lineColor[0], lineColor[1], lineColor[2]);
		glBegin(GL_LINES);
		
		//�Ʒ���
		glVertex3f(-size, -size, 0.0f);
		glVertex3f(size, -size, 0.0f);
		//����
		glVertex3f(-size, size - 2 * spacing, 0.0f);
		glVertex3f(size, size - 2 * spacing, 0.0f);
		//�º�
		glVertex3f(-size, -size, 0.0f);
		glVertex3f(-size, size - 2 * spacing, 0.0f);
		//�캯
		glVertex3f(size, -size, 0.0f);
		glVertex3f(size, size - 2 * spacing, 0.0f);
		//Ghost's room
		glVertex3f(-size + 3 * spacing, size - 4 * spacing, 0.0f);
		glVertex3f(-size + 7 * spacing, size - 4 * spacing, 0.0f);

		glEnd();
	}


	// �̷� ��ǥ�� ����
	void setCoordinate() {
		float x_start = -size + spacing / 2.0f;
		float y_start = size - 2 * spacing - spacing / 2.0f;
		MazeVector = {
			//square1
		   { x_start + spacing * 1, y_start - spacing * 1},
		   { x_start + spacing * 1, y_start - spacing * 2},
		   //maze
		  { x_start + spacing * 3, y_start - spacing * 2},
		  { x_start + spacing * 4, y_start - spacing * 4}, //�̷� ������ �κ�
		  { x_start + spacing * 5, y_start - spacing * 4}, //�̷� ������ �κ�
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
		 // �߰��� �̷�
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
	}

	vector<pair<float, float>> getMazeVector() {
		setCoordinate();
		return MazeVector;
	}

	// �̷� �׸���
	void drawMaze()const {
		glColor3f(lineColor[0], lineColor[1], lineColor[2]);
		// MazeVector X,Y�� �и�
		glBegin(GL_QUADS);
		for (const auto& coord : MazeVector) {
			float x = coord.first;
			float y = coord.second;
			float halfSize = spacing / 2.0f;
			glVertex2f(x - halfSize, y - halfSize);
			glVertex2f(x + halfSize, y - halfSize);
			glVertex2f(x + halfSize, y + halfSize);
			glVertex2f(x - halfSize, y + halfSize);
		}
		glEnd();
	}

	// ������
	void writeHeadline() {
		glPushMatrix();
		glColor3f(lineColor[0], lineColor[1], lineColor[2]);
		glLineWidth(LineWidth);
		glTranslatef(translate[0], translate[1], translate[2]);
		glScalef(fontSize[0], fontSize[1], fontSize[2]);
		for (int i = 0; i < characters.size(); i++) { glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, characters[i]); }
		glPopMatrix();
	}

	void writePoint(string str) {
		glColor3f(1.0f, 1.0f, 1.0f);
		glRasterPos2f(squarePosition[0]-str.size(), squarePosition[1]);
		for (int i = 0; i < str.size(); i++) {
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str[i]);
		}
	}

	// ����Ʈ ǥ�� �ڽ� ����
	void pointbox() {
		glColor3f(lineColor[0], lineColor[1], lineColor[2]);
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(squarePosition[0] - squareSize[0], squarePosition[1] - squareSize[1]);
		glVertex2f(squarePosition[0] + squareSize[0], squarePosition[1] - squareSize[1]);
		glVertex2f(squarePosition[0] + squareSize[0], squarePosition[1] + squareSize[1]);
		glVertex2f(squarePosition[0] - squareSize[0], squarePosition[1] + squareSize[1]);
		glVertex2f(squarePosition[0] - squareSize[0], squarePosition[1] - squareSize[1]);
		glEnd();
	}
};