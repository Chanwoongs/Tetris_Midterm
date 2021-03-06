#pragma once

#include "Position.h"
#include "Block.h"
#include "Score.h"
#include "Map.h"
#include "Confirmation.h"

class TetrisGame : public Panel
{
    bool        isCompleted;
    Score*      score;  // cache
    Map*        map;    // cache
    Block*      block;
    Confirmation* confirmation;

public:
    TetrisGame()
        // 큰 정사각형 게임 틀
        : Panel("", Position{ 1, 1 }, 77, 30, "UI", nullptr),
        isCompleted(false), score(nullptr), confirmation(nullptr)
    {
        // 맵 공간 만듦
        map = new Map{ Position{5,5}, 10, 20, "map", this };

        // 맵 안에 블럭 만듦
        block = new Block{ " \xdb \xdb\xdb\xdb",
            Position{5,0},
            Dimension{3, 2},
            "block",
            map
        }; // make a block to be a child of map object
        
        // 다음 블럭 패널
        new Panel{ " Next", Position{25, 5}, 10, 5, "UI", this };

        // 스코어
        score = new Score{ Position{4, 2},
            // 스코어 패널 만듦
            new Panel{ " Score", Position{25, 20}, 10, 5, "UI", this}
        }; // create a ScorePanel and make a "score" its child.
        // 스코어 세팅
        map->setScore(score);
        // 블럭을 맵에 세팅
        block->setMap(map);
        // 퍼즈 패널 생성
        confirmation = new Confirmation(Position{ 30, 12 }, 20, 5, "UI", this);
    }

    // 게임 오버
    bool isGameOver() const { return isCompleted; }

    // 업데이트
    void update() override // 선조 클래스의 업데이트를 나의 업데이트로 덮어 씌운다
    {
        // 블럭이 위를 뚫으면
        if (map->isDone()) 
        {
            // 게임 오버
            isCompleted = true;
            return;
        }
        // ESC 키를 누르면 confirmation 생성
        if (input->getKey(VK_ESCAPE))
        {
            // 일시중지 창 생성
            confirmation->setActive(true);
            // 게임 일시중지
            setIsPaused(true);
        }    
        // 블럭이 비활성화 된다면
        if (!block->isActive())
        {
            // 블럭 초기화
            block->initializeBlock();
            // 블럭 활성화
            block->setActive(true);
        }
    }
};
