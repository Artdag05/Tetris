#pragma once
#include <string>
#include <functional>
#include <list>
#include <utility>
#include <cmath>

class Tetramino
{
public:
    Tetramino();
    ~Tetramino();
    
    void setRandomTetra();
    void setTo(std::function<void(int x, int y)> setter);
    std::list<std::pair<int, int>> rotate(const std::list<std::pair<int, int>>& coords);
    
    const char img() const {return 'J';};
    std::string operator[](const int index);

private:
    std::string mTetra;
    std::string mI;
    std::string mL;
    std::string mJ;
    std::string mS;
    std::string mZ;  
    std::string mT;
    std::string mO;

    const int WIDTH;
    const int HEIGHT;
    const char TETRAMINO_IMG;

    int mRandomTetra;
    bool rotatedOnce;
    
    std::pair<int, int> getRotationPoints(const std::list<std::pair<int, int>> &coords);
    std::list<std::pair<int, int>> rotation(
        const std::list<std::pair<int, int>> &coords, 
        std::function<std::pair<int, int>(std::pair<int, int>, int, int)> turn);
};
