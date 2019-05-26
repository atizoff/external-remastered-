#pragma once
#include "../Define/Stdafx.h"
#include "Tools.h"

void MakeWindows()
{
	int X = 27, W = 250;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	Esp_Table1 = CreateWindow(XorString("button"), XorString("Силуэты"), StyleCheckBox, X, POS(1), W, 25, hwndMain, (HMENU)1, hinst, NULL);
	Esp_Table2 = CreateWindow(XorString("button"), XorString("Мины"), StyleCheckBox, X, POS(2), W, 25, hwndMain, (HMENU)2, hinst, NULL);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	Aim_Table1 = CreateWindow(XorString("button"), XorString("Сайлент"), StyleCheckBox, X, POS(1), W, 25, hwndMain, (HMENU)3, hinst, NULL);
	Aim_Table2 = CreateWindow(XorString("button"), XorString("Тело [Голова]"), StyleButton, X, POS(2), W, 25, hwndMain, (HMENU)4, hinst, NULL);
	Aim_Table3 = CreateWindow(XorString("button"), XorString("Аим на турели"), StyleCheckBox, X, POS(3), W, 25, hwndMain, (HMENU)5, hinst, NULL);
	Aim_Table4 = CreateWindow(XorString("button"), XorString("Выключить аим [Capslock]"), StyleCheckBox, X, POS(4), W, 25, hwndMain, (HMENU)6, hinst, NULL);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	Weapon_Table1 = CreateWindow(XorString("button"), XorString("Нет отдачи"), StyleCheckBox, X, POS(1), W, 25, hwndMain, (HMENU)7, hinst, NULL);
	Weapon_Table2 = CreateWindow(XorString("button"), XorString("Нет разброса"), StyleCheckBox, X, POS(2), W, 25, hwndMain, (HMENU)8, hinst, NULL);
	Weapon_Table3 = CreateWindow(XorString("button"), XorString("Антизатвор [BAN!!!]"), StyleCheckBox, X, POS(3), W, 25, hwndMain, (HMENU)9, hinst, NULL);
	Weapon_Table4 = CreateWindow(XorString("button"), XorString("Антипокачивание"), StyleCheckBox, X, POS(4), W, 25, hwndMain, (HMENU)10, hinst, NULL);
	Weapon_Table5 = CreateWindow(XorString("button"), XorString("Бесконечные патроны"), StyleCheckBox, X, POS(5), W, 25, hwndMain, (HMENU)20, hinst, NULL);
	Weapon_Table6 = CreateWindow(XorString("button"), XorString("Дамаг [x5]"), StyleCheckBox, X, POS(6), W, 25, hwndMain, (HMENU)21, hinst, NULL);
	Weapon_Table7 = CreateWindow(XorString("button"), XorString("Скорострельность"), StyleCheckBox, X, POS(7), W, 25, hwndMain, (HMENU)23, hinst, NULL);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	Player_Table1 = CreateWindow(XorString("button"), XorString("Длинный подкат"), StyleCheckBox, X, POS(1), W, 25, hwndMain, (HMENU)12, hinst, NULL);
	Player_Table2 = CreateWindow(XorString("button"), XorString("Поворот ботов"), StyleCheckBox, X, POS(2), W, 25, hwndMain, (HMENU)14, hinst, NULL);
	Player_Table3 = CreateWindow(XorString("button"), XorString("Anti-AFK"), StyleCheckBox, X, POS(3), W, 25, hwndMain, (HMENU)16, hinst, NULL);
	Player_Table4 = CreateWindow(XorString("button"), XorString("Автошот [не работает]"), StyleCheckBox, X, POS(4), W, 25, hwndMain, (HMENU)17, hinst, NULL);
	Player_Table5 = CreateWindow(XorString("button"), XorString("Скрытие с радара"), StyleCheckBox, X, POS(5), W, 25, hwndMain, (HMENU)18, hinst, NULL);
	Player_Table6 = CreateWindow(XorString("button"), XorString("Подсад в одного [не работает]"), StyleCheckBox, X, POS(6), W, 25, hwndMain, (HMENU)21, hinst, NULL);
	Player_Table7 = CreateWindow(XorString("button"), XorString("Призрак [K]"), StyleCheckBox, X, POS(7), W, 25, hwndMain, (HMENU)24, hinst, NULL);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		Driver().Unload();
		Beep(1000, 800);
		TerminateProcess(GetCurrentProcess(), EXIT_SUCCESS);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_NOTIFY:
		switch (((LPNMHDR)lParam)->code)
		{
		case TCN_SELCHANGE:
		{
			int iPage = TabCtrl_GetCurSel(hwndTab);
			CloseWindows();
			SHWindow(iPage);
			break;
		}
		}
		break;
	case WM_COMMAND:
	{
		switch (wParam)
		{
		case 1:
			set_bool(Settings::ESP::EspSilhouettes, Esp_Table1);
			break;
		case 2:
			set_bool(Settings::ESP::EspMines, Esp_Table2);
			break;
		case 3:
			set_bool(Settings::Aimbot::enabled, Aim_Table1);
			break;
		case 4:
			set_int_text(Settings::Aimbot::bones, Aim_Table2, XorStringW(L"Тело [Голова]"), XorStringW(L"Тело [Грудь]"));
			break;
		case 5:
			set_bool(Settings::Aimbot::turets, Aim_Table3);
			break;
		case 6:
			set_bool(Settings::Aimbot::capslock, Aim_Table4);
			break;
		case 7:
			set_bool(Settings::Weapone::norecoil, Weapon_Table1);
			break;
		case 8:
			set_bool(Settings::Weapone::nospread, Weapon_Table2);
			break;
		case 9:
			set_bool(Settings::Weapone::noshoters, Weapon_Table3);
			break;
		case 10:
			set_bool(Settings::Weapone::nosway, Weapon_Table4);
			break;
		case 12:
			set_bool(Settings::Player::longslide, Player_Table1);
			break;
		case 14:
			set_bool(Settings::Player::rotateshl, Player_Table2);
			break;
		case 16:
			set_bool(Settings::Player::afk, Player_Table3);
			break;
		case 17:
			set_bool(Settings::Player::autoshoot, Player_Table4);
			break;
		case 19:
			set_bool(Settings::Aimbot::as, Aim_Table5);
			break;
		case 20:
			set_bool(Settings::Weapone::pistol, Weapon_Table5);
			break;
		case 21:
			set_bool(Settings::Weapone::dmg, Weapon_Table6);
			break;
		case 22:
			set_bool(Settings::Player::climb, Player_Table6);
			break;
		case 23:
			set_bool(Settings::Weapone::speedshot, Weapon_Table7);
			break;
		case 24:
			set_bool(Settings::Player::ghost, Player_Table7);
			break;
		}
	}
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

