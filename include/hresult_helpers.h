#if !defined(HRESULT_HELPERS_H)
#define HRESULT_HELPERS_H

#include <stdio.h>
#include <Windows.h>

#define HR_ABORT_IF_FAILED(hr) \
    if (FAILED(hr))            \
    {                          \
        abort();               \
    }

#define HR_ALERT_IF_FAILED(hr)                                                                            \
    if (FAILED(hr))                                                                                       \
    {                                                                                                     \
        wchar_t message[MAX_PATH] = {0};                                                                  \
        swprintf_s(message, sizeof(message), L"Fatal error on line: %d in file %hs", __LINE__, __FILE__); \
        MessageBox(NULL, message, L"Fatal error", MB_OK | MB_ICONERROR);                                  \
        abort();                                                                                          \
    }

#endif
