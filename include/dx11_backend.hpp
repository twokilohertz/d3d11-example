#include "dxgi.h"
#include <Windows.h>
#include <d3d11.h>
#include <vector>

class DX11Backend
{
    private:
        IDXGIFactory1*          m_factory     = nullptr;
        ID3D11Device*           m_device      = nullptr;
        IDXGISwapChain*         m_swapchain   = nullptr;
        ID3D11DeviceContext*    m_context     = nullptr;
        ID3D11RenderTargetView* m_rtv         = nullptr;
        ID3D11Texture2D*        m_back_buffer = nullptr;

    public:
        DX11Backend(HWND hwnd);
        ~DX11Backend() = default;

    private:
        std::vector<IDXGIAdapter1*> enumerate_adapters();
};
