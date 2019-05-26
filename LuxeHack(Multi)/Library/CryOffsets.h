#pragma once
#include "CryTools.h"

//////////////////
/*
UPDATE CHEAT DATE: 17.05.2019
GAME: WARFACE RU
*/
//////////////////


// PlayerDummy or ObserverPlayer [+ GameFrameWork + Game]
/*
if ( !dword_1B4D79C )
{
dword_1B4D79C = (*(int (**)(void))(*(_DWORD *)dword_1B53138 + 56))(); [dword_1B4D79C] - GameFrameWork [dword_1B53138] - Game
v12 = (*(int (**)(void))(*(_DWORD *)dword_1B53138 + 56))(); [dword_1B53138] - Game
dword_1B4D7A0 = (*(int (__thiscall **)(int))(*(_DWORD *)v12 + 0x78))(v12);
dword_1B4D798 = (*(int (**)(void))(*(_DWORD *)dword_1B4D79C + 104))(); [dword_1B4D798] - IItemSystem
}

ray: 384 / 4 = 86
srwi: 136 / 4 = 34
*/

enum GameData : int32
{
	dwGlobalAdress = 0x1926580,
	dwBaseRender = 0x1B4A50C,
	dwBaseGameCVar = 0x1B53128, // g_victoryCondition
	dwBaseGameFrameWork = 0x1B4D79C,
	dwBaseIItemSystem = 0x1B4D798,
	dwBaseProjection = 0x1B45724, //74 14 56 81 C7 AC 00 00 00 B9 10 00 00 00 BE
	dwBaseMatrix = dwBaseProjection + 0x40, // BE 4C 55 B3 01
};

enum IRenderData : int32
{
	GetCameraI = 0x1044,
	GetWidthI = 0x7018,
	GetHeightI = 0x701C, //85 C0 74 08 8B 10 57 8B  C8 FF 52 18 80 BE 2C 70
};

enum IEntityData : int32
{
	GetEntityIdI = 0x4,
	GetEntityClassI = 0x28,
	GetFlagsI = 0x4,
	GetRawIdI = 0x14,
	GetWorldTMI = 0x30,
	GetNameI = 0xB8,
	GetClassNameI = 0x8,
	GetRotationI = 0x78
};

enum IActorData : int32
{
	GetEntityI = 0x8,
	GetActorIdI = 0x10,
	GetTeamIdI = 0x344, // (gameParams) 55 8B EC 81 EC 9C 01 ??  ?? 53 56 FF 75 08 8B D9 or 84 C0 74 09 6A 01 8B CE (Revive) if ( v17 ) (*(void(__thiscall **)(int, int, _DWORD, int))(*(_DWORD *)v17 + 292))(v17, v3, *(_DWORD *)(v3 + 0x348), a3);
	GetPlayerI = 0x964, // 55 8B EC 8B 89 ? ? ? ? 8B 45 08 F3 0F 7E 81
	SetScaleI = 0xC0,
	claymore_detector_radiusI = 0xB00,
	climb = 0x4,
	hide_radar = 0xB98,
	leanAngleI = 0xB2C,
	WeaponIdI = leanAngleI + 0x4,
	slideDistanceMultI = 0xC3C,
	GetClassIdI = 0x3A0 // 85 C0 74 0A 8B 10 8B C8  FF 52 20 C2 04 00 33 C0 mov eax, [ecx+3A4h] retn
};

