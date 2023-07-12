#include "gui.hpp"
#include <Windows.h>
#include <cstdint>
#include <iostream>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
#if !defined(NDEBUG)
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    // freopen("CONERR$", "w", stderr); - doesn't work? Creates an actual "CONERR$" file instead
    std::cout << "[DEBUG] Allocated console for logging" << std::endl;
#endif

    GUI gui = GUI(hInstance, nCmdShow);
    gui.run();

#if !defined(NDEBUG)
    std::cout << "[DEBUG] Freeing console" << std::endl;
    FreeConsole();
#endif

    return 0;
}
