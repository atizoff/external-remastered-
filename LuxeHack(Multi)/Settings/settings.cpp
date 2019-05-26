#include "../Define/Stdafx.h"
#include "settings.h"
#include "../Protect/XorStr.h"

namespace Settings
{
	namespace Weapone
	{
		bool norecoil = false;
		bool nospread = false;
		bool noshoters = false;
		bool nosway    = false;
		bool pistol = false;
		bool dmg = false;
		bool speedshot = false;
	}

	namespace Player
	{
		bool longslide = false;
		bool rotateshl = false;
		bool afk = false;
		bool autoshoot = false;
		bool radar = false;
		bool climb = false;
		bool ghost = false;
	}

	namespace Aimbot
	{
		bool enabled = false;
		bool turets  = false;
		bool capslock = false;
		int bones = 0;
		bool as = false;
	}

	namespace ESP
	{
		bool EspSilhouettes = false;
		bool EspMines = false;
	}
}