enum IWeaponData : int32
{
	IWeaponSpecificI = 0x4,
	SetFiringPosI = 0x10,
	IWeaponExtraI = 0x24,
	IWeaponCryptI = 0x30,
	IWeaponAmmoI = 0x34,
	ShutterI = 0x8A,
	GetWeaponStanceI = 0x70,
	SpeedFireId = 0x4F,
	DamageI = 0x8
	/*SetAmmo_Id = 0x5,
	SetDamage_Id = 0x1B,
	SetRangeFire_Id = 0x1C,
	SetRangeKnife_Id = 0x3E,
	SetRecoil_Id = 0x41,
	SetSpread_Id = 0x5E,
	SetShutter_Id = 0x10,
	SpeedWeapon_Id = 0x34,
	SpeedKnife_Id = 0x52,
	SpeedKnifeL_Id = 0x36,
	SpeedKnifeR_Id = 0x37,
	SpeedFire_Id = 0x4F,
	SpeedReload_Id = 0x47,
	SpeedChange_Id = 0x20,
	SetZoom_Id = 0x6B,
	SetSwayX_Id = 0x64,
	SetSwayY_Id = 0x65
	*/
};

enum ICVarData : int32
{
	i_pelletsDispI = 0x118,
	g_victoryConditionI = 0x57C,
	g_ingame_afk_timeoutI = 0x6F8,
	g_gameroom_afk_timeoutI = 0x6F4,
	g_anti_cheat_memscan_thread_delayI = 0xA28,
	g_anti_cheat_memscan_logI = 0xA2C,
	g_anti_cheat_memscan_dump_patternsI = 0xA30
};

class IRender
{
private:
	template<class cData> cData GetValue(int32 dwOffset)
	{
		return Read<cData>((int32)this + dwOffset);
	}
	template<class cData> void SetValue(int32 dwOffset, cData Value)
	{
		Write<cData>(((int32)this + dwOffset), Value);
	}
	template<class cData> cData TGetValue(int32 dwOffset)
	{
		return Read<cData>(dwOffset);
	}
	template<class cData> void TSetValue(int32 dwOffset, cData Value)
	{
		Write<cData>((dwOffset), Value);
	}
public:
	static IRender* Singleton()
	{
		return Read<IRender*>(GameData::dwBaseRender);
	}

	Vec3 GetCamera()
	{
		return GetValue<Vec3>(IRenderData::GetCameraI);
	}

	int32 GetWidth()
	{
		return GetValue<int32>(IRenderData::GetWidthI);
	}

	int32 GetHeight()
	{
		return GetValue<int32>(IRenderData::GetHeightI);
	}

	bool ProjectToScreen(int32*vp, f32 ptx, f32 pty, f32 ptz, f32* sx, f32* sy, f32* sz)
	{
		Vec3 vOut, vIn;
		vIn.x = ptx;
		vIn.y = pty;
		vIn.z = ptz;
		int32 v[4] = { vp[0], vp[1], vp[2], vp[3] };
		Matrix44 mIdent;
		mIdent.SetIdentity();
		Matrix44 View = TGetValue<Matrix44>(GameData::dwBaseProjection);
		Matrix44 Projection = TGetValue<Matrix44>(GameData::dwBaseMatrix);
		if (__mathVec3Project(&vOut, &vIn, v, &Projection, &View, &mIdent))
		{
			*sx = vOut.x* 100.0f / (f32)v[2];
			*sy = vOut.y* 100.0f / (f32)v[3];
			*sz = vOut.z;
			return true;
		}
		return false;
	}

	void DrawAABB(AABB aabb)
	{
		int32 v2 = (int32)this + 0xC * (GetValue<int32>(0xE08) + 0x93A);
		int32 v0 = TGetValue<int32>(v2);
		int32 v3 = TGetValue<int32>(v2 + 0x4);

		if (!v0 || !v3) return;

		if (v0 == v3)
		{
			TSetValue(v0, aabb);
			TSetValue(v2 + 0x4, v0 + 0x18);
		}
	}
};

