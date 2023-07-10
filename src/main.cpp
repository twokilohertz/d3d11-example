#include <Windows.h>
#include <cstdint>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"D3D11 Example";

    WNDCLASS wndclass = {};
    wndclass.lpfnWndProc = WindowProc;
    wndclass.hInstance = hInstance;
    wndclass.lpszClassName = CLASS_NAME;

    if (RegisterClass(&wndclass) == 0)
    {
        return -1;
    }

    HWND hwnd =
        CreateWindowEx(0, CLASS_NAME, L"D3D11 Example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
                       CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    if (hwnd == NULL)
    {
        return -1;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
