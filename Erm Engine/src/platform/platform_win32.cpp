#include "platform.h"

#if EPLATFORM_WINDOWS
#include<windows.h>
#include<windowsx.h>


typedef struct internalState {
    HINSTANCE  hInstance;
    HWND hwnd;

} internalState;

static f64 clockFrequency;
static LARGE_INTEGER startTime;

LRESULT CALLBACK win32_process_message(HWND hwnd, u32 msg, WPARAM wParam, LPARAM lParam);

b8 Platform::PlatformStartup(platformState* platState, const char* appName, i32 x, i32 y, i32 width, i32 height)
{
    platState->internalState = PlatformAllocate(sizeof(internalState), false);
    internalState* state = (internalState*)platState->internalState;


    state->hInstance = GetModuleHandleA(0);

    HICON icon = LoadIcon(state->hInstance, IDI_APPLICATION);
    WNDCLASSA winClass;
    memset(&winClass, 0, sizeof(winClass));
    winClass.style = CS_DBLCLKS;
    winClass.lpfnWndProc = win32_process_message;
    winClass.cbClsExtra = 0;//
    winClass.cbWndExtra = 0;//extra bytes to allocate
    winClass.hInstance = state->hInstance;
    winClass.hIcon = icon;
    winClass.hCursor = LoadCursor(nullptr, IDC_ARROW);// manage cursor manually
    winClass.hbrBackground = nullptr; // transparency
    winClass.lpszClassName = "erm_engine_window_class";

    if (!RegisterClassA(&winClass)) {
        MessageBoxA(0, "window registration failed", "error", MB_ICONEXCLAMATION | MB_OK);
        return false;

    }

    u32 clientX = x;
    u32 clientY = y;
    u32 clientWidth = width;
    u32 clientHeight = height;

    u32 windowX = clientX;
    u32 windowY = clientY;
    u32 windowWidth = clientWidth;
    u32 windowHeight = clientHeight;

    u32 windowStyle = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;
    u32 windowExStyle = WS_EX_APPWINDOW;

    windowStyle |= WS_MAXIMIZEBOX;
    windowStyle |= WS_MINIMIZEBOX;
    windowStyle |= WS_THICKFRAME;

    RECT borderRect = { 0,0,0,0 };
    AdjustWindowRectEx(&borderRect, windowStyle, 0, windowExStyle);

    windowX += borderRect.left;
    windowY += borderRect.top;

    windowWidth += borderRect.right - borderRect.left;
    windowHeight += borderRect.bottom - borderRect.top;

    HWND handle = CreateWindowExA(windowExStyle, "erm_engine_window_class", appName, windowStyle,
        windowX, windowY, windowWidth, windowHeight, 0, 0, state->hInstance, 0);

    if (handle == 0) {
        MessageBoxA(nullptr, "window creation failed!!!!!!", "ERROR!!!!", MB_ICONEXCLAMATION | MB_OK);

        EFATAL("Window creation fucked up man!");
        return false;
    }
    else {
        state->hwnd = handle;
    }

    b32 shouldActivate = true; // if window should not activate would be false
    i32 showWindowCommandFlags = shouldActivate ? SW_SHOW : SW_SHOWNOACTIVATE;
    // if initially minimized, use SW_MINIMIZE : SW_SHOWMINNOACTIVE;
    // if initially mazimized, use SW_SHOWMAXIMIZED : SW_MAXIMIZE;
    ShowWindow(state->hwnd, showWindowCommandFlags);

    //clock setup
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    clockFrequency = 1.0f / (f64)frequency.QuadPart;
    QueryPerformanceCounter(&startTime);

    return true;

}

void Platform::PlatformShutdown(platformState* platState) {
    internalState* state = (internalState*)platState->internalState;

    if (state->hwnd) {
        DestroyWindow(state->hwnd);
        state->hwnd = 0;
    }

}

b8 Platform::PlatformPumpMessages(platformState* platState) {
    MSG message;
    while (PeekMessageA(&message, nullptr, 0, 0, PM_REMOVE)) {
        TranslateMessage(&message);
        DispatchMessageA(&message);
    }
    return true;
}

void* Platform::PlatformAllocate(u64 size, b8 aligned) {
    // allocated a chunk of memory for use
    return operator new(size);
}


void Platform::PlatformFree(void* block, b8 aligned) {
    // frees that object
   operator delete(block);

}

void* Platform::PlatformZeroMemory(void* block, u64 size) {
    //i know memset is not good
    return memset(block, 0, size);
}

void* Platform::PlatformCopyMemory(void* destination, const void* source, u64 size) {
    //i know memcpy is not good
    return memcpy(destination, source, size);
}

void* Platform::PlatformSetMemory(void* destination, i32 value, u64 size) {
    //i know memset is not good
    return memset(destination, value, size);
}

void Platform::PlatformConsoleWrite(const char* message, u8 color) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    // array contains the fatal error warn info debug trace levels
    static u8 levels[6] = { 64,4,6,2,1,8 };
    SetConsoleTextAttribute(consoleHandle, levels[color]);

    OutputDebugStringA(message);
    u64 length = strlen(message);
    LPDWORD numWritten = 0;
    WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), message, (DWORD)length, numWritten, 0);

}

void Platform::PlatformConsoleWriteError(const char* message, u8 color) {
    HANDLE consoleHandle = GetStdHandle(STD_ERROR_HANDLE);
    // array contains the fatal error warn info debug trace levels
    static u8 levels[6] = { 64,4,6,2,1,8 };
    SetConsoleTextAttribute(consoleHandle, levels[color]);

    OutputDebugStringA(message);
    u64 length = strlen(message);
    LPDWORD numWritten = 0;
    WriteConsoleA(GetStdHandle(STD_ERROR_HANDLE), message, (DWORD)length, numWritten, 0);
}

f64 Platform::PlatformGetAbsoluteTime() {
    LARGE_INTEGER currTime;
    QueryPerformanceCounter(&currTime);
    return (f64)currTime.QuadPart * clockFrequency;
}

void Platform::PlatformSleep(u64 miliseconds) {
    Sleep(miliseconds);
}

f64 PlatformGetAbsoluteTime() {
    LARGE_INTEGER currTime;
    QueryPerformanceCounter(&currTime);
    return (f64)currTime.QuadPart * clockFrequency;
}



LRESULT CALLBACK win32_process_message(HWND hwnd, u32 msg, WPARAM wParam, LPARAM lParam) {
    switch (msg)
    {
    case WM_ERASEBKGND:
        // tell the OS that rasing will be handled by the application
        return 1;
    case WM_CLOSE:
        // when event system is up
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_SIZE: {
        // RECT r;
        //GetClientRect(hwnd, &r);
        // u32 width = r.right - r.left;
        // u32 height = r.bottom - r.top;
        // 
        //  Fire an event for window resize
    }break;
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
    case WM_KEYUP:
    case WM_SYSKEYUP: {
        //b8 pressed = (msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN);
        // moar event shi
    }break;
    case WM_MOUSEMOVE: {
        //TODO mouse move
        //i32 xPos = GET_X_LPARAM(lParam);
        //i32 yPos = GET_Y_LPARAM(lParam);


    }break;
    case WM_MOUSEWHEEL: {
        //i32 zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
        //if (zDelta != 0) {
            //zDelta = (zDelta < 0) ? -1 : 1;
        //}

    }break;
    case WM_LBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_MBUTTONUP:
    case WM_RBUTTONUP: {
        //b8 pressed = msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN || msg == WM_MBUTTONDOWN;
        // TODO: input processing.
    } break;
    }

    return DefWindowProcA(hwnd, msg, wParam, lParam);
}

#endif

