#pragma once
#include "Panel.h"

class Confirmation : public Panel
{
	
public:
	Confirmation(const Position& pos, int width, int height, GameObject* parent)
		: Panel("", pos, width, height, parent)
	{

	}
	~Confirmation() {}

	// 맵 그리기
	void draw()
	{
		// 테두리를 먼저 그린다
		Panel::draw();
		// 자기 자신 그리기
		GameObject::draw();
	}
};