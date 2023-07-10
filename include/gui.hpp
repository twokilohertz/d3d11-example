#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

const wchar_t CLASS_NAME[] = L"D3D11 Example";

class GUI
{
  private:
    WNDCLASS m_wndclass = {};
    HWND m_hwnd = NULL;

  public:
    GUI(HINSTANCE hInstance, int nCmdShow);
    ~GUI();
    void run();
};
