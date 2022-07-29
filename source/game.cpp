#include "game.hpp"

/* 
   On Field play area width starts with index 1, because index 0 == border
   and width ends with index WIDTH - 1, because index WIDTH == border.
   Height play area ends with HEIGHT - 1, because index HEIGHT == border.
    
   In all program first going Y coord, then X coord;
*/


#define ESC 27
#define SPACE 32
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

Game::Game() :
    mShift(0),
    mSpriteOnBottom(0),
    mFieldArea(nullptr)
{
    setSprite();
}

Game::~Game()
{

}

void Game::setSprite()
{
    mFieldArea = [&](int x, int y){
        mField[y - 1][(mField.getWidth()/2) - x] = mSprite[y][x];
    };

    mSprite.setTo(mFieldArea);
}

bool Game::canSpriteHorMove()
{
    bool makeMove = true;
    for (int h = 0; h < mField.getHeight() - 1; ++h)
    {
        for (int w = 1; w < mField.getWidth() - 1; ++w)
        {
            if (mField[h][w] == mSprite.img())
            {
                if ((w + mShift <= 0) || (w + mShift >= mField.getWidth() - 1)|| 
                    (mField[h][w - 1] == mField.fieldSpriteImg() || mField[h][w + 1] == mField.fieldSpriteImg()))
                {
                    makeMove = false;
                }
            }
        }
    }
    return makeMove;
}

std::list<std::pair<int, int>> Game::getSpriteCoords()
{
    std::list<std::pair<int, int>> coords;
    for (int h = 0; h < mField.getHeight() - 1; ++h)
    {
        for (int w = 1; w < mField.getWidth() - 1; ++w)
        {
            if (mField[h][w] == mSprite.img())
            {
                coords.push_back(std::make_pair(h, w));
            }
        }
    }

    return coords;
}

void Game::spriteHorMove()
{
    if (!canSpriteHorMove())
    {
        return;
    }

    auto spriteCoords = getSpriteCoords();
    if (!spriteCoords.empty())
    {
        mField.clear(spriteCoords);
        for(const auto& coord : spriteCoords)
        {
            mField[coord.first][coord.second + mShift] = mSprite.img();
        }

        mShift = 0;
    }
}

void Game::moveSpriteRight()
{
    mShift = 1;
    spriteHorMove();
}

void Game::moveSpriteLeft()
{
    mShift = -1;
    spriteHorMove();
}

void Game::moveSpriteDown()
{
    if (mSpriteOnBottom)
    {
        return;
    }

    if (isCollideFromBelow())
    {
        mSpriteOnBottom = true;
        mField.setSpriteOnField(mSprite.img());
    }
    
    auto spriteCoords = getSpriteCoords();
    if (!spriteCoords.empty())
    {
        mField.clear(spriteCoords);
        for (const auto& coord : spriteCoords)
        {
            mField[coord.first + 1][coord.second] = mSprite.img();
        }
    }
}

bool Game::canSpriteRotate(const std::list<std::pair<int, int>>& coords)
{
    bool canRotate = true;
    for (const auto& coord : coords)
    {
        if (mField[coord.first][coord.second] == mField.fieldSpriteImg() ||
            (coord.second <= 0 || coord.second >= mField.getWidth() - 1) || 
            (coord.first >= mField.getHeight() - 1))
        {
            return canRotate = false;
        }
    }
    return canRotate;
}

void Game::rotateSprite()
{
    auto spriteCoords = getSpriteCoords();
    if (spriteCoords.empty())
    {
        return;
    }
    
    auto spriteRotatedCoords = mSprite.rotate(spriteCoords);
    if (!canSpriteRotate(spriteRotatedCoords))
    {
        return;
    }

    mField.clear(spriteCoords);
    for (const auto& coord : spriteRotatedCoords)
    {
        mField[coord.first][coord.second] = mSprite.img();
    }
}

bool Game::isCollideFromBelow()
{
    bool collision = false;
    int bottom = mField.getHeight() - 2;
    for (int h = 0; h < mField.getHeight() - 1; ++h)
    {
        for (int w = 1; w < mField.getWidth() - 1; ++w)
        {
            if ((mField[h][w] == mSprite.img() && mField[h + 1][w] == mField.fieldSpriteImg()) ||
                (h == bottom && mField[bottom][w] == mSprite.img()))
            {
               return collision = true;
            }
        }
    }
    return collision;
}

void Game::drawOnWindow()
{
    for (int h = 0; h < mField.getHeight(); ++h)
    {
        for (int w = 1; w < mField.getWidth(); ++w)
        {
            if (mField[h][w] == mSprite.img() || mField[h][w] == mField.fieldSpriteImg())
            {
                mWindow.setChar(w, h, 0x08);
            }

        }
    }

}
// resolve FPS issue  !!!!!!!!!!!!!
void Game::run()
{
    mWindow.setBorders();
    mTimer.start();
    bool endGame = false;

    // game loop
    while(!endGame)
    {
        // keyboard events
        if(_kbhit())
        {
            mWindow.clear();
            char btnCode = getch();
            switch (btnCode)
            {
            case UP:
                break;
            case DOWN:
                break;
            case LEFT:
                moveSpriteLeft();
                break;
            case RIGHT:
                moveSpriteRight();
                break;
            case SPACE:
                rotateSprite();
                break;
            case ESC:
                endGame = true;
                break;
            }
        }

        // draw
        if (mTimer.elapsed() >= 0.5)
        {
            mWindow.render();
            mWindow.clear();
            moveSpriteDown();
            mTimer.reset();
            mField.checkLine();
        }

        if (mSpriteOnBottom)
        {
            setSprite();
            mSpriteOnBottom = false;
        }
        drawOnWindow();
    }
}