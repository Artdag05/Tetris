#include "tetramino.hpp"

#include <cstdlib>
#include <ctime>

/* 
    rotation formula from point:
    y = (x - xRotPoint) * sin(alpha) + (y - yRotPoint) * cos(alpha) + yRotPoint
    x = (x - xRotPoint) * cos(alpha) - (y - yRotPoint) * sin(alpha) + xRotPoint
    in this game alpha == 90 degree angle, which means that cos(90) == 0 and sin(90) == 1
    formula can be shortened to:
    y =  (x - xRotPoint) + yRotPoint
    x = -(y - yRotPoint) + xRotPoint
*/
    
Tetramino::Tetramino() : 
    WIDTH(4),
    HEIGHT(4),
    TETRAMINO_IMG('J'),
    mRandomTetra(0),
    rotatedOnce(false)
{
    mI.append("....");
    mI.append(".J..");
    mI.append(".J..");
    mI.append(".J..");

    mL.append("....");
    mL.append(".J..");
    mL.append(".J..");
    mL.append(".JJ.");

    mJ.append("....");
    mJ.append("..J.");
    mJ.append("..J.");
    mJ.append(".JJ.");

    mS.append("....");
    mS.append(".J..");
    mS.append(".JJ.");
    mS.append("..J.");
    
    mZ.append("....");
    mZ.append("..J.");
    mZ.append(".JJ.");
    mZ.append(".J..");

    mT.append("....");
    mT.append("..J.");
    mT.append(".JJJ");
    mT.append("....");

    mO.append("....");
    mO.append(".JJ.");
    mO.append(".JJ.");
    mO.append("....");

    srand(static_cast<unsigned int>(time(0)));
}

Tetramino::~Tetramino()
{
}

void Tetramino::setRandomTetra()
{
    enum TETRAMINOS {I, L, J, S, Z, T, O, TETRAMINOS_NUM};
    mRandomTetra = rand() % TETRAMINOS_NUM;
    switch (mRandomTetra)
    {
    case I:
        mTetra = mI;
        break;
    case L:
        mTetra = mL;
        break;
    case J:
        mTetra = mJ;
        break;
    case S:
        mTetra = mS;
        break;
    case Z:
        mTetra = mZ;
        break;
    case T:
        mTetra = mT;
        break;
    case O:
        mTetra = mO;
        break;
    }
}

void Tetramino::setTo(std::function<void(int x, int y)> setter)
{
    setRandomTetra();
    int x, y;
    size_t index = 0;
    while (((index = mTetra.find(TETRAMINO_IMG, index)) != std::string::npos) && (index < mTetra.size()))
    {
        x = int(index % WIDTH);
        y = int(index / WIDTH);
        setter(x, y);
        ++index;
    }
}

std::pair<int, int> Tetramino::getRotationPoints(const std::list<std::pair<int, int>> &coords)
{
    int totalX = 0;
    int totalY = 0;

    for (const auto& coord : coords)
    {
        totalY += coord.first;
        totalX += coord.second;
    }

    int elementsNum = coords.size();
    return {round((double)totalY / elementsNum), round((double)totalX / elementsNum)};
}

std::list<std::pair<int, int>> Tetramino::rotation(
    const std::list<std::pair<int, int>> &coords, 
    std::function<std::pair<int, int>(std::pair<int, int>, int, int)> turn)
{
    unsigned int newX, newY;
    std::list<std::pair<int, int>> newCoords;
    int yRotPoint = getRotationPoints(coords).first;
    int xRotPoint = getRotationPoints(coords).second;

    for (const auto& coord : coords)
    {
        newCoords.push_back(turn(coord, xRotPoint, yRotPoint));
    }

    return newCoords;
}

std::list<std::pair<int, int>> Tetramino::rotate(const std::list<std::pair<int, int>>& coords)
{
    auto clockWiseRotation = [](std::pair<int, int> posyx, int x, int y) -> std::pair<int, int>{
        return std::make_pair(
            abs((posyx.second - x) + y), 
            abs(-(posyx.first - y) + x)
        );
    };

    auto counterClockWiseRotation = [](std::pair<int, int> posyx, int x, int y) -> std::pair<int, int>{
        return std::make_pair(
            abs(-(posyx.second - x) + y), 
            abs((posyx.first - y) + x)
        );
    };

    enum TETRAMINOS {I, L, J, S, Z, T, O, TETRAMINOS_NUM};
    switch (mRandomTetra)
    {
    case I:
    case S:
    case Z:
        rotatedOnce = !rotatedOnce;
        if (rotatedOnce)
        {
           return rotation(coords, clockWiseRotation);
        }
        else
        {
           return rotation(coords, counterClockWiseRotation);
        }
    case L:
    case J:
    case T:
        return rotation(coords, clockWiseRotation);
    case O:
        break;
    }
    return coords;
}

std::string Tetramino::operator[](const int index)
{
    int startPos = index * WIDTH;
    return mTetra.substr(startPos, WIDTH);
}