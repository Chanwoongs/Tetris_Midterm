#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Screen.h"
#include "Input.h"

using namespace std;

class GameObject
{
private:
	char* shape;
	Position			pos;		// "relative" position to its parent game object.

	int					capacity;	// allocated memory size of "shape"
	bool				dirty;		// if its pos is updated, it should be marked as dirty
									// to make sure all the locations of its children game objects
									// are updated accordingly.
	Position			parentWorldPos;	// "absolute" position of its parent game object to the screen 
	bool				active;	// indicator whether it is being served by the update/render logic
									// if "false", it should not be served by the game engine.

protected:

	Screen* screen;
	Input* input;

	vector<GameObject*> children;
	GameObject* parent;
	Dimension			dim;

	// 부모의 월드 포지션 세팅 
	void setParentWorldPos(const Position& parentWorldPos) 
	{ 
		this->parentWorldPos = parentWorldPos; 
	}

	// 자식 객체를 벡터에 삽입
	void add(GameObject* child) 
	{
		if (!child) return;

		children.push_back(child);
	}

public:
	// 생성자		모양				위치					공간			hierarchy부모
	GameObject(const char* face, const Position& pos, const Dimension& dim, GameObject* parent = nullptr)
		//	위치	공간			용량 ( X x Y )
		: pos(pos), dim(dim), capacity((size_t)dim.x* dim.y),
		//		모양 [ X x Y ]						활성화
		shape{ new char[(size_t)dim.x * dim.y] }, active(true),
		//		스크린							입력				포지션 변화
		screen(Screen::GetInstance()), input(Input::GetInstance()), dirty(false),
		//hierarchy부모			부모가 있다면 부모의 포지션을 월드포지션으로, 없다면 (0,0)	
		parent(parent), parentWorldPos(parent ? parent->local2Screen() : Position::zeros)
	{
		//	부모가 있다면 자식으로 이 객체를 삽입
		if (parent) parent->add(this);
		//	모양 세팅
		setShape(face);
	}

	virtual ~GameObject()
	{
		//	자식 객체가 없을 때 까지 자식 객체 삭제
		while (children.size() > 0)
		{
			auto child = children.back();
			children.pop_back();
			delete child;
		}
		// 동적 할당 해제
		if (shape != nullptr)
			delete[] shape;
		shape = nullptr;
	}

	virtual void move(const Position& offset) {}

	// utility functions

	// 좌표를 인덱스로 변환
	int pos2Offset(const Position& pos) const { return pos.y * dim.x + pos.x; }
	// 인덱스를 좌표로 변환
	Position offset2Pos(int offset) const { return Position{ offset % dim.x, offset / dim.x }; }

	// 좌표 가져오기
	Position getPos() const { return pos; }
	// 좌표 세팅 (Postion 값)
	void setPos(const Position& pos) { this->pos = pos; dirty = true; }
	// 좌표 세팅 (좌표 값)
	void setPos(int x, int y) { setPos(Position{ x, y }); }

	// 활성화 여부 가져오기
	virtual bool isActive() const { return active; }
	// 활성화 세팅
	void setActive(bool flag = true) { this->active = flag; }

	// 가로 가져오기
	int getWidth() const { return dim.x; }
	// 세로 가져오기
	int getHeight() const { return dim.y; }

	// 용량 가져오기
	int getCapacity() const { return capacity; }

	// 부모로 설정하기
	void setParent(GameObject* parent) {
		// 부모 정보에 인자 부모 넣기
		this->parent = parent;
		// 부모 포지션 세팅
		setParentWorldPos(parent ? parent->local2Screen() : Position::zeros);
		// 자식들 포지션 업데이트
		for (auto child : children) child->updatePos(true);
	}

	// 스크린 좌표계에서 지역 좌표계로
	Position screen2local(const Position& screenPos) const {
		Position pos = local2Screen();
		return Position{ screenPos.x - pos.x, screenPos.y - pos.y };
	}

	// 지역 좌표계에서 스크린 좌표계로
	Position local2Screen(const Position& pos) const {
		return { parentWorldPos.x + pos.x, parentWorldPos.y + pos.y };
	}

	// 지역 좌표계에서 스크린 좌표계로
	Position local2Screen() const { return local2Screen(getPos()); }

	// 공간 가져오기
	const Dimension& getDimension() const { return dim; } // why getDimension returns reference value?
	// 공간 세팅
	void setDimension(const Dimension& dim) { this->dim = dim; }

	// 모양 가져오기
	const char* getShape() const { return shape; }
	// 모양 세팅 (const char*)
	void setShape(const char* face) {
		// 처음에 모양이 없다면 전체 빈 공간으로 초기화
		if (face == nullptr || face[0] == '\0') {
			memset(shape, ' ', sizeof(char) * capacity);
			return;
		}
		// 모양 복사
		strncpy(shape, face, min(capacity, strlen(face)));
	}
	// 모양 세팅 (char, int)
	void setShape(char shape, int offset) {
		// 인덱스가 범위 밖일 경우 return
		if (offset < 0 || offset >= capacity) return;
		// 모양을 인덱스에 넣기
		this->shape[offset] = shape;
	}
	// 모양세팅 (char, const Position&)
	void setShape(char shape, const Position& pos) { setShape(shape, pos2Offset(pos)); }

	// 좌표 업데이트
	void updatePos(bool dirty = false) {
		// 변화 플래그 설정
		bool inheritedDirty = dirty;
		// 변화 true로 설정
		if (inheritedDirty == false) {
			if (this->dirty == true)
				inheritedDirty = true;
		}
		// 부모 좌표 세팅
		else {
			setParentWorldPos(parent ? parent->local2Screen() : Position::zeros);
		}
		// 모든 자식 좌표 업데이트 
		for (auto child : children) child->updatePos(inheritedDirty); /* update all children's loc */
		// 업데이트 종료 후 변화 플래그 false
		this->dirty = false; // all its children were updated successfully.
	}

	// 전부 그리기
	void internalDraw() {
		// 비활성화 되어 있다면 그리기 않기
		if (active == false) return;
		// 자기 자신 그리기
		draw();
		// 자식들 전부 그리기
		for (auto child : children) child->internalDraw();
	}
	//  자신 그리기
	virtual void draw() { screen->draw(local2Screen(), shape, dim); }

	// 전부 업데이트
	void internalUpdate() {
		// 비활성화 되어 있다면 업데이트 하기 않기
		if (active == false) return;
		// 자기 자신 업데이트
		update();
		// 자식들 전부 업데이트
		for (auto child : children) child->internalUpdate();
	}
	// 만약 isPaused라면 필요한것만 업데이트되게
	// 자신 업데이트
	virtual void update() {}

};
