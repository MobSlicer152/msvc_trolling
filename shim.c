#include <stdio.h>
#include <windows.h>

#pragma comment(lib, "ntdll.lib")
extern __declspec(dllimport) VOID __stdcall DbgPrint(const char* fmt, ...);

typedef BOOL(__stdcall* PFNINVOKECOMPILERPASS)(int argc, wchar_t* argv[], BOOLEAN x, HMODULE* ui);

#define PRINT(...) DbgPrint(__VA_ARGS__), printf(__VA_ARGS__)

#ifndef PASSNUM
#define PASSNUM 1
#endif

#define STRINGIZE2(x) #x
#define STRINGIZE(x) STRINGIZE2(x)

__declspec(dllexport) BOOL __stdcall InvokeCompilerPassW(int argc, wchar_t** argv, BOOLEAN idk, HMODULE* ui)
{
    HMODULE cx = LoadLibraryExA("C:\\Program Files (x86)\\Microsoft Xbox 360 SDK\\bin\\win32\\c" STRINGIZE(PASSNUM) "_orig.dll", NULL, LOAD_LIBRARY_SEARCH_DEFAULT_DIRS | LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR);

    PFNINVOKECOMPILERPASS pass = (PFNINVOKECOMPILERPASS)GetProcAddress(cx, "_InvokeCompilerPassW@16");

    PRINT("argc = %d, argv = 0x%X, idk = %d, ui = 0x%X, *ui = 0x%X\n", argc, (UINT_PTR)argv, idk, (UINT_PTR)ui, ui ? (UINT_PTR)*ui : 0xDEADBEEF);

    for (int i = 0; i < argc; i++)
    {
        PRINT("argv[%d] = %ls\n", i, argv[i]);
    }

    return pass(argc, argv, idk, ui);
}
