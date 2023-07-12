#include <Windows.h>
#include <dx11_backend.hpp>
#include <memory>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

const wchar_t CLASS_NAME[] = L"D3D11 Example";

class GUI
{
    private:
        WNDCLASS                     m_wndclass = {};
        HWND                         m_hwnd     = NULL;
        std::unique_ptr<DX11Backend> m_backend;

    public:
        GUI(HINSTANCE hInstance, int nCmdShow);
        ~GUI();

        void run();
        HWND get_window_handle(void);
};