class IActorSystem
{
private:
	template<class cData> cData GetValue(int32 dwOffset)
	{
		return Read<cData>((int32)this + dwOffset);
	}
	template<class cData> void SetValue(int32 dwOffset, cData Value)
	{
		Write<cData>(((int32)this + dwOffset), Value);
	}
	template<class cData> cData TGetValue(int32 dwOffset)
	{
		return Read<cData>(dwOffset);
	}
	template<class cData> void TSetValue(int32 dwOffset, cData Value)
	{
		Write<cData>((dwOffset), Value);
	}
public:
	IActor* GetActor(int32 EntityId)
	{
		int32 v7 = NULL;
		int32 v3 = GetValue<int32>(0x1C);
		int32 v4 = v3;
		int32 v5 = TGetValue<int32>(v3 + 0x4);

		while (!TGetValue<BYTE>(v5 + 0xD))
		{
			if (TGetValue<int32>(v5 + 0x10) >= EntityId)
			{
				v4 = v5;
				v5 = TGetValue<int32>(v5);
			}
			else
			{
				v5 = TGetValue<int32>(v5 + 0x8);
			}
		}

		if (v4 == v3 || (v7 = v4, EntityId < TGetValue<int32>(v4 + 0x10)))
			v7 = v3;

		if (v7 != v3) { return TGetValue<IActor*>((int32)v7 + 0x14); }
		return NULL;
	}

	void CreateActorIterator()
	{
		int32 v3, v5, j, i;
		int32 m_actors_size = GetValue<int32>(0x20);
		v3 = TGetValue<int32>(GetValue<int32>(0x1C));
		while (m_actors_size)
		{
			m_actors_size--;
			m_actors.emplace(TGetValue<int32>(v3 + 0x10), 
			TGetValue<IActor*>(v3 + 0x14));
			if (!TGetValue<BYTE>(v3 + 0xD))
			{
				v5 = TGetValue<int32>(v3 + 0x8);
				if (TGetValue<BYTE>(v5 + 0xD))
				{
					for (i = TGetValue<int32>(v3 + 0x4);
						!TGetValue<BYTE>(i + 0xD); 
						i = TGetValue<int32>(i + 0x4))
					{
						if (v3 != TGetValue<int32>(i + 0x8))
							break;
						v3 = i;

					}
					v3 = i;
				}
				else
				{
					v3 = TGetValue<int32>(v3 + 0x8);
					for (j = TGetValue<int32>(v5); 
						!TGetValue<BYTE>(j + 0xD); 
						j = TGetValue<int32>(j))
						v3 = j;
				}
			}
		}
	}
};

class IEntity
{
private:
	template<class cData> cData GetValue(int32 dwOffset)
	{
		return Read<cData>((int32)this + dwOffset);
	}
	template<class cData> void SetValue(int32 dwOffset, cData Value)
	{
		Write<cData>(((int32)this + dwOffset), Value);
	}
	template<class cData> cData TGetValue(int32 dwOffset)
	{
		return Read<cData>(dwOffset);
	}
	const char* GetStringValue(int32 dwOffset)
	{
		return ReadStringMemoryPtr((uintptr_t)this + dwOffset);
	}
public:
	int32 GetEntityId()
	{
		return GetValue<int32>(IEntityData::GetEntityIdI);
	}

	IEntityClass* GetEntityClass()
	{
		return GetValue<IEntityClass*>(IEntityData::GetEntityClassI);
	}

	Vec3 GetWorldPos()
	{
		return GetValue<Vec3>(0x60);
	}

	int32 GetFlags()
	{
		return GetValue<int32>(0x4);
	}

	int32 GetRawId()
	{
		return GetValue<int32>(0x14);
	}

	Matrix3x4 GetWorldTM()
	{
		return GetValue<Matrix3x4>(0x30);
	}

	Quat GetRotation()
	{
		return GetValue<Quat>(0x78);
	}

	IEntityRenderProxy* GetRenderProxy()
	{
		return TGetValue<IEntityRenderProxy*>(GetValue<int32>(0x9C));
	}

	void SetLocalPos(const Vec3& vPos)
	{
		WriteMemory(((int32)this + 0x30), &GetWorldTM().SetTranslation(vPos), sizeof(f32) * 12);
	}

	const char* GetName()
	{
		return GetStringValue(0xB8);
	}

	int32 GetIntName()
	{
		return GetValue<int32>(0xB8);
	}

