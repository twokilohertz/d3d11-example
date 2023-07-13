#include "gui.hpp"
#include <iostream>

GUI::GUI(HINSTANCE hInstance, int nCmdShow, int32_t width, int32_t height)
{
    m_wndclass               = {};
    m_wndclass.lpfnWndProc   = WindowProc;
    m_wndclass.hInstance     = hInstance;
    m_wndclass.lpszClassName = CLASS_NAME;

    if (RegisterClass(&m_wndclass) == 0)
    {
        return;
    }

    // We pass a "this" pointer so that the WndProc can access object members
    m_hwnd = CreateWindowEx(0, CLASS_NAME, L"D3D11 Example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width,
                            height, nullptr, nullptr, hInstance, this);

    if (m_hwnd == NULL)
    {
        return;
    }

    std::cout << "[GUI] Created application window" << std::endl;

    ShowWindow(m_hwnd, nCmdShow);

    // Initialise D3D11 backend

    m_backend = std::make_unique<DX11Backend>(m_hwnd);
}

GUI::~GUI()
{
    ShowWindow(m_hwnd, SW_HIDE); // Window should already be destroyed anyway
    UnregisterClass(CLASS_NAME, nullptr);
}

void GUI::run()
{
    bool should_quit = false;

    while (!should_quit)
    {
        MSG msg = {};
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT)
            {
                should_quit = true;
            }
        }

        if (should_quit)
        {
            break;
        }

        m_backend->render();
    }
}

HWND GUI::get_window_handle(void)
{
    return m_hwnd;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static GUI* gui_instance = nullptr;

    switch (uMsg)
    {
        case WM_CREATE:
            // When the window is first created we must store the "this" pointer to the GUI object
            gui_instance = reinterpret_cast<GUI*>((reinterpret_cast<CREATESTRUCT*>(lParam))->lpCreateParams);
            break;
        case WM_CLOSE:
            // Destroy the window when the close button is pressed
            if (gui_instance != nullptr)
            {
                HWND window_handle = gui_instance->get_window_handle();
                if (window_handle != nullptr)
                {
                    DestroyWindow(window_handle);
                    return 0;
                }
            }
            break;
        case WM_DESTROY:
            // It's time for our application to leave this Earth
            PostQuitMessage(0);
            return 0;
    }

    // Default window message handler for anything we don't handle
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
