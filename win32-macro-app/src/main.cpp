#include <windows.h>
#include <string>
#include "include/macro_manager.h"
#include "include/script_runner.h"

#define IDC_EDIT_SCRIPT 101
#define IDC_BUTTON_RUN  102
#define IDC_BUTTON_COORDS 103

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND hEditScript = NULL;
    static HWND hButtonRun = NULL;

    switch (uMsg) {
        case WM_CREATE: {
            // Get ScriptRunner pointer from CREATESTRUCT
            ScriptRunner* scriptRunnerPtr = (ScriptRunner*)((LPCREATESTRUCT)lParam)->lpCreateParams;
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)scriptRunnerPtr);

            // Create Edit control (textarea)
            hEditScript = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL,
                WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
                10, 10, 400, 100,
                hwnd, (HMENU)IDC_EDIT_SCRIPT, GetModuleHandle(NULL), NULL);

            // Pre-fill with demo script
            const char* demoScript = "move 300 300\nclick left";
            SetWindowText(hEditScript, demoScript);

            // Create Run button
            hButtonRun = CreateWindow("BUTTON", "Run",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                420, 10, 80, 30,
                hwnd, (HMENU)IDC_BUTTON_RUN, GetModuleHandle(NULL), NULL);

            // Create Show Coordinates button
            CreateWindow("BUTTON", "Show Coordinates",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD,
                420, 50, 80, 30,
                hwnd, (HMENU)IDC_BUTTON_COORDS, GetModuleHandle(NULL), NULL);
            break;
        }
        case WM_COMMAND: {
            if (LOWORD(wParam) == IDC_BUTTON_RUN) {
                // Get script from Edit control
                char buffer[1024] = {0};
                GetWindowText(hEditScript, buffer, sizeof(buffer));
                ScriptRunner* scriptRunnerPtr = (ScriptRunner*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
                if (scriptRunnerPtr) {
                    scriptRunnerPtr->executeScript(std::string(buffer));
                }
            } else if (LOWORD(wParam) == IDC_BUTTON_COORDS) {
                // Get mouse position
                POINT pt;
                GetCursorPos(&pt);
                // Get current script
                char buffer[1024] = {0};
                GetWindowText(hEditScript, buffer, sizeof(buffer));
                std::string script(buffer);
                // Append move command
                script += "\nmove " + std::to_string(pt.x) + " " + std::to_string(pt.y);
                SetWindowText(hEditScript, script.c_str());
            }
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_PAINT:
            // Handle painting here if needed
            break;
        // Handle other messages here
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nShowCmd) {
    const char CLASS_NAME[] = "MacroAppWindowClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Initialize MacroManager and ScriptRunner
    MacroManager macroManager;
    ScriptRunner scriptRunner(macroManager);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Win32 Macro Application",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 540, 160,
        NULL,
        NULL,
        hInstance,
        &scriptRunner // Pass pointer to WM_CREATE
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nShowCmd);

    // Main message loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}