	void SetIntName(int32 name)
	{
		SetValue<int32>(0xB8, name);
	}

	ICharacterInstance* GetCharacter(int32 Slot)
	{
		if (int32 GetProxyRenderPtr = (int32)GetRenderProxy())
		{
			int32 Point = TGetValue<int32>(GetProxyRenderPtr + 0x30);
			int32 SlotID = TGetValue<int32>(Point + 0x4 * Slot);
			if (Point && SlotID)
			{
				return TGetValue<ICharacterInstance*>(SlotID + 0x6C);
			}
		}
		return 0;
	}
};

class IEntityClass
{
private:
	const char* GetStringValue(int32 dwOffset)
	{
		return ReadStringMemoryPtr((uintptr_t)this + dwOffset);
	}
public:
	const char* GetName()
	{
		return GetStringValue(0x8);
	}
};

class IEntityRenderProxy
{
private:
	template<class cData> cData GetValue(int32 dwOffset)
	{
		return Read<cData>((int32)this + dwOffset);
	}
	template<class cData> void SetValue(int32 dwOffset, cData Value)
	{
		Write<cData>(((int32)this + dwOffset), Value);
	}
public:
	void GetWorldBounds(IEntity* pEntity, AABB &aabb)
	{
		aabb = GetValue<AABB>(0x3C);
		aabb.SetTransformedAABB(pEntity->GetWorldTM(), aabb);
	}

	void SetRndFlags(int32 Flag)
	{
		SetValue<int32>((0x14), Flag);
	}

	void SetHUDSilhouettesParams(f32 r, f32 g, f32 b, f32 a)
	{
		int32 m_color = (int32)(f32)(a* 255.0) | (((int32)(f32)(b* 255.0) | (((int32)(f32)(g* 255.0) | ((int32)(f32)(r* 255.0) << 8)) << 8)) << 8);
		SetValue<int32>((0x78), m_color);
	}
};

class ICharacterInstance
{
public:
	ISkeletonPose* GetISkeletonPose()
	{
		return (ISkeletonPose*)(this + 0x748);
	}
};

class ISkeletonPose
{
private:
	template<class cData> cData GetValue(int32 dwOffset)
	{
		return Read<cData>((int32)this + dwOffset);
	}
	template<class cData> cData TGetValue(int32 dwOffset)
	{
		return Read<cData>(dwOffset);
	}
public:
	QuatT GetAbsJointById(int32 nJointID)
	{
		return TGetValue<QuatT>(GetValue<int32>(0x114) + 0x1C * nJointID);
	}
};

class IActor
{
private:
	template<class cData> cData GetValue(int32 dwOffset)
	{
		return Read<cData>((int32)this + dwOffset);
	}
	template<class cData> void SetValue(int32 dwOffset, cData Value)
	{
		Write<cData>(((int32)this + dwOffset), Value);
	}
	template<class cData> cData TGetValue(int32 dwOffset)
	{
		return Read<cData>(dwOffset);
	}
	template<class cData> void TSetValue(int32 dwOffset, cData Value)
	{
		Write<cData>((dwOffset), Value);
	}	
	int32 GetEncryptValue(int32 dwOffset)
	{
		int32 xor_decdata[2];
		ReadMemory((int32)this + dwOffset, &xor_decdata, sizeof(xor_decdata));
		return xor_decdata[0] ^ xor_decdata[1];
	}
	void SetEncryptValue(int32 dwOffset, f32 fValue)
	{
		Write<int32>((int32)this + dwOffset, *(int32*)& fValue ^ Read<int32>((int32)this + dwOffset + 0x4));
	}
public:
	template<class cData> cData GetFunction(int32 dwOffset)
	{
		return Read<cData>((int32)this + dwOffset);
	}
	template<class cData> void SetFunction(int32 dwOffset, cData Value)
	{
		Write<cData>(((int32)this + dwOffset), Value);
	}
	void NoClimb(f32 fValue)
	{
		SetFunction(0x1926580 + 0x70 + 0x144 + 0x4 + 0x4, fValue);
		Write<float>(0x1926580 + 0x70 + 0x144 + 0x4 + 0x4, 22.5f);
	}

