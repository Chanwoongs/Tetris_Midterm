#pragma once
#include "GameObject.h"

class Score : public GameObject
{
	int value;
	char buffer[3];

public:
	//			위치				   부모
	Score(const Position& pos, GameObject* parent)
		: GameObject("0", pos, Dimension{ 3, 1 }, "", parent), value(0)
	{
		// value 값을 buffer에 저장
		sprintf(buffer, "%3d", value % 1000);
	}

	// 스코어 그리기
	void draw() override
	{
		// value 값을 buffer에 저장
		sprintf(buffer, "%3d", value % 1000);
		// 스크린에 buffer(score) 그리기
		screen->draw(local2Screen(), buffer);
	}

	// 스코어 값 세팅
	void setValue(int value) { this->value = value; }

	// 스코어 값 가져오기
	int getValue() const { return value; }
};                              