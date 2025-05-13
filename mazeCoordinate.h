#pragma once
#include "BASELINE.h"

class totalCoordinate {
private:
	int col_vector_input;
	int row_vector_input;
	float col_vector;
	float row_vector;
	bool bghostMovable;
protected:
	vector<pair<float, float>> point;
	vector<pair<float, float>> Bigpoint;

public:
	BASELINE baseline;

	// 미로 좌표계로 변환(행렬 입력)
	totalCoordinate(int x, int y){ setColVector(x), setRowVector(y); }

	void setRowVector(int x) { row_vector_input = x; }
	void setColVector(int y) { col_vector_input = y; }

	float getColVector() {
		col_vector = -mainSIZE + mainSPACING / 2.0f + mainSPACING * col_vector_input;
		return col_vector;
	}
	float getRowVector() {
		row_vector = -mainSIZE + mainSPACING / 2.0f + mainSPACING * row_vector_input;
		return row_vector;
	}


	bool isghostMovable(int x, int y) {
		// 행렬식을 좌표로 변환
		baseline.setSize(mainSIZE);
		baseline.setSpacing(mainSPACING);
		setColVector(x);
		setRowVector(y);

		// 좌표를 비교할 허용 오차
		const float epsilon = 0.01f;
		float currentRow = getRowVector();
		float currentCol = getColVector();


		// 미로 좌표 확인
		const vector<pair<float, float>>& MazeCoords = baseline.getMazeVector();
		for (const auto& coord : MazeCoords) {
			float xAxis = coord.first;
			float yAxis = coord.second;

			// 좌표가 허용 오차 내에 있으면 이동 불가
			if (fabs(xAxis - currentCol) < epsilon && fabs(yAxis - currentRow) < epsilon) {
				
				return false;
			}
		}

		return true;
	}

	// 포인트 생성
	bool ghostHome(int i, int j) {
		if ((i == 4 && j == 5)|| (i == 4 && j == 4)|| (i == 5 && j == 5) || (i == 5 && j == 4)) { return true; }
		else return false;
	}
	bool bigPointcheck(int i, int j) {
		if ((i == 0 && j == 0) || (i == 0 && j == 7) || (i == 9 && j == 0) || (i == 9 && j == 7)) { return true; }
		else return false;
	}
};