	IEntity* GetEntity()
	{
		return GetValue<IEntity*>(IActorData::GetEntityI);
	}	

	IPlayer* GetPlayer()
	{
		return GetValue<IPlayer*>(IActorData::GetPlayerI);
	}

	int32 GetActorId()
	{
		return GetValue<int32>(IActorData::GetActorIdI);
	}

	int32 GetClassId()
	{
		return GetValue<int32>(IActorData::GetClassIdI);
	}

	int32 GetTeamId()
	{
		return GetValue<int32>(IActorData::GetTeamIdI);
	}

	int32 GetWeaponId()
	{
		return GetValue<int32>(IActorData::WeaponIdI);
	}

	int32 GetCurrentItemId()
	{
		return TGetValue<int32>(GetValue<int32>(0x1C) + 0x68);
	}

	int32 GetHealth()
	{
		f32 fValue = 100.0f;
		*(int32*)&fValue = GetEncryptValue(0x40);
		return fValue;
	}

	int32 GetArmor()
	{
		f32 fValue = 100.0f;
		*(int32*)&fValue = GetEncryptValue(0xBD4);
		return fValue;
	}

	void SetHealth(f32 fValue)
	{
		SetEncryptValue(0x40, fValue);
	}

	void SetArmor(f32 fValue)
	{
		SetEncryptValue(0xBD4, fValue);
	}

	bool IsDead()
	{
		int32 xor_decdata = GetValue<int32>(0x44);
		if (xor_decdata)
		{
			int32 xor_data = xor_decdata ^ GetValue<int32>(0x40);
			return (xor_data != IsDeadFlag::eUnknown && xor_data != IsDeadFlag::eDead);
		}
		return false;
	}

	IWorldQuery* GetWorldQuery()
	{
		int32 ptr_s = GetValue<int32>(0xC);
		if (!ptr_s)
			return nullptr;

		int32 ptr_v = TGetValue<int32>(ptr_s + 0x40);
		if (!ptr_v)
			return nullptr;

		return TGetValue<IWorldQuery*>(ptr_v + 0x18);
	}
};

class IWorldQuery
{
private:
	template<class cData> cData GetValue(int32 dwOffset)
	{
		return Read<cData>((int32)this + dwOffset);
	}
	template<class cData> void SetValue(int32 dwOffset, cData Value)
	{
		Write<cData>(((int32)this + dwOffset), Value);
	}
public:
	Vec3 GetPos() 
	{ 
		return GetValue<Vec3>(0x20);
	}

	Vec3 GetDir()  
	{ 
		return GetValue<Vec3>(0x2C);
	}

	void SetPos(const Vec3 &vPos)
	{ 
		SetValue(0x20, vPos);
	}

	void SetDir(const Vec3 &vPos) 
	{ 
		SetValue(0x2C, vPos);
	}

	f32 m_proximityRadius() 
	{ 
		return GetValue<f32>(0x1C);
	}

	uint32 m_validQueries()  
	{
		return GetValue<uint32>(0x14); 
	}

	int32 m_renderFrameId()  
	{
		return GetValue<int32>(0x18); 
	}

	EntityId* ProximityQuery(int32 &numberOfEntities)
	{
		ValidateQuery(eWQ_Proximity);
		numberOfEntities = (GetValue<int32>(0x130) - GetValue<int32>(0x12C)) >> 0x2;
		return numberOfEntities ? GetValue<EntityId*>(0x12C) : 0x0;
	}

	EntityId* GetEntitiesAround(int32 &num)
	{
		ValidateQuery(eWQ_EntitiesAround);
		num = (GetValue<int32>(0x24) - GetValue<int32>(0x20)) >> 0x2;
		return num ? GetValue<EntityId*>(0x20) : 0;
	}

