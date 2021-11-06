#pragma once
#include "Panel.h"
#include "Button.h"

class Confirmation : public Panel
{
	Button* exitBtn;
	Button* continueBtn;
public:
	Confirmation(const Position& pos, int width, int height, const string& tag, GameObject* parent)
		: Panel("", pos, width, height, tag, parent)
	{
		// 비활성화 상태로 초기화
		this->setActive(false);
		// Exit 버튼 생성
		exitBtn = new Button("Exit", Position{1, 1}, 8, 3, "UI", this);
		// Continue 버튼 생성
		continueBtn = new Button("Continue", Position{11, 1}, 8, 3, "UI", this);
	}
	~Confirmation() {}

	void update() override
	{
		// Exit 버튼 클릭 시 게임 종료
		if (exitBtn->onClick())
		{
			exit(0);
		}
		// Continue 버튼 클릭 시 게임 재개
		if (continueBtn->onClick())
		{
			// TetrisGame에게 게임 재개 알림
			parent->setIsPaused(false);
			// 일시중지 창 끄기
			setActive(false);
		}
	}

	// 창 그리기
	void draw()
	{
		// 테두리를 먼저 그린다
		Panel::draw();
	}
};