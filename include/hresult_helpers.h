#include <stdio.h>
#include <Windows.h>

#define HR_ABORT_IF_FAILED(hr) \
    if (hr != S_OK)            \
    {                          \
        abort();               \
    }

#define HR_ALERT_IF_FAILED(hr)                                                                            \
    if (hr != S_OK)                                                                                       \
    {                                                                                                     \
        wchar_t message[MAX_PATH] = {0};                                                                  \
        swprintf_s(message, sizeof(message), L"Fatal error on line: %d in file %hs", __LINE__, __FILE__); \
        MessageBox(NULL, message, L"Fatal error", MB_OK | MB_ICONERROR);                                  \
        abort();                                                                                          \
    }