    void SetProximityRadius(f32 n)
	{
		SetValue(0x1C, n);
		SetValue<uint32_t>(0x14, m_validQueries() & (eWQ_Proximity | eWQ_InFrontOf));
	}

	ray_hit GetLookAtPoint(f32 fMaxDist = 0, bool ignoreGlass = false)
	{
		ValidateQuery(eWQ_Raycast);
		if (GetValue<BYTE>(0x48))
		{
			ray_hit m_rayHitPierceable = GetValue<ray_hit>(0x8C);
			ray_hit m_rayHitSolid = GetValue<ray_hit>(0x4C);
			ray_hit hit = !ignoreGlass && GetValue<f32>(0x8C) >= 0.f ? m_rayHitPierceable : m_rayHitSolid;
			if ((fMaxDist <= 0) || (hit.dist <= fMaxDist)) { return hit; }
		}
		return ray_hit();
	}

	EntityId GetLookAtEntityId(bool ignoreGlass = false)
	{
		ValidateQuery(eWQ_Raycast);
		return !ignoreGlass && GetValue<f32>(0x8C) >= 0.f ? 0 : GetValue<EntityId>(0x110);
	}

	void ValidateQuery(EWorldQuery query)
	{
		uint32 queryMask = 1u << query;
		int32 frameid = GetValue<int32>(Read<int32>(GameData::dwGlobalAdress) + 0xE4);
		if (m_renderFrameId() != frameid)
		{
			SetValue(0x18, frameid);
			SetValue(0x14, 0);
		}
		else
		{
			if (m_validQueries() & queryMask)
				return;
		}
		SetValue(0x14, m_validQueries() | queryMask);
	}
};

class IPlayer
{
private:
	template<class cData> cData GetValue(int32 dwOffset)
	{
		return Read<cData>((int32)this + dwOffset);
	}
	template<class cData> void SetValue(int32 dwOffset, cData Value)
	{
		Write<cData>(((int32)this + dwOffset), Value);
	}
public:
	void SetScale(f32 fValue)
	{
		SetValue<f32>((0x8), fValue);
	}

	void SetRecoilMult(int8 iValue)
	{
		SetValue<int8>((0xB1), iValue);
	}

	Quat GetViewRotation()
	{
		return GetValue<Quat>(0x80);
	}

	void SetViewRotation(Quat &rotation)
	{
		SetValue<Quat>((0xA0), rotation);
		SetValue<Quat>((0x80), rotation);
		SetValue<Quat>((0x90), rotation);
	}
};

class IItemSystem
{
private:
	template<class cData> cData GetValue(int32 dwOffset)
	{
		return Read<cData>((int32)this + dwOffset);
	}
	template<class cData> cData TGetValue(int32 dwOffset)
	{
		return Read<cData>(dwOffset);
	}
public:
	static IItemSystem* Singleton()
	{
		return Read<IItemSystem*>(GameData::dwBaseIItemSystem);
	}

	IItem* GetItem(int32 itemId)
	{
		int32 v7 = NULL;
		int32 v3 = GetValue<int32>(0x40);
		int32 v4 = v3;
		int32 v5 = TGetValue<int32>(v3 + 0x4);

		while (!TGetValue<BYTE>(v5 + 0xD))
		{
			if (TGetValue<int32>(v5 + 0x10) >= itemId)
			{
				v4 = v5;
				v5 = TGetValue<int32>(v5);
			}
			else
			{
				v5 = TGetValue<int32>(v5 + 0x8);
			}
		}

		if (v4 == v3 || (v7 = v4, itemId < TGetValue<int32>(v4 + 0x10)))
			v7 = v3;

		if (v7 != v3)
			return TGetValue<IItem*>(v7 + 0x14);

		return NULL;
	}
};

class IItem
{
private:
	template<class cData> cData GetValue(int32 dwOffset)
	{
		return Read<cData>((int32)this + dwOffset);
	}
public:
	IWeapon* GetWeapon()
	{
		return (IWeapon*)(this + 0x14);
	}

