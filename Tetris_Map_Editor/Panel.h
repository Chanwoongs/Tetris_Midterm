#pragma once
#include "GameObject.h"
class Panel : public GameObject
{
	string title;

public:
	//			제목					위치			가로		세로		태그				부모
	Panel(const string& title, const Position& pos, int width, int height, const string& tag, GameObject* parent)
		: GameObject("", pos, Dimension{ width, height }, tag, parent), title(title)
	{}
	// 패널 그리기
	void draw() override
	{
		// 스크린 좌표계로 위치 변경
		Position pos = local2Screen();
		// 네모 그리기 좌표에서 공간만큼
		screen->drawRectangle({ pos.x - 1, pos.y - 1 }, { dim.x + 1, dim.y + 1 });

		// 타이틀이 없다면 return
		if (title.length() == 0) return;
		// 왼쪽 모퉁이에 타이틀 그리기
		screen->draw({ pos.x + 1, pos.y - 1 }, title.c_str());
	}
};