#include <windows.h>

typedef BOOL(__stdcall* PFNINVOKECOMPILERPASS)(int argc, wchar_t* argv[], BOOLEAN x, HMODULE* ui);

BOOL RunFrontend(int argc, wchar_t** argv)
{
	HMODULE mspdbcore = LoadLibraryExA(
		"C:\\Program Files (x86)\\Microsoft Xbox 360 SDK\\bin\\win32\\mspdbcore.dll",
		NULL, LOAD_LIBRARY_SEARCH_DEFAULT_DIRS | LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR);
	HMODULE clui = LoadLibraryExA(
		"C:\\Program Files (x86)\\Microsoft Xbox 360 SDK\\bin\\win32\\1033\\clui.dll",
		NULL, LOAD_LIBRARY_SEARCH_DEFAULT_DIRS | LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR);
	HMODULE c1 = LoadLibraryExA(
		"C:\\Program Files (x86)\\Microsoft Xbox 360 SDK\\bin\\win32\\c1.dll",
		NULL, LOAD_LIBRARY_SEARCH_DEFAULT_DIRS | LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR);

	PFNINVOKECOMPILERPASS pass1 = (PFNINVOKECOMPILERPASS)GetProcAddress(c1, "_InvokeCompilerPassW@16");

	BOOL errored = pass1(argc, argv, TRUE, &clui);

	FreeLibrary(c1);
	FreeLibrary(clui);
	FreeLibrary(mspdbcore);

	return !errored;
}

BOOL RunModernFrontend(int argc, wchar_t** argv)
{
	HMODULE mspdbcoreModern = LoadLibraryExA(
		"C:\\Program Files\\Microsoft Visual "
		"Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.39.33519\\bin\\Hostx86\\x86\\mspdbcore.dll",
		NULL, LOAD_LIBRARY_SEARCH_DEFAULT_DIRS | LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR);
	HMODULE cluiModern = LoadLibraryExA(
		"C:\\Program Files\\Microsoft Visual "
		"Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.39.33519\\bin\\Hostx86\\x86\\1033\\clui.dll",
		NULL, LOAD_LIBRARY_SEARCH_DEFAULT_DIRS | LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR);
	HMODULE c1 = LoadLibraryExA(
		"C:\\Program Files\\Microsoft Visual "
		"Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.39.33519\\bin\\Hostx86\\x86\\c1.dll",
		NULL, LOAD_LIBRARY_SEARCH_DEFAULT_DIRS | LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR);

	PFNINVOKECOMPILERPASS pass1 = (PFNINVOKECOMPILERPASS)GetProcAddress(c1, "_InvokeCompilerPassW@16");

	BOOL errored = pass1(argc, argv, TRUE, &cluiModern);

	FreeLibrary(c1);
	FreeLibrary(cluiModern);
	FreeLibrary(mspdbcoreModern);

	return !errored;
}

BOOL RunBackend(int argc, wchar_t** argv)
{
	HMODULE clui = LoadLibraryExA(
		"C:\\Program Files (x86)\\Microsoft Xbox 360 SDK\\bin\\win32\\1033\\clui.dll", NULL,
		LOAD_LIBRARY_SEARCH_DEFAULT_DIRS | LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR);
	HMODULE mspdbcore =
		LoadLibraryExA("C:\\Program Files (x86)\\Microsoft Xbox 360 SDK\\bin\\win32\\mspdbcore.dll", NULL, LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR);
	HMODULE mspdbxx =
		LoadLibraryExA("C:\\Program Files (x86)\\Microsoft Xbox 360 SDK\\bin\\win32\\mspdbxx.dll", NULL, LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR);
	HMODULE c2 = LoadLibraryExA("C:\\Program Files (x86)\\Microsoft Xbox 360 SDK\\bin\\win32\\c2.dll", NULL, LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR);

	PFNINVOKECOMPILERPASS pass2 = (PFNINVOKECOMPILERPASS)GetProcAddress(c2, "_InvokeCompilerPassW@16");

	BOOL errored = pass2(argc, argv, TRUE, &clui);

	FreeLibrary(c2);
	FreeLibrary(clui);
	FreeLibrary(mspdbxx);
	FreeLibrary(mspdbcore);

	return !errored;
}

int wmain(int argc, wchar_t** argv)
{
	wchar_t* c1Argv[] = {
		L"fuckyoumicrosoft", L"-il", L"goober_", L"-typedil", L"-Fotest_test.obj", L"-pc", L"\\:/", L"-W", L"1", L"-fpfast", L"-Ze",
		L"-D_MSC_EXTENSIONS", L"-Zp8",
		// L"-ZB64",
		L"-D_INTEGRAL_MAX_BITS=64", L"-Gs", L"-Gd", L"-D_M_PPC=5401", L"-D_M_PPCBE", L"-D_XBOX_VER=200", L"-D__VMX128_SUPPORTED=1",
		L"-D__XBOX_CPU_DD2=1", L"-Ot", L"-clrNoPureCRT", L"-Fdvc100_goober.pdb", L"-f", L"..\\test_test.c", L"-D_MSC_VER=1600",
		L"-D_MSC_FULL_VER=160011887", L"-D_MSC_BUILD=0", L"-D_WIN32", L"-D_MT"};
	int c1Argc = sizeof(c1Argv) / sizeof(c1Argv[0]);
	wchar_t* c1ModernArgv[] = {
		L"fuckyoumicrosoft", L"-il", L"goobermodern_", L"-typedil", L"-Fotest_test.obj", L"-pc", L"\\:/", L"-W", L"1", L"-fpfast", L"-Ze",
		L"-D_MSC_EXTENSIONS", L"-Zp8",
		// L"-ZB64",
		L"-D_INTEGRAL_MAX_BITS=64", L"-Gs", L"-Gd", L"-D_M_PPC=5401", L"-D_M_PPCBE", L"-D_XBOX_VER=200", L"-D__VMX128_SUPPORTED=1",
		L"-D__XBOX_CPU_DD2=1", L"-Ot", L"-clrNoPureCRT", L"-Fdvc100_goober.pdb", L"-f", L"..\\test_test.c", L"-D_MSC_VER=1600",
		L"-D_MSC_FULL_VER=160011887", L"-D_MSC_BUILD=0", L"-D_WIN32", L"-D_MT"};
	int c1ModernArgc = sizeof(c1ModernArgv) / sizeof(c1ModernArgv[0]);
	wchar_t* c2Argv[] = {L"fuckyoumicrosoft", L"-il",   L"goober_", L"-typedil", L"-Fotest_test.obj",    L"-W", L"1",          L"-Gs4096", L"-G604",
						 L"-QVMX128",         L"-QDD2", L"-Ob0",    L"-MT",      L"-Fdvc100_goober.pdb", L"-f", L"..\\test_test.c"};
	int c2Argc = sizeof(c2Argv) / sizeof(c2Argv[0]);

	//RunFrontend(c1Argc, c1Argv);
	//RunModernFrontend(c1ModernArgc, c1ModernArgv);
	//if (RunFrontend(c1Argc, c1Argv))
	//{
		RunBackend(c2Argc, c2Argv);
	//}

	TerminateProcess(GetCurrentProcess(), 0);
}
