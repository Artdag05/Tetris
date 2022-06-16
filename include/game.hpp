#pragma once

#include "window.hpp"
#include "tetramino.hpp"
#include "field.hpp"
#include "timer.hpp"

#include <list>
#include <utility>
#include <conio.h>
#include <functional>

class Game
{
public:
    Game();
    ~Game();
    
    void run();

private:
    Window mWindow;
    Field mField;
    Tetramino mSprite;
    Timer mTimer;
    short mShift;
    bool mSpriteOnBottom;
    std::function<void(int, int)> mFieldArea;

    void drawOnWindow(); 
    void setSprite();
    void moveSpriteDown();
    void moveSpriteLeft();
    void moveSpriteRight();
    void rotateSprite();
    void spriteHorMove();
    bool canSpriteHorMove();
    bool canSpriteRotate(const std::list<std::pair<int, int>>& coords);
    bool isCollideFromBelow();

    std::list<std::pair<int, int>> getSpriteCoords();
};