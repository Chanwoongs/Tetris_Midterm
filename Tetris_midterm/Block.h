#pragma once

#include "Map.h"

class Block :
	public GameObject
{
	bool		interactable; /* indicator whether it can respond with user input events.*/
	float		currentX;
	float		currentY;
	float		speed;
	Map*		map;
	char*		shapeBuffer;

	// 블럭 돌리기
	void rotateShape() 
	{
		// 원래 모양 복사
		auto originalShape = getShape();
		// 원래 공간 복사
		auto sz = getDimension();
		int w = sz.x; 
		int h = sz.y;

		// 공식을 이용하여 블럭 모양 변환
		for (int y = 0; y < h; y++)
		{
			for (int x = 0; x < w; x++)
			{
				shapeBuffer[(w - 1 - x) * h + y] = originalShape[y * w + x];
			}
		}

		// 변환된 모양 세팅
		setShape(shapeBuffer);
		sz.x = h; 
		sz.y = w;
		// 변환된 공간 세팅
		setDimension(sz);
	}

public:
	//				모양			위치					공간					부모					상호작용 가능
	Block(const string& shape, const Position& pos, const Position& dim, GameObject* parent = nullptr, bool interactable = true)
	//	 게임오브젝트 const char*								상호작용				맵				좌표X			좌표Y		  속도							모양
		: GameObject(shape.c_str(), pos, dim, parent), interactable(interactable), map(nullptr), currentX(pos.x), currentY(pos.y), speed(0.1f), shapeBuffer{ new char[(size_t)dim.x * dim.y] }
	{}

	~Block() {
		if (shapeBuffer != nullptr) delete[] shapeBuffer;
		shapeBuffer = nullptr;
	}

	// 블럭 업데이트
	void update() override
	{
		// 상호작용 불가능 이거나 맵이 없다면 return
		if (!interactable || !map) return;

		// 정보 가져오기
		auto shape = getShape();
		auto pos = getPos();
		auto width = dim.x;
		auto height = dim.y;

		// 땅에 떨어 졌다면
		if (map->isGrounded(shape, pos, width, height)) 
		{
			// 
			map->place(shape, pos, width, height);

			for (int i = height - 1; i >= 0; --i) {
				int nCombos = 0;
				while (map->evaluateLine(pos.y + i)) {
					nCombos++;
				}
			}

			/* reuse the block. */
			currentX = 4.0f; currentY = 0.0f;
			speed = 0.1f;
			setPos(currentX, currentY); // update location from float to integer			
			//setActive(false);
			return;
		}

		if (input->getKey(VK_RIGHT)) {
			float nextX = currentX + 1;
			if (map && map->isValidRange({ (int)nextX, (int)currentY }, dim))
				currentX = nextX;
		}
		if (input->getKey(VK_LEFT)) {
			float nextX = currentX - 1;
			if (map && map->isValidRange({ (int)nextX, (int)currentY }, dim))
				currentX = nextX;
		}
		if (input->getKey(VK_UP)) {
			rotateShape();
		}
		if (input->getKey(VK_DOWN)) {
			speed *= 2;
		}
		if (input->getKey(VK_SPACE)) {
			if (map) {
				pos.y = currentY;
				while (!map->isGrounded(shape, pos, width, height)) {
					float nextY = currentY + 1;
					if (map->isValidRange({ (int)currentX, (int)nextY }, dim)) {
						pos.y = nextY;
						currentY = nextY;
					}
				}
				return;
			}
		}
		float nextY = currentY + speed;
		if (map && map->isValidRange({ (int)currentX, (int)nextY }, dim)) {
			currentY = nextY;
		}
	}

	void draw() override
	{
		if (interactable == true) {
			setPos(currentX, currentY);
		}
		auto shape = getShape();
		auto pos = getPos();
		auto width = dim.x;
		auto height = dim.y;
		if (!map->isGrounded(shape, pos, width, height))
			screen->draw(local2Screen(), getShape(), dim);
	}

	void setMap(Map* map) {
		this->map = map;
	}

	void setInteractable(bool interactable = true) { this->interactable = interactable; }
};