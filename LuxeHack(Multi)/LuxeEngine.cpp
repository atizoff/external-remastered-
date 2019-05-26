#include "Define/Stdafx.h"
#include "Protect/XorStr.h"
#include "Settings/Settings.h"
#include "Process\Process.h"
#include "Library\CryRevers.h"
#include "Form/CreateForm.h"
#include <winhttp.h>
#include <strsafe.h>
#pragma comment (lib, "urlmon.lib")
#pragma comment (lib, "wininet.lib")
#pragma comment (lib, "winhttp.lib")

///////////////////////
DWORD ProcessId = 0;
std::wstring GameClassName = XorStringW(L"CryENGINE");
///////////////////////

bool IsRunGame(const wchar_t* WindowClassName)
{
	if (::FindWindowW(WindowClassName, NULL)) 
		return true;
	else
	{
		Driver().Unload();
		::TerminateProcess(GetCurrentProcess(), EXIT_SUCCESS);
	}
}

bool GetProcessId(_Out_ LPDWORD lpdwProcessId)
{
	HWND hWnd = ::FindWindowW(GameClassName.c_str(), NULL);
	if (hWnd != NULL)
	{
		::GetWindowThreadProcessId(hWnd, lpdwProcessId);
		return true;
	}
	return false;
}

void CreateEngine()
{
	while (1)
	{
		if (::FindWindowW(GameClassName.c_str(), NULL))
		{
			if (!ProcessId)
			{
				GetProcessId(&ProcessId);
				SetProcessId(ProcessId);
			}

			IsRunGame(GameClassName.c_str());
			create_Engine();
			Sleep(1);
		}
	}
}

BOOL FileExists(CONST CHAR *fname)
{
	return access(fname, 0) != -1;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	if (!FindWindowW(GameClassName.c_str(), NULL))
	{
		/////////////////////////////////////////////
		Driver().Unload();
		Driver().DropDriver();
		if (!Driver().IsLoaded())
			Driver().Loaded();
		if (!Driver().IsLoaded())
			return 0;
		/////////////////////////////////////////////
		HWND hwnd;
		MSG Msg;
		szClassName = XorStringW(L"uefhwhfae9wfu9u3fiqfhq34.") + RandomANString(1) + RandomANString(1) + RandomANString(1);
		WNDCLASSEXW form =
		{
			sizeof(WNDCLASSEXW),
			CS_CLASSDC,
			WndProc,
			0L,
			0L,
			GetModuleHandle(NULL),
			NULL,
			NULL,
			(HBRUSH)COLOR_WINDOW,
			NULL,
			szClassName.c_str(),
			NULL
		};
		RegisterClassExW(&form);
		hwndMain = CreateWindowExW(0, szClassName.c_str(), XorStringW(L""), StyleForm, (GetSystemMetrics(SM_CXSCREEN) - 1024) / 2, (GetSystemMetrics(SM_CYSCREEN) - 576) / 2, 340, 310, 0, 0, hInstance, NULL);
		ShowWindow(hwndMain, nCmdShow);
		UpdateWindow(hwndMain);
		hwndTab = CreateWindowExW(0, XorStringW(L"SysTabControl32"), L"", WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE, 10, 10, 300, 250, hwndMain, NULL, hInstance, NULL);
		///////////
		TCITEM tie;
		tie.mask = TCIF_TEXT;
		tie.pszText = "Вх";
		TabCtrl_InsertItem(hwndTab, 0, &tie);
		///////////
		tie.mask = TCIF_TEXT;
		tie.pszText = "Аим";
		TabCtrl_InsertItem(hwndTab, 1, &tie);
		///////////
		tie.mask = TCIF_TEXT;
		tie.pszText = "Оружие";
		TabCtrl_InsertItem(hwndTab, 2, &tie);
		///////////
		tie.mask = TCIF_TEXT;
		tie.pszText = "Игрок";
		TabCtrl_InsertItem(hwndTab, 3, &tie);
		///////////
		MakeWindows();
		CloseWindows();
		TabCtrl_SetCurSel(hwndTab, 0);
		SHWindow(0);
		ShowWindow(hwndTab, SW_SHOW);
		UpdateWindow(hwndTab);
		Create_Thread(CreateEngine);
		/////////////////////////////////////////////
		while (GetMessage(&Msg, NULL, 0, 0) > 0)
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
		return Msg.wParam;
	}
	else
	{
		MessageBoxW(0, XorStringW(L"Запустите чит, а потом игру!"), XorStringW(L""), MB_OK);
		::TerminateProcess(GetCurrentProcess(), EXIT_SUCCESS);
	}
}

