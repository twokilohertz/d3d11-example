#include "dx11_backend.hpp"
#include "hresult_helpers.h"
#include <cstdint>
#include <iostream>

DX11Backend::DX11Backend(HWND hwnd)
{
    std::cout << "[DX11Backend] Initialising D3D11 backend" << std::endl;

    if (CreateDXGIFactory1(IID_PPV_ARGS(m_factory.GetAddressOf())) != S_OK)
    {
        abort();
    }

    auto dxgi_adapters = enumerate_adapters();

    // Create device & swap chain

    DXGI_SWAP_CHAIN_DESC swap_chain_desc = {};
    ZeroMemory(&swap_chain_desc, sizeof(swap_chain_desc));

    swap_chain_desc.BufferCount                        = 1;
    swap_chain_desc.BufferDesc.Width                   = 0;
    swap_chain_desc.BufferDesc.Height                  = 0;
    swap_chain_desc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
    swap_chain_desc.BufferDesc.RefreshRate.Numerator   = 60;
    swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
    swap_chain_desc.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swap_chain_desc.OutputWindow                       = hwnd;
    swap_chain_desc.SampleDesc.Count                   = 1; // All D3D11 renderers support at least 4X MSAA
    swap_chain_desc.SampleDesc.Quality                 = 0;
    swap_chain_desc.Windowed                           = TRUE;
    swap_chain_desc.SwapEffect                         = DXGI_SWAP_EFFECT_DISCARD;
    swap_chain_desc.Flags                              = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    const D3D_FEATURE_LEVEL requested_feature_levels = D3D_FEATURE_LEVEL_11_0;
    int                     num_feature_levels       = 1;

    UINT create_device_flags = 0;
#if !defined(NDEBUG)
    create_device_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    HR_ALERT_IF_FAILED(D3D11CreateDeviceAndSwapChain(dxgi_adapters[0], D3D_DRIVER_TYPE_UNKNOWN, nullptr,
                                                     create_device_flags, &requested_feature_levels, num_feature_levels,
                                                     D3D11_SDK_VERSION, &swap_chain_desc, m_swapchain.GetAddressOf(),
                                                     m_device.GetAddressOf(), nullptr, m_context.GetAddressOf()))

    std::cout << "[DX11Backend] Created device & swap chain" << std::endl;

    // TODO: Check MSAA support

    HR_ALERT_IF_FAILED(m_swapchain->GetBuffer(0, IID_PPV_ARGS(m_back_buffer.GetAddressOf())))

    std::cout << "[DX11Backend] Got the swap-chain's back buffer" << std::endl;

    HR_ALERT_IF_FAILED(m_device->CreateRenderTargetView(m_back_buffer.Get(), nullptr, m_rtv.GetAddressOf()))
    m_back_buffer->Release();

    std::cout << "[DX11Backend] Created render target view" << std::endl;

    // // Set-up the viewport in the window

    // RECT client_area = {};
    // if (!GetClientRect(hwnd, &client_area))
    // {
    //     abort();
    // }

    // D3D11_VIEWPORT viewport = {};
    // viewport.TopLeftX       = 0.0F;
    // viewport.TopLeftY       = 0.0F;
    // viewport.Width          = (client_area.right - client_area.left);
    // viewport.Height         = (client_area.bottom - client_area.top);
    // viewport.MinDepth       = 0.0F;
    // viewport.MaxDepth       = 1.0F;

    // m_context->RSSetViewports(1, &viewport);
}

void DX11Backend::render()
{
    m_context->OMSetRenderTargets(1, m_rtv.GetAddressOf(), nullptr);

    const float red[4] = {1.0F, 0.0F, 0.0F, 1.0F};

    m_context->ClearRenderTargetView(m_rtv.Get(), red);

    m_swapchain->Present(1, 0);
}

std::vector<IDXGIAdapter1*> DX11Backend::enumerate_adapters()
{
    IDXGIAdapter1*              adapter = nullptr;
    std::vector<IDXGIAdapter1*> dxgi_adapters;

    for (uint32_t i = 0; m_factory->EnumAdapters1(i, &adapter) != DXGI_ERROR_NOT_FOUND; i++)
    {
        dxgi_adapters.push_back(adapter);
    }

    return dxgi_adapters;
}
