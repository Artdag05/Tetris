#pragma once
#include "tetramino.hpp"

class Field
{
public:
    Field(int width = 17, int height = 23);  // 12 22
    ~Field();
    
    void draw();
    void checkLine();
    void clear(const std::list<std::pair<int, int>>& coords);
    void setSpriteOnField(const char SPRITE_IMG); 
    
    const int getWidth() const {return WIDTH;};
    const int getHeight() const {return HEIGHT;};
    const char bgImage() const {return BG_IMAGE;};
    const char brdrImage() const {return BRDR_IMAGE;};
    const char fieldSpriteImg() const {return FIELD_SPRITE_IMG;};
    
    char* operator[](const int index);

private:
    char** mField;
    const int WIDTH;
    const int HEIGHT;
    const char BG_IMAGE;
    const char BRDR_IMAGE;
    const char FIELD_SPRITE_IMG;

    bool isLineFull();
    int fullLineIndex;
};