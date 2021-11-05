#pragma once
#include "Panel.h"

class Button : public Panel
{
	const char*		name;
	bool			isClicked;
	Input*			input;
public:
	Button(const Position& pos, int width, int height, GameObject* parent)
		: name(name), Panel("", pos, width, height, parent), isClicked(false), input(Input::GetInstance())
	{}
	~Button() {}

	// 버튼이 눌렸는지
	bool onClick() 
	{
		// 버튼 범위를 클릭하면
		if (input->getMousePosition().x > parent->getPos().x + getPos().x && input->getMousePosition().x < parent->getPos().x + getPos().x + getWidth() &&
			input->getMousePosition().y > parent->getPos().y + getPos().y && input->getMousePosition().y < parent->getPos().y + getPos().y + getHeight() &&
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
	void draw()
	{
		// 테두리를 먼저 그린다
		Panel::draw();
		// 자기 자신 그리기
		GameObject::draw();
	}
};
