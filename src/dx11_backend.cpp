#include "dx11_backend.hpp"
#include <cstdint>
#include <iostream>

DX11Backend::DX11Backend()
{
    std::cout << "Initialising D3D11 backend" << std::endl;

    if (CreateDXGIFactory1(IID_PPV_ARGS(&m_factory)) != S_OK)
    {
        return;
    }

    auto dxgi_adapters = enumerate_adapters();

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
