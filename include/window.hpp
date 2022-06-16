#pragma once
#include <windows.h>
#include <iostream>

class Window
{
public:
    Window(short width = 16, short height = 22);  // 11 21
    ~Window();
    void setChar(int x, int y, wchar_t ch);
    void render();
    void setBorders();
    void clear();

private:
    const SHORT WIDTH;
    const SHORT HEIGHT;    

    HANDLE mConsole;
    HANDLE mConsoleIn;

    CHAR_INFO* mConsoleBuffer;
    COORD mDwBufSize;
    COORD mDwBufCoord;
    SMALL_RECT windowSize;
};