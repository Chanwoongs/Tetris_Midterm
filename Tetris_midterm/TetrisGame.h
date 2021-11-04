#pragma once

#include "Position.h"
#include "Block.h"
#include "Score.h"
#include "Map.h"

class TetrisGame : public Panel
{
    bool        isCompleted;
    Score*      score;  // cache
    Map*        map;    // cache

public:
    TetrisGame()
        // 큰 정사각형 게임 틀
        : Panel("", Position{ 1, 1 }, 77, 30, nullptr),
        isCompleted(false), score(nullptr)
    {
        // 맵 공간 만듬
        map = new Map{ Position{5,5}, 10, 20, this };

        // 맵 안에 블럭 만듬
        auto block = new Block{ " \xdb \xdb\xdb\xdb",
            Position{5,0},
            Dimension{3, 2},
            map
        }; // make a block to be a child of map object
        
        // 다음 블럭 패널
        new Panel{ " Next", Position{25, 5}, 10, 5, this };

        // 스코어
        score = new Score{ Position{4, 2},
            // 스코어 패널 만듬
            new Panel{ " Score", Position{25, 20}, 10, 5, this }
        }; // create a ScorePanel and make a "score" its child.
        // 스코어 세팅
        map->setScore(score);
        // 블럭을 맵에 세팅
        block->setMap(map);
    }

    // 게임 오버
    bool isGameOver() const { return isCompleted; }

    // 업데이트
    void update() override 
    {
        // 블럭이 위를 뚫으면
        if (map->isDone()) {
            isCompleted = true;
            return;
        }
        // ESC 키를 누르면
        if (input->getKey(VK_ESCAPE))
            isCompleted = true;
    }
};
