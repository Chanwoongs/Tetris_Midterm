#pragma once

#include "Position.h"
#include "Map.h"
#include "Button.h"

class MapEditor : public Panel
{
    bool        isCompleted;
    Map*        map;    // cache
    Button*     saveBtn;
    Button*     exitBtn;
    ofstream    fout;

public:
    MapEditor()
        // 큰 정사각형 게임 틀
        : Panel("", Position{ 1, 1 }, 77, 30, "UI", nullptr),
        isCompleted(false)
    {
        // 파일 생성
        fout.open("C:\\Users\\방찬웅\\Desktop\\Project\\OOP\\Tetris_midterm\\CustomMap.txt");
        // 예외 처리
        if (!fout)
        {
            cout << "Can not open file!\n";
        }

        // 맵 공간 만듦
        map = new Map{ Position{5,5}, 10, 20, "map", this };
        // Save 버튼 생성
        saveBtn = new Button("Save", Position{ 20, 5 }, 8, 3, "UI", this);
        // Exit 버튼 생성
        exitBtn = new Button("Exit", Position{ 20, 10 }, 8, 3, "UI", this);
        
    }

    // 에디팅 끝내기
    bool isDone() const { return isCompleted; }

    // 업데이트
    void update() override // 선조 클래스의 업데이트를 나의 업데이트로 덮어 씌운다
    {
        Position mapPos = local2Screen(map->getPos());
        if (input->getMouseButtonDown(0) &&
            input->getMousePosition().x > mapPos.x && input->getMousePosition().x < mapPos.x + map->getWidth() + 1 &&
            input->getMousePosition().y > mapPos.y && input->getMousePosition().y < mapPos.y + map->getHeight() + 1)
        {
            map->editMap(input->getMousePosition());
        }
        if (saveBtn->onClick())
        {
            // Save를 누른다면 파일에 커스터마이징한 맵을 저장
            fout << map->getMap() << endl;
            // 파일 닫기
            fout.close();
            // 프로그램 종료 요청
            isCompleted = true;
        }
        if (exitBtn->onClick())
        {
            // Exit를 누른다면 빈 맵을 파일에 저장
            fout << map->getEmptyMap() << endl;
            // 파일 닫기
            fout.close();
            // 프로그램 종료 요청
            isCompleted = true;
        }
    }
};
