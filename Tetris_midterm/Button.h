#pragma once
#include "Panel.h"

class Button : public Panel
{
	string		name;
	bool		isClicked;
	Input*		input;
public:
	Button(const string& name, const Position& pos, int width, int height, const string& tag, GameObject* parent)
		: name(name), Panel("", pos, width, height, tag, parent), isClicked(false), input(Input::GetInstance())
	{}
	~Button() {}

	// 버튼이 눌렸는지
	bool onClick() 
	{
		// 스크린 좌표계로 변환
		Position pos = local2Screen(getPos());
		// 버튼 범위를 클릭하면
		if (input->getMousePosition().x > pos.x && input->getMousePosition().x < pos.x + getWidth() + 1 &&
			input->getMousePosition().y > pos.y && input->getMousePosition().y < pos.y + getHeight() + 1 &&
			input->getMouseButtonDown(0))
		{
			// 클릭 했다
			isClicked = true;
		}
		// 클릭 안했다
		else isClicked = false;

		return isClicked;
	}

	// 버튼 그리기
	void draw() override
	{
		// 테두리를 먼저 그린다
		Panel::draw();
		// 문자열 그리기
		screen->draw({ parent->getPos().x + getPos().x + 1, parent->getPos().y + getPos().y + 2 }, name.c_str());
	}
};
