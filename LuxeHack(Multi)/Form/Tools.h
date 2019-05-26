#pragma once
HWND hwndMain;
HWND hwndTab;
HWND Esp_Table1;
HWND Esp_Table2;
HWND Esp_Table3;
HWND Aim_Table1;
HWND Aim_Table2;
HWND Aim_Table3;
HWND Aim_Table4;
HWND Aim_Table5;
HWND Weapon_Table1;
HWND Weapon_Table2;
HWND Weapon_Table3;
HWND Weapon_Table4;
HWND Weapon_Table5;
HWND Weapon_Table6;
HWND Weapon_Table7;
HWND Player_Table1;
HWND Player_Table2;
HWND Player_Table3;
HWND Player_Table4;
HWND Player_Table5;
HWND Player_Table6;
HWND Player_Table7;
HINSTANCE hinst;
#define Create_Thread(Function) CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Function, 0, 0, 0));

void set_int(int &Var, HWND HwnD)
{
	if (Var == 1 && Var != 0)
	{
		Var = 0;
	}
	else

		if (Var == 0)
		{
			Var = 1;
		}
}

void set_int_text(int &Var, HWND HwnD, LPWSTR textOFF, LPWSTR textOn)
{
	if (Var == 1 && Var != 0)
	{
		Var = 0;
		SetWindowTextW(HwnD, textOFF);
	}
	else

		if (Var == 0)
		{
			Var = 1;
			SetWindowTextW(HwnD, textOn);
		}
}

void set_bool(bool &Var, HWND HwnD)
{
	if (Var == 1 && Var != 0)
	{
		Var = 0;
	}
	else

		if (Var == 0)
		{
			Var = 1;
		}
}

void set_bool_text(bool &Var, HWND HwnD, LPWSTR textOFF, LPWSTR textOn)
{
	if (Var == 1 && Var != 0)
	{
		Var = 0;
		SetWindowTextW(HwnD, textOFF);
	}
	else

		if (Var == 0)
		{
			Var = 1;
			SetWindowTextW(HwnD, textOn);
		}
}

void textform(int x, int y, HWND Hwnd, LPWSTR text)
{
	SetWindowTextW(Hwnd, text);
}

void OpenWindows(HWND Table)
{
	ShowWindow(Table, SW_SHOW);
	SetFocus(Table);
}

void CloseWindows()
{
	///////////
	ShowWindow(Esp_Table1, SW_HIDE);
	ShowWindow(Esp_Table2, SW_HIDE);
	///////////

	///////////
	ShowWindow(Aim_Table1, SW_HIDE);
	ShowWindow(Aim_Table2, SW_HIDE);
	ShowWindow(Aim_Table3, SW_HIDE);
	ShowWindow(Aim_Table4, SW_HIDE);
	//ShowWindow(Aim_Table5, SW_HIDE);
	///////////

	///////////
	ShowWindow(Weapon_Table1, SW_HIDE);
	ShowWindow(Weapon_Table2, SW_HIDE);
	ShowWindow(Weapon_Table3, SW_HIDE);
	ShowWindow(Weapon_Table4, SW_HIDE);
	ShowWindow(Weapon_Table5, SW_HIDE);
	ShowWindow(Weapon_Table6, SW_HIDE);
	ShowWindow(Weapon_Table7, SW_HIDE);
	///////////

	///////////
	ShowWindow(Player_Table1, SW_HIDE);
	ShowWindow(Player_Table2, SW_HIDE);
	ShowWindow(Player_Table3, SW_HIDE);
	ShowWindow(Player_Table4, SW_HIDE);
	ShowWindow(Player_Table5, SW_HIDE);
	ShowWindow(Player_Table6, SW_HIDE);
	ShowWindow(Player_Table7, SW_HIDE);
	///////////
}

void SHWindow(int num)
{
	if (num == 0)
	{
		OpenWindows(Esp_Table1);
		OpenWindows(Esp_Table2);
	}
	if (num == 1)
	{
		OpenWindows(Aim_Table1);
		OpenWindows(Aim_Table2);
		OpenWindows(Aim_Table3);
		OpenWindows(Aim_Table4);
		//OpenWindows(Aim_Table5);
	}
	if (num == 2)
	{
		OpenWindows(Weapon_Table1);
		OpenWindows(Weapon_Table2);
		OpenWindows(Weapon_Table3);
		OpenWindows(Weapon_Table4);
		OpenWindows(Weapon_Table5);
		OpenWindows(Weapon_Table6);
		OpenWindows(Weapon_Table7);
	}
	if (num == 3)
	{
		OpenWindows(Player_Table1);
		OpenWindows(Player_Table2);
		OpenWindows(Player_Table3);
		OpenWindows(Player_Table4);
		OpenWindows(Player_Table5);
		OpenWindows(Player_Table6);
		OpenWindows(Player_Table7);
	}
}

static std::wstring RandomANString(int length)
{
	static const wchar_t alphabet[] = L"ABCDEFGHIJKLMNOPQRSTUVWXYZbcdefghijklmnopqrstuvwxyz";
	static std::random_device rd;
	static std::uniform_int_distribution<> dist(0, ARRAYSIZE(alphabet) - 2);
	static std::uniform_int_distribution<> dist_len(5, 15);
	std::wstring result;


	if (length == 0)
		length = dist_len(rd);

	for (int i = 0; i < length; i++)
		result.push_back(alphabet[dist(rd)]);

	return result;
}

RECT wRect;
std::wstring szClassName;
std::wstring szWindowName;

#define StyleButton    (WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|BS_FLAT)
#define StyleCheckBox  (WS_CHILD|WS_VISIBLE|BS_AUTOCHECKBOX|BS_FLAT)
#define StyleForm      WS_OVERLAPPED | WS_MINIMIZEBOX | WS_CAPTION | WS_SYSMENU | WS_VISIBLE
#define POS(y) 15+30*y
