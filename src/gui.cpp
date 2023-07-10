#include "gui.hpp"

GUI::GUI(HINSTANCE hInstance, int nCmdShow)
{
    m_wndclass = {};
    m_wndclass.lpfnWndProc = WindowProc;
    m_wndclass.hInstance = hInstance;
    m_wndclass.lpszClassName = CLASS_NAME;

    if (RegisterClass(&m_wndclass) == 0)
    {
        return;
    }

    m_hwnd =
        CreateWindowEx(0, CLASS_NAME, L"D3D11 Example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
                       CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    if (m_hwnd == NULL)
    {
        return;
    }

    ShowWindow(m_hwnd, nCmdShow);
}

GUI::~GUI()
{
    ShowWindow(m_hwnd, SW_HIDE);
    CloseHandle(m_hwnd);
    UnregisterClass(CLASS_NAME, NULL);
}

void GUI::run()
{
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
