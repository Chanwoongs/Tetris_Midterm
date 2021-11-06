#pragma once
#include <iostream>
#include "Panel.h"
#include "Score.h"

class Map : public Panel {
	bool*		map;
	int			upper;
	Score*		score;

	static const char rect = '\xdb';

public:
	//			위치			가로		세로			부모
	Map(const Position& pos, int width, int height, const string& tag, GameObject* parent)
		//				bool형 맵 초기화		현재 가장 높은 위치
		: map(new bool[(size_t)width * height]), upper(height - 1),
		Panel("", pos, width, height, tag, parent), score(nullptr)
	{
		// 맵 초기화
		for (int i = 0; i < width * height; i++)
		{
			map[i] = false;
		}
	}
	~Map() { if (map) delete[] map; }

	// 스코어 세팅
	void setScore(Score* score) {
		this->score = score;
	}

	// 가장 높은 블럭이 위 쪽을 벗어나면
	bool isDone() const { return upper <= 0; }

	// 점수 더하기
	void addScore(int inc) {
		if (!score) return;
		score->setValue(score->getValue() + inc);
	}

	// 줄이 가득 차있는지
	bool isLineAllOccupied(int line) const {
		for (int i = 0; i < dim.x; i++)
		{
			// 줄을 검사하여 줄이 모두 false라면 
			if (!map[line * dim.x + i])
			{
				// 줄이 안차있다
				return false;
			}
		}
		// 줄이 가득 차있다
		return true;
	}

	// 라인 계산
	bool evaluateLine(int line) {
		// 줄이 가득 차있지 않다면
		if (!isLineAllOccupied(line)) return false;
		// 점수 +
		addScore(1);
		// 가로 길이
		auto width = dim.x;

		// 가득찬 라인 false로 초기화
		memset(&map[line * width], false, sizeof(bool) * width);

		// 윗 줄을 아래 줄로 내림
		for (int i = line - 1; i >= (upper - 1) && i >= 0; i--)
		{
			for (int j = 0; j < width; j++)
			{
				map[(i + 1) * width + j] = map[i * width + j];
			}
		}

		// 가장 높은 위치를 내린다
		upper++;

		return true;
	}
	
	// 갈 수 있는 범위 인지 체크
	bool isValidRange(const Position& nextPos, const Dimension& sz)
	{
		auto pos = getPos();
		// 다음 x, y 값이 범위를 벗어나면 false
		if (nextPos.x < 0 || nextPos.x > getWidth() || nextPos.y < 0 || nextPos.y > getHeight()) return false;
		// 다음 x, y 값 + 공간이 범위를 벗어나면 false
		if (nextPos.x + sz.x > getWidth() || nextPos.y + sz.y > getHeight()) return false;

		return true;
	}

	// 땅에 떨어 졌는지 체크
	bool isGrounded(const char* shape, const Position& pos, int w, int h) {
		// 맵 가로 세로 세팅
		auto height = dim.y;
		auto width = dim.x;

		// y 좌표 + 블럭 높이가 높이 아래면 땅에 떨어진 것
		if (pos.y + h >= height) return true;

		// y 좌표 + 블럭 높이
		int next = pos.y + h;
		// 현재 블럭 가장 높은 위치보다 높게 있다면 false
		if (next < upper) return false;
		
		int capacity = getCapacity();

		for (int j = 0; j < w; j++) 
		{
			// 초기값 세팅
			int last = -1;

			// 블럭의 빈칸이 아니라면 last = i로 세팅
			for (int i = 0; i < h; i++) 
			{
				if (shape[j + i * w] != ' ') last = i;
			}

			// 블럭의 빈칸이라면 다시 검색
			if (last == -1) continue;

			// 바로 아래 인덱스 초기화
			auto nextOffset = pos.x + j + (pos.y + last + 1) * width;
			// 아래 인덱스가 범위를 벗어나면
			if (nextOffset >= capacity) return true;
			// 아래 인덱스가 차있다면
			if (map[nextOffset] == true) return true;
		}
		return false;
	}

	// map의 좌표값 체크
	bool isOccupied(const Position& pos) {
		return map[pos2Offset(pos)];
	}

	// 블럭 맵에 위치 시키기
	void place(const char* shape, const Position& pos, int w, int h) 
	{
		// 스크린 좌표계로 변환
		auto worldPos = local2Screen();

		for (int i = 0; i < h; i++) 
		{
			for (int j = 0; j < w; j++) 
			{
				// 모양이 빈칸이 아니라면
				if (shape[j + i * w] != ' ') 
				{
					// 맵의 인덱스 값 설정
					map[pos.x + j + (pos.y + i) * dim.x] = true;
					// 인덱스에 네모로 채우기
					setShape(rect, { pos.x + j, pos.y + i });
				}
			}
		}
		// 위치한 곳의 y가 upper보다 높다면 upper 업데이트
		if (pos.y < upper) upper = pos.y;
	}

	// 맵 그리기
	void draw()
	{
		// 테두리를 먼저 그린다
		Panel::draw();

		auto height = dim.y;
		auto width = dim.x;

		// map칸이 true 이면 네모로 채우고, 아니라면 빈칸으로 그리기
		for (int i = upper - 2; i < height; i++) 
		{
			for (int j = 0; j < width; j++) {
				setShape(map[j + i * width] ? rect : ' ', j + i * width);
			}
		}
		// 자기 자신 그리기
		GameObject::draw();
	}
};