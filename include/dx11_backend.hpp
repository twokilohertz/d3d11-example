#include "dxgi.h"
#include <d3d11.h>
#include <vector>
#include <Windows.h>
#include <wrl.h>

namespace wrl = Microsoft::WRL;

class DX11Backend
{
    private:
        wrl::ComPtr<IDXGIFactory1>          m_factory;
        wrl::ComPtr<ID3D11Device>           m_device;
        wrl::ComPtr<IDXGISwapChain>         m_swapchain;
        wrl::ComPtr<ID3D11DeviceContext>    m_context;
        wrl::ComPtr<ID3D11RenderTargetView> m_rtv;
        wrl::ComPtr<ID3D11Texture2D>        m_back_buffer;

    public:
        DX11Backend(HWND hwnd);
        ~DX11Backend() = default;
        void render();

    private:
        std::vector<IDXGIAdapter1*> enumerate_adapters();
};