	IEntity* GetEntity()
	{
		return GetValue<IEntity*>(0x8);
	}
};

class IWeapon
{
private:
	template<class cData> cData GetValue(int32 dwOffset)
	{
		return Read<cData>((int32)this + dwOffset);
	}
	template<class cData> void TSetValue(int32 dwOffset, cData Value)
	{
		Write<cData>((dwOffset), Value);
	}
public:
	IWeaponSpecific* GetWeaponSpecific()
	{
		return GetValue<IWeaponSpecific*>(IWeaponSpecificI);
	}

	void SetFiringPos(Vec3 VectorValue)
	{
		int32 ptr_s = GetValue<int32>(0xC);
		if (!ptr_s)
			return;

		TSetValue<Vec3>((ptr_s + SetFiringPosI), VectorValue);
	}
};

class IWeaponSpecific
{
private:
	template<class cData> cData GetValue(int32 dwOffset)
	{
		return Read<cData>((int32)this + dwOffset);
	}
	template<class cData> void SetValue(int32 dwOffset, cData Value)
	{
		Write<cData>(((int32)this + dwOffset), Value);
	}
public:
	IWeaponExtra* GetWeaponExtra()
	{
		return GetValue<IWeaponExtra*>(IWeaponData::IWeaponExtraI);
	}

	IWeaponCrypt* GetWeaponCrypt()
	{
		return GetValue<IWeaponCrypt*>(IWeaponData::IWeaponCryptI);
	}

	IWeaponAmmo* GetWeaponAmmo()
	{
		return GetValue<IWeaponAmmo*>(IWeaponData::IWeaponAmmoI);
	}

	void Shutter(int8 iValue)
	{
		SetValue<int8>((IWeaponData::ShutterI), iValue);
	}

	int32 GetWeaponStance()
	{
		return GetValue<int32>(IWeaponData::GetWeaponStanceI);
	}
	bool IsFiring()
	{
		DWORD v12 = *(DWORD*)((DWORD)this + 0x70);
		return (v12 == 3 || v12 == 6 || v12 == 12 || v12 == 13 || v12 == 14 || v12 == 15 || v12 == 16 || v12 == 48 || v12 == 49);
	}
	void StartFire()
	{
		SetValue<int32>((0xF4), GetValue<int32>(0xF8));
	}

	void StopFire()
	{
		SetValue<int32>((0xF4), GetValue<int32>(0xF0));
	}
};

class IWeaponExtra
{
private:
	template<class cData> void SetValue(int32 dwOffset, cData Value)
	{
		Write<cData>(((int32)this + dwOffset), Value);
	}
public:
	void SetDamage(int32 iValue)
	{
		SetValue<int32>((IWeaponData::DamageI), iValue);
	}
	void SetSpeed(int8 iValue)
	{
		SetValue<int8>((IWeaponData::SpeedFireId), iValue);
	}
};

class IWeaponCrypt
{
private:
	template<class cData> cData GetValue(int32 dwOffset)
	{
		return Read<cData>((int32)this + dwOffset);
	}
	template<class cData> void SetValue(int32 dwOffset, cData Value)
	{
		Write<cData>(((int32)this + dwOffset), Value);
	}
	template<class cData> cData TGetValue(int32 dwOffset)
	{
		return Read<cData>(dwOffset);
	}
	template<class cData> void TSetValue(int32 dwOffset, cData Value)
	{
		Write<cData>((dwOffset), Value);
	}
public:
	void SetSway(Vec3 VectorValue)
	{
		SetValue<Vec3>((0x0), VectorValue);
	}

	int32 GetCrypt(int32 Id)
	{
		int32 result;
		int32 v3 = GetValue<int32>(0x6C);
		int32 v5 = TGetValue<int32>(v3 + 0x4);
		while (!TGetValue<BYTE>(v5 + 0xD))
		{
			int32 EntityId = TGetValue<int32>(v5 + 0x10);
			if (EntityId == Id) break;
			else if (EntityId < Id) v5 = TGetValue<int32>(v5 + 0x8);
			else v5 = TGetValue<int32>(v5);
		}
		if (TGetValue<int32>(v5 + 0x10) == Id)
		{
			result = v5;
		}
		return result;
	}

