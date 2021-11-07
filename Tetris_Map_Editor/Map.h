#pragma once
#include <iostream>
#include <fstream>
#include "Panel.h"
using namespace std;

class Map : public Panel {
	string map;

	static const char rect = '\xdb';

public:
	//			위치			가로		세로			태그			부모
	Map(const Position& pos, int width, int height, const string& tag, GameObject* parent)
		: Panel("", pos, width, height, tag, parent)
	{
		// 맵 초기화
		for (int i = 0; i < width * height; i++)
		{
			map.append("0");
		}
	}
	~Map() 
	{}

	void editMap(const Position& pos)
	{
		int index = pos2Offset(screen2local(pos));

		if (map[index] == '0')
		{
			map[index] = '1';
		}
		else if (map[index] == '1')
		{
			map[index] = '0';
		}
	}

	string getMap()
	{
		return map;
	}

	string getEmptyMap()
	{
		for (int i = 0; i < getWidth() * getHeight(); i++)
		{
			map[i] = '0';
		}
		return map;
	}

	// 맵 그리기
	void draw()
	{
		// 테두리를 먼저 그린다
		Panel::draw();

		auto height = dim.y;
		auto width = dim.x;

		// map칸이 true 이면 네모로 채우고, 아니라면 빈칸으로 그리기
		for (int i = 0; i < height; i++) 
		{
			for (int j = 0; j < width; j++) {
				setShape(map[j + i * width] == '1' ? rect : ' ', j + i * width);
			}
		}
		// 자기 자신 그리기
		GameObject::draw();
	}
};