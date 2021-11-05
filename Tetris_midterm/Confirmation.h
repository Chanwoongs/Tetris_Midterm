#pragma once
#include "Panel.h"
#include "Button.h"

class Confirmation : public Panel
{
	Button* exitButton;
	Button* resumeButton;
public:
	Confirmation(const Position& pos, int width, int height, GameObject* parent)
		: Panel("", pos, width, height, parent)
	{
		// 비활성화 상태로 초기화
		this->setActive(false);
		exitButton = new Button(Position{ 1, 1 }, 8, 3, this);
		resumeButton = new Button(Position{ 11, 1 }, 8, 3, this);
	}
	~Confirmation() {}

	void update() override
	{
		if (exitButton->onClick())
		{
			exit(0);
		}
		if (resumeButton->onClick())
		{
			this->setActive(false);
		}
	}

	// 창 그리기
	void draw()
	{
		// 테두리를 먼저 그린다
		Panel::draw();
		// 자기 자신 그리기
		GameObject::draw();
	}
};