	bool GetEncryptValue(int32 Id, f32* fValue)
	{
		bool result = false;
		int32 xor_decdata[2];
		ReadMemory(GetCrypt(Id) + 0x14, &xor_decdata, sizeof(xor_decdata));
		result = *(int32*)fValue = xor_decdata[0] ^ xor_decdata[1];
		return result;
	}

	void SetCryptValue(int32 Id, f32 fValue)
	{
		TSetValue<int32>(GetCrypt(Id) + 0x14, *(int32*)&fValue ^ Read<int32>(GetCrypt(Id) + 0x18));
	}
};

class IWeaponAmmo
{
private:
	template<class cData> cData GetValue(int32 dwOffset)
	{
		return Read<cData>((int32)this + dwOffset);
	}
	template<class cData> void SetValue(int32 dwOffset, cData Value)
	{
		Write<cData>(((int32)this + dwOffset), Value);
	}
public:
	void UnlimitedAmmo(bool bForce)
	{
		SetValue<int32>((0x0), bForce);
	}

	int32 GetAmmoCount()
	{
		return GetValue<int32>(0x4);
	}

	void SetAmmoCount(int32 iValue)
	{
		SetValue<int32>((0x4), iValue);
	}
};

class IGameRules
{
private:
	template<class cData> cData GetValue(int32 dwOffset)
	{
		return Read<cData>((int32)this + dwOffset);
	}
public:
	int32 GetTeamCount()
	{
		return GetValue<int32>(0x88);
	}
};

class IGameFramework
{
private:
	template<class cData> cData GetValue(int32 dwOffset)
	{
		return Read<cData>((int32)this + dwOffset);
	}
	template<class cData> cData TGetValue(int32 dwOffset)
	{
		return Read<cData>(dwOffset);
	}
public:
	static IGameFramework* Singleton()
	{
		return Read<IGameFramework*>(GameData::dwBaseGameFrameWork);
	}

	IGameRules* GetGameRules()
	{
		return GetValue<IGameRules*>(0x618);
	}

	IActorSystem* GetActorSystem()
	{
		return GetValue<IActorSystem*>(0x4B0);
	}

	IEntitySystem* GetEntitySystem()
	{
		return GetValue<IEntitySystem*>(0x18);
	}

	int32 GetClientActorId()
	{
		int32 v3 = 0;
		int32 v4 = 0;
		int32 v8 = GetValue<int32>(0x28);
		if (v8)
		{
			int32 v2 = TGetValue<int32>(v8 + 0x24);
			if (v2)
				v3 = TGetValue<int32>(v2 + 0x8);
			else
				v3 = 0;

			if (v3)
			{
				v4 = TGetValue<int32>(v3 + 0x10);
			}
		}
		return v4;
	}

	IActor* GetClientActor(TActorMap m_actors)
	{
		TActorMap::iterator it = m_actors.find(GetClientActorId());
		if (it != m_actors.end()) return it->second;
		return 0;
	}
};

class ICVar
{
private:
	template<class cData> cData GetValue(int32 dwOffset)
	{
		return Read<cData>((int32)this + dwOffset);
	}
	template<class cData> void SetValue(int32 dwOffset, cData Value)
	{
		Write<cData>(((int32)this + dwOffset), Value);
	}
public:
	static ICVar* Singleton()
	{
		return Read<ICVar*>(GameData::dwBaseGameCVar);
	}

	template<class cData> cData GetCVar(int32 dwOffset)
	{
		return GetValue<cData>(dwOffset);
	}

	template<class cData> void SetCVar(int32 dwOffset, cData Value)
	{
		SetValue<cData>((dwOffset), Value);
	}
};