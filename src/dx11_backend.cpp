#include "dx11_backend.hpp"
#include <cstdint>
#include <iostream>

DX11Backend::DX11Backend(HWND hwnd)
{
    std::cout << "Initialising D3D11 backend" << std::endl;

    if (CreateDXGIFactory1(IID_PPV_ARGS(&m_factory)) != S_OK)
    {
        return;
    }

    auto dxgi_adapters = enumerate_adapters();

    DXGI_SWAP_CHAIN_DESC swap_chain_desc = {};
    ZeroMemory(&swap_chain_desc, sizeof(swap_chain_desc));

    swap_chain_desc.BufferCount = 1;
    swap_chain_desc.BufferDesc.Width = 0;
    swap_chain_desc.BufferDesc.Height = 0;
    swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swap_chain_desc.BufferDesc.RefreshRate.Numerator = 60;
    swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
    swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swap_chain_desc.OutputWindow = hwnd;
    swap_chain_desc.SampleDesc.Count = 1;
    swap_chain_desc.SampleDesc.Quality = 0;
    swap_chain_desc.Windowed = TRUE;

    const D3D_FEATURE_LEVEL requested_feature_levels = D3D_FEATURE_LEVEL_11_0;
    int num_feature_levels = 1;

    if (D3D11CreateDeviceAndSwapChain(dxgi_adapters[0], D3D_DRIVER_TYPE_UNKNOWN, NULL, 0,
                                      &requested_feature_levels, num_feature_levels,
                                      D3D11_SDK_VERSION, &swap_chain_desc, &m_swapchain, &m_device,
                                      NULL, &m_context) != S_OK)
    {
        return;
    }

    std::cout << "Created device & swap chain" << std::endl;

    DebugBreak();
}

// DX11Backend::~DX11Backend()
// {
// }

std::vector<IDXGIAdapter1 *> DX11Backend::enumerate_adapters()
{
    IDXGIAdapter1 *adapter = nullptr;
    std::vector<IDXGIAdapter1 *> dxgi_adapters;

    for (uint32_t i = 0; m_factory->EnumAdapters1(i, &adapter) != DXGI_ERROR_NOT_FOUND; i++)
    {
        dxgi_adapters.push_back(adapter);
    }

    return dxgi_adapters;
}
