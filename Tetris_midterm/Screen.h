#pragma once

#include <iostream>
#include "Position.h"
#include "Borland.h"

class Screen
{
private:
	int		width; // visible width
	int		height;
	int		size;
	char* canvas;

	// constructor (생성자 함수) 메모리공간상에 적재되는 순간 호출되는
	Screen(int width = 80, int height = 20)
		: width(width), height(height),
		canvas(new char[((size_t)width + 1) * height])
	{
		bool faultyInput = false;
		if (this->width <= 0) {
			this->width = 80;
			faultyInput = true;
		}
		if (this->height <= 0) {
			this->height = 20;
			faultyInput = true;
		}
		size = (this->width + 1) * this->height;
		if (faultyInput == true) {
			delete canvas;
			canvas = new char[size];
		}
	}
	// destructor (소멸자 함수) 메모리공간상에서 없어지는 순간 호출되는 함수
	virtual ~Screen()
	{
		if (canvas != nullptr)
			delete[] canvas;
		canvas = nullptr;
		width = 0; height = 0;
	}

	static Screen* Instance;

	// 유효한 범위인지
	bool validateRange(int offset) const { 
		return offset >= 0 || offset < size;
	}

public:

	static Screen* GetInstance() {
		if (Instance == nullptr) {
			Instance = new Screen(80, 35);
		}
		return Instance;
	}

	// 스크린 가로 가져오기
	int getWidth() const { return width; }
	// 스크린 가로 세팅
	void setWidth(int width) { this->width = width; }

	// 스크린 높이 가져오기
	int getHeight() const { return height; }

	// 포지션을 인덱스로
	int pos2Offset(const Position& pos) const {
		// 범위 밖이라면
		if (pos.x < 0 || pos.x > width || pos.y < 0 || pos.y > height) return -1;

		return (width + 1) * pos.y + pos.x;
	}

	// 스크린 지우기
	void clear() { memset(canvas, ' ', size); }

	// 모양의 좌표를 인덱스로 바꾸어 모양 그리기
	void draw(const Position& pos, const char* shape, const Dimension& dim) {
		// 좌표 인덱스 변환
		int offset = pos2Offset(pos);
		// 범위를 벗어나면
		if (validateRange(offset) < 0) return;
		// 한칸씩 복사
		for (int h = 0; h < dim.y; h++)
		{
			strncpy(&canvas[offset + (width + 1) * h], &shape[h * dim.x], dim.x);
		}
	}
	// 좌표를 인덱스로 바꾸어 그리기
	void draw(int x, int y, char shape) {
		// 좌표 인덱스 변환
		int offset = pos2Offset({ x, y });
		// 범위를 벗어나면
		if (validateRange(offset) < 0) return;
		// 모양 바꾸기
		canvas[offset] = shape;
	}
	void draw(const Position& pos, char shape) { draw(pos.x, pos.y, shape); }
	void draw(int x, int y, const char* shape, int len) { draw(Position{ x, y }, shape, Dimension{ len, 1 }); }
	void draw(const Position& pos, const char* shape) { draw(pos.x, pos.y, shape, strlen(shape)); }
	void draw(const Position& pos, const char* shape, int len) { draw(pos.x, pos.y, shape, len); }
	// 수평선 그리기
	void drawLineHorizontal(const Position& pos, int width) {
		if (pos.x < 0 || pos.y < 0 || pos.x + width > getWidth() || pos.y > getHeight()) return;

		for (int i = pos.x; i <= min(this->width, pos.x + width); i++)
		{
			draw(i, pos.y, 205);
		}
	}
	// 수직선 그리기
	void drawLineVertical(const Position& pos, int height) {
		if (pos.x < 0 || pos.y < 0 || pos.x > getWidth() || pos.y + height > getHeight()) return;

		for (int i = pos.y; i <= min(this->height, pos.y + height); i++)
		{
			draw(pos.x, i, 186);
		}
	}
	// 사각형 그리기
	void drawRectangle(const Position& topLeft, const Dimension& sz) {
		drawLineHorizontal(topLeft, sz.x);
		drawLineHorizontal(Position{ topLeft.x, topLeft.y + sz.y }, sz.x);
		drawLineVertical(topLeft, sz.y);
		drawLineVertical(Position{ topLeft.x + sz.x, topLeft.y }, sz.y);
		draw(topLeft, 201);
		draw(Position{ topLeft.x + sz.x, topLeft.y }, 187);
		draw(topLeft.x, topLeft.y + sz.y, 200);
		draw(topLeft.x + sz.x, topLeft.y + sz.y, 188);
	}

	// 스크린 출력
	void render()
	{
		Borland::gotoxy(0, 0);
		for (int h = 0; h < height; h++)
			canvas[(width + 1) * (h + 1) - 1] = '\n';
		canvas[size - 1] = '\0';
		printf("%s", canvas);
	}
};