#include "gui.hpp"
#include <Windows.h>
#include <cstdint>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    GUI gui = GUI(hInstance, nCmdShow);
    gui.run();

    return 0;
}
