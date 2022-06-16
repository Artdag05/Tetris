#include "field.hpp"

Field::Field(int width, int height) :  
    WIDTH(width), 
    HEIGHT(height), 
    BG_IMAGE(' '), 
    BRDR_IMAGE('#'),
    FIELD_SPRITE_IMG('L'),
    fullLineIndex(0)
{
    // create field
    mField = new char*[HEIGHT];
    for (int h = 0; h < HEIGHT; ++h)
    {
        mField[h] = new char[WIDTH];
    }

    // fill field
    for (int h = 0; h < HEIGHT; ++h)
    {
        for (int w = 0; w < WIDTH; ++w)
        {
            mField[h][w] = (w == 0 || w == WIDTH - 1 || h == HEIGHT - 1) ? BRDR_IMAGE : BG_IMAGE;
        }
    }
}

Field::~Field()
{
    for (int h = 0; h < HEIGHT; ++h)
    {
        delete [] mField[h];
    } 
}

void Field::clear(const std::list<std::pair<int, int>>& coords)
{
    for (const auto& coord: coords)
    {
        mField[coord.first][coord.second] = bgImage();
    }
}

void Field::setSpriteOnField(const char SPRITE_IMG)
{
    std::list<std::pair<int, int>> coords;
    for(int h = 0; h < HEIGHT - 1; ++h)
    {
        for (int w = 1; w < WIDTH - 1; ++w)
        {
            if (mField[h][w] == SPRITE_IMG)
            {
                coords.push_back(std::make_pair(h, w));
            }
        }
    }
    
    clear(coords);

   for (const auto& coord : coords)
   {
       mField[coord.first][coord.second] = FIELD_SPRITE_IMG;
   }
}

bool Field::isLineFull()
{
    bool isFull; fullLineIndex = 0;
    for (int lineIndex = HEIGHT - 2; lineIndex > 0; --lineIndex)
    {
        for (int w = WIDTH - 2; w > 0; --w)
        {
            if (mField[lineIndex][w] != FIELD_SPRITE_IMG)
            {
                isFull = false;
                break;
            }
            isFull = true;

        }
        if (isFull) {fullLineIndex = lineIndex; return isFull;}
    }
    return isFull;
}

void Field::checkLine()
{
    if (!isLineFull())
    {
        return;
    }

    for (int w = 1; w < WIDTH - 1; ++w)
    {
        mField[fullLineIndex][w] = BG_IMAGE;
    }

    std::list<std::pair<int, int>> coords;

    for (int h = fullLineIndex - 1; h > 0; --h)
    {
        for (int w = WIDTH - 2; w > 0; --w)
        {
            if (mField[h][w] == FIELD_SPRITE_IMG)
            {
                mField[h][w] = BG_IMAGE;
                coords.push_back(std::make_pair(h, w));
            }
        }
    }

    for (const auto& coord : coords)
    {
        mField[coord.first + 1][coord.second] = FIELD_SPRITE_IMG;
    }

}

char* Field::operator[](const int index)
{
    return mField[index];
}