#pragma once
#include "CryOffsets.h"

int32 gWidth = 0;
int32 gHeight = 0;
f32   gCenterX = 0.f;
f32   gCenterY = 0.f;
std::string p_names;
std::string p_classname;
std::string m_itemname;
std::string p_weponsname;
std::string p_weponsclassname;
std::string p_objectname;
std::string p_objectclassname;
int32 m_weaponid = 0;
int32 p_weaponid = 0;
int32 m_class_id = 0;
int32 g_victoryCondition = 0;
Vec3 p_head = { ZERO }, p_pos = { ZERO }, m_pos = { ZERO };
f32 vector_z = 0.0f;
bool v_silhouettes = false;

ILINE bool world_to_screen(IRender* p_Render, Vec3 in, Vec3 &out)
{
	int32 v[4] = { 0, 0, p_Render->GetWidth(), p_Render->GetHeight() };
	p_Render->ProjectToScreen(v, in.x, in.y, in.z, &out.x, &out.y, &out.z);
	if (out.z < 0.0f || out.z > 1.0f) return false;
	out.x = out.x * (v[2] / 100.0f);
	out.y = out.y * (v[3] / 100.0f);
	return true;
}

ILINE bool set_fov_aim(IRender *p_Render, Vec3 &p_vector, f32 size)
{
	f32 screen_center_x = (p_Render->GetWidth() * 0.5f);
	f32 screen_center_y = (p_Render->GetHeight() * 0.5f);
	return ((screen_center_x >= p_vector.x && screen_center_x <= p_vector.x + size / 2 && screen_center_y >= p_vector.y && screen_center_y <= p_vector.y + size / 2) ||
		sqrt((p_vector.x - screen_center_x) * (p_vector.x - screen_center_x) + (p_vector.y - screen_center_y) * (p_vector.y - screen_center_y)) <= size);
}

ILINE f32 get_hypotenuse(IRender* p_Render, Vec3 &vec_screen)
{
	f32 f_screen_center_x = (p_Render->GetWidth() * 0.5f);
	f32 f_screen_center_y = (p_Render->GetHeight() * 0.5f);
	f32 f_position_x = vec_screen.x > f_screen_center_x ? vec_screen.x - f_screen_center_x : f_screen_center_x - vec_screen.x;
	f32 f_position_y = vec_screen.y > f_screen_center_y ? vec_screen.y - f_screen_center_y : f_screen_center_y - vec_screen.y;
	return sqrt(f_position_x * f_position_x + f_position_y * f_position_y);
}

ILINE bool elimination_team(IActor* m_Actor, IActor* p_Actor)
{ 
	return ((m_Actor->GetTeamId() != p_Actor->GetTeamId() || p_Actor->GetTeamId() == 0) && (p_Actor != m_Actor));
}

ILINE Vec3 get_bone_by_id(IEntity* p_Entity, int16 BoneId)
{
	ICharacterInstance* p_Character = p_Entity->GetCharacter(0);
	if (!IsValidPtr(p_Character))
		return Vec3(ZERO);

	ISkeletonPose* p_Skeleton = p_Character->GetISkeletonPose();
	if (!IsValidPtr(p_Skeleton))
		return Vec3(ZERO);

	Matrix3x4 m_Out = p_Entity->GetWorldTM() * Matrix3x4(p_Skeleton->GetAbsJointById(BoneId));
	return m_Out.GetTranslation();
}

ILINE int16 bone_select_pvp()
{
	vector_z = 0.0f;
	int16 s_bone = 0;
	switch (Settings::Aimbot::bones)
	{
	case 0: s_bone = Bones::Bone_R_Eye_01;
		break;
	case 1: s_bone = Bones::Bone_Spine2;
		break;
	}
	return s_bone;
};

ILINE int16 bone_select_pve()
{
	vector_z = 0.1f;
	int16 s_bone = 0;
	switch (Settings::Aimbot::bones)
	{
	case 0: s_bone = Bones::Bone_Head;
		break;
	case 1: s_bone = Bones::Bone_Spine2;
		break;
	}
	return s_bone;
};

ILINE int16 get_point_aim()
{
	int16 g_type = 0;
	if (g_victoryCondition == GameModes::ePVE)
		g_type = bone_select_pve();
	else
		g_type = bone_select_pvp();

	return g_type;
}

ILINE bool is_object_detect(const char* name)
{
	if (Settings::Aimbot::turets == 1 && g_victoryCondition == GameModes::ePVE)
	{	
		if (strstr(p_names.c_str(), name))
			return true;
		else
			return false;
	}
}

ILINE void unlim_ammo(IWeapon* m_Weapon)
{
	if (IWeaponAmmo * m_WeaponAmmo = m_Weapon->GetWeaponSpecific()->GetWeaponAmmo())
	{
		if (m_WeaponAmmo->GetAmmoCount() < 1)
		{
			m_WeaponAmmo->SetAmmoCount(-1);
			m_WeaponAmmo->UnlimitedAmmo(1);
		}
	}
}

ILINE int16 get_bone_object()
{
	if (Settings::Aimbot::turets == 1 && g_victoryCondition == GameModes::ePVE)
	{
		if (strstr(p_names.c_str(), XorString("TurretRail_"))) return Bones::Bone_R_ForeTwist_1;
		if (strstr(p_names.c_str(), XorString("Heavy"))) return Bones::Bone_Head;
		if (strstr(p_names.c_str(), XorString("IronMan"))) return Bones::Bone_Spine2;
		if (strstr(p_names.c_str(), XorString("mech2300_"))) return Bones::Bone_Head;
		if (strstr(p_names.c_str(), XorString("TurretFloor_MG"))) return Bones::Bone_R_ForeTwist_1;
		if (strstr(p_names.c_str(), XorString("TurretHunt"))) return Bones::Bone_R_ForeTwist_1;
		if (strstr(p_names.c_str(), XorString("TurretFloor_mg"))) return Bones::Bone_R_ForeTwist_1;
		if (strstr(p_names.c_str(), XorString("TurretFloor"))) return Bones::Bone_R_Finger02;
		if (strstr(p_names.c_str(), XorString("Turret_MG"))) return Bones::Bone_R_Finger02;
		if (strstr(p_names.c_str(), XorString("TurretAPC"))) return Bones::Bone_Head;
		if (strstr(p_names.c_str(), XorString("_Drone_"))) return Bones::Bone_R_Finger02;
		if (strstr(p_names.c_str(), XorString("TurretWall_mg01"))) return Bones::Bone_R_UpperArm;
		if (strstr(p_names.c_str(), XorString("TurretCeil_"))) return Bones::Bone_R_Finger3;
		if (strstr(p_names.c_str(), XorString("TurretFloor_A"))) return Bones::Bone_R_ForeTwist_1;
		if (strstr(p_names.c_str(), XorString("HeavyTurretRail"))) return Bones::Bone_R_Finger1;
		if (strstr(p_names.c_str(), XorString("SED"))) return Bones::Bone_R_Finger01;
		if (strstr(p_names.c_str(), XorString("Cyborg"))) return Bones::Bone_Spine;
		if (strstr(p_names.c_str(), XorString("Destroyer"))) return Bones::Bone_Spine;
		if (strstr(p_names.c_str(), XorString("Drone_MG_Normal"))) return Bones::Bone_Neck;
		if (strstr(p_names.c_str(), XorString("SMGHeavy"))) return Bones::Bone_Head;
		if (strstr(p_names.c_str(), XorString("CQBHeavy"))) return Bones::Bone_Head;
		if (strstr(p_names.c_str(), XorString("Crusher"))) return Bones::Bone_Head;
		if (strstr(p_classname.c_str(), XorString("Mantis"))) return Bones::Bone_Head;
		if (strstr(p_classname.c_str(), XorString("SEDSoldier"))) return Bones::Bone_Head;
		if (!strstr(p_classname.c_str(), XorString("Helicopter"))) return Bones::Bone_Head;
	}
	else
	{
		return get_point_aim();
	}
	return get_point_aim();
}

ILINE Vec3 get_enemy_head_position(IEntity* p_Entity)
{
	Vec3 head = { ZERO };

	if (g_victoryCondition == GameModes::ePVE)
		head = get_bone_by_id(p_Entity, Bones::Bone_Head);
	else
		head = get_bone_by_id(p_Entity, Bones::Bone_R_Eye_01);

	return head;
}

ILINE void start_fire(IWeapon* m_Weapon)
{
	if (m_Weapon)
	{
		m_Weapon->GetWeaponSpecific()->StartFire();
		m_Weapon->GetWeaponSpecific()->StopFire();
	}
}

ILINE void trigger_bot(IActor* m_Actor, IActor* p_Actor, int32 clamp = 0, int32 delay = 0)
{
	if (m_Actor->GetWorldQuery()->GetLookAtEntityId() == p_Actor->GetActorId())
	{
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		Sleep(clamp);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		Sleep(delay);
	}
}

ILINE void trigger_war(IActor* m_Actor, IActor* p_Actor, int32 clamp = 0, int32 delay = 0)
{
	if (p_Actor->GetWorldQuery()->GetLookAtEntityId() == m_Actor->GetActorId() || m_Actor->GetWorldQuery()->GetLookAtEntityId() == p_Actor->GetActorId())
	{
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		Sleep(clamp);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		Sleep(delay);
	}
}

ILINE void update_flags(IEntity* p_Entity)
{
	p_Entity->GetRenderProxy()->SetRndFlags(eRenderNodeFlags::eAllMap);
}

ILINE void esp_silhouettes(IActor* p_Actor, IEntity* p_Entity, IRender* p_Render, int32 Status, f32 r, f32 g, f32 b)
{
	IEntityRenderProxy* pRenderProxy = p_Entity->GetRenderProxy();
	if (pRenderProxy)
	{
		if (Status > 0)
		{
			if (p_Actor->IsDead())
			{
				AABB aabb;
				pRenderProxy->GetWorldBounds(p_Entity, aabb);
				p_Render->DrawAABB(aabb);
				pRenderProxy->SetHUDSilhouettesParams(r, g, b, a_Def);
			}
			else
			{
				pRenderProxy->SetHUDSilhouettesParams(a_Def, a_Def, a_Def, a_Def);
			}

			v_silhouettes = true;
		}
		if (Status < 1)
		{
			if (v_silhouettes)
			{
				pRenderProxy->SetHUDSilhouettesParams(a_Def, a_Def, a_Def, a_Def);
				v_silhouettes = false;
			}
		}
	}
}

ILINE void hide_name(IEntity* m_Entity, IEntity* p_Entity)
{
	if ((!strstr(p_names.c_str(), XorString("Heavy")) ||
		!strstr(p_names.c_str(), XorString("Turret")) ||
		!strstr(p_names.c_str(), XorString("Crusher")) ||
		!strstr(p_classname.c_str(), XorString("Mantis")) ||
		!strstr(p_classname.c_str(), XorString("SEDSoldier")) ||
		!strstr(p_classname.c_str(), XorString("Helicopter")) ||
		!strstr(p_names.c_str(), XorString("_Drone_")) ||
		!strstr(p_names.c_str(), XorString("IronMan")) ||
		!strstr(p_names.c_str(), XorString("SED")) ||
		!strstr(p_names.c_str(), XorString("Cyborg")) ||
		!strstr(p_names.c_str(), XorString("Destroyer")) ||
		!strstr(p_names.c_str(), XorString("Drone_MG_Normal")) ||
		!strstr(p_names.c_str(), XorString("SMGHeavy")) ||
		!strstr(p_names.c_str(), XorString("CQBHeavy"))))
	{
		m_Entity->SetIntName(p_Entity->GetIntName());
	}
}

ILINE void rotate_actor(IActor* m_Actor, IActor* p_Actor)
{
	IPlayer* m_Player = m_Actor->GetPlayer();
	IPlayer* p_Player = p_Actor->GetPlayer();

	p_Player->SetViewRotation(m_Player->GetViewRotation());
}

ILINE void zero_bullet_pos(IWeapon* m_Weapon)
{
	m_Weapon->SetFiringPos(ZERO);
}

ILINE void set_bullet_pos(IWeapon* m_Weapon, IActor* m_Actor, IActor* p_Actor, Vec3 &p_hit_point)
{
	Vec3 p_pos = { ZERO };
	p_pos.x = p_hit_point.x;
	p_pos.y = p_hit_point.y;
	p_pos.z = p_hit_point.z + vector_z;
	m_Weapon->SetFiringPos(p_pos);
}

#pragma pack(push, 4)
struct _target
{
	int32 p_result;
	Vec3 bone_hit_point;
} target;
#pragma pack(pop)

void create_Bypass(ICVar* m_CVar, int32 anticheat_Status)
{
	m_CVar->SetCVar(ICVarData::g_anti_cheat_memscan_thread_delayI, 9999);
	m_CVar->SetCVar(ICVarData::g_anti_cheat_memscan_logI, anticheat_Status);
	m_CVar->SetCVar(ICVarData::g_anti_cheat_memscan_dump_patternsI, anticheat_Status);
}


void create_Function(ICVar* m_CVar, IActor* m_Actor, IItem* m_Item)
{
	IWeapon* m_Weapon = m_Item->GetWeapon();
	if (!IsValidPtr(m_Weapon))
		return;

	IWeaponSpecific* m_Specific = m_Weapon->GetWeaponSpecific();
	if (!IsValidPtr(m_Specific))
		return;

	IWeaponExtra* m_Extra = m_Specific->GetWeaponExtra();
	if (!IsValidPtr(m_Extra))
		return;

	IWeaponCrypt* m_Crypt = m_Specific->GetWeaponCrypt();
	if (!IsValidPtr(m_Crypt))
		return;

	IWeaponAmmo* m_Ammo = m_Specific->GetWeaponAmmo();
	if (!IsValidPtr(m_Ammo))
		return;

	IPlayer* m_Player = m_Actor->GetPlayer();
	if (!IsValidPtr(m_Player))
		return;

	m_weaponid = m_Actor->GetWeaponId();
	m_itemname = m_Item->GetEntity()->GetName();

	if (Settings::Weapone::nosway == 1)
		m_Crypt->SetSway(ZERO);

	if (Settings::Weapone::noshoters == 1)
		m_Specific->Shutter(0);


	if (Settings::Weapone::dmg == 1)
	{
		m_Extra->SetDamage(5);
	}
	else
	{
		m_Extra->SetDamage(1);
	}

	m_Extra->SetSpeed(25);

	m_Actor->SetFunction(IActorData::slideDistanceMultI, Settings::Player::longslide ? 700.f : 1.f);
	m_Actor->SetFunction(IActorData::claymore_detector_radiusI, Settings::ESP::EspMines ? 700.f : 0.f);
	m_CVar->SetCVar(IActorData::hide_radar, Settings::Player::radar ? 0 : 1);
	(((Settings::Weapone::norecoil)) ? m_Player->SetRecoilMult(1) : m_Player->SetRecoilMult(0));
	m_CVar->SetCVar(ICVarData::i_pelletsDispI, Settings::Weapone::nospread  && m_class_id != ClassesId::Medic ? 29.f : 1.f);


	if (Settings::Player::climb == 1)
		m_Actor->NoClimb(22.5f);
	else
		m_Actor->NoClimb(2.25f);

	if (Settings::Player::afk == 1)
	{
		m_CVar->SetCVar(ICVarData::g_ingame_afk_timeoutI, 3600);
		m_CVar->SetCVar(ICVarData::g_gameroom_afk_timeoutI, 3600);
	}
	else
	{
		m_CVar->SetCVar(ICVarData::g_ingame_afk_timeoutI, 30);
		m_CVar->SetCVar(ICVarData::g_gameroom_afk_timeoutI, 60);
	}
}

void create_Engine()
{
	m_actors.clear();
	f32 max_dist = 1000.f;
	f32 min_dist = 0.f;
	Vec3 v_out = { ZERO };
	target.bone_hit_point = { ZERO };
	target.p_result = 0;

	if ((GetAsyncKeyState(VK_CAPITAL) & 1) && Settings::Aimbot::capslock == true && (Settings::Aimbot::enabled == 0 || Settings::Aimbot::enabled == 1))
		Settings::Aimbot::enabled = !Settings::Aimbot::enabled;

	IRender* m_IRender = IRender::Singleton();
	if (!IsValidPtr(m_IRender))
		return;

	ICVar* m_ICVar = ICVar::Singleton();
	if (!IsValidPtr(m_ICVar))
		return;

	g_victoryCondition = m_ICVar->GetCVar<int32>(ICVarData::g_victoryConditionI);
	IGameFramework* m_IGameFramework = IGameFramework::Singleton();
	if (!IsValidPtr(m_IGameFramework))
		return;

	IActorSystem* m_IActorSystem = m_IGameFramework->GetActorSystem();
	if (!IsValidPtr(m_IActorSystem))
		return;

	m_IActorSystem->CreateActorIterator();
	IActor* m_Actor = m_IGameFramework->GetClientActor(m_actors);
	if (!IsValidPtr(m_Actor))
		return;

	IEntity* m_IEntity = m_Actor->GetEntity();
	if (!IsValidPtr(m_IEntity))
		return;

	IItemSystem* m_IItemSystem = IItemSystem::Singleton();
	if (!IsValidPtr(m_IItemSystem))
		return;

	IItem* m_Item = m_IItemSystem->GetItem(m_Actor->GetCurrentItemId());
	if (!IsValidPtr(m_Item))
		return;

	IWeapon* m_IWeapon = m_Item->GetWeapon();
	if (!IsValidPtr(m_IWeapon))
		return;

	if (Settings::Weapone::pistol == 1 && GetAsyncKeyState(VK_LBUTTON))
	{
		if (IWeaponAmmo * m_WeaponAmmo = m_IWeapon->GetWeaponSpecific()->GetWeaponAmmo())
		{
			if (m_WeaponAmmo->GetAmmoCount() <= 0)
				m_WeaponAmmo->UnlimitedAmmo(1);
			else
			{
				m_WeaponAmmo->UnlimitedAmmo(0);
			}
		}
	}

	m_pos = m_IEntity->GetWorldPos();
	m_class_id = m_Actor->GetClassId();
	//create_Bypass(m_ICVar, 0);
	create_Function(m_ICVar, m_Actor, m_Item);

	if (Settings::Aimbot::enabled == 0)
		zero_bullet_pos(m_IWeapon); 
	
	//if (Settings::Weapone::pistol == 1 && GetAsyncKeyState(VK_LBUTTON))
	//{
	//	if (m_weaponid == WeaponsId::Pistol)
	//	{
	//		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	//		Sleep(0);
	//		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	//		Sleep(0);
	//	}
	//}

	for (auto& item : m_actors)
	{
		IActor* p_Actor = item.second;
		if (!p_Actor)
			continue;
		if (!elimination_team(m_Actor, p_Actor))
			continue;

		if (IEntity* p_Entity = p_Actor->GetEntity())
		{
			update_flags(p_Entity);
			esp_silhouettes(p_Actor, p_Entity, m_IRender, Settings::ESP::EspSilhouettes, r_Green, g_Green, b_Green);

			if (Settings::Player::autoshoot == 1)
			{
				if (m_Actor->GetWorldQuery()->GetLookAtEntityId() == p_Actor->GetActorId())
				{
					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					Sleep(0);
					mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
					Sleep(0);
				}
			}

			p_names = p_Entity->GetName();
			p_classname = p_Entity->GetEntityClass()->GetName();
			p_weaponid = p_Actor->GetWeaponId();
			p_pos = p_Entity->GetWorldPos();
			p_head = get_enemy_head_position(p_Entity);

			if (!m_Actor->IsDead())
				continue;
			if (!p_Actor->IsDead())
				continue;

			if (Settings::Player::rotateshl == 1)
			{
				if (strstr(p_names.c_str(), XorString("Shield")) || strstr(p_names.c_str(), XorString("IronMan")) || strstr(p_names.c_str(), XorString("Drone")) || strstr(p_names.c_str(), XorString("HeavyTurret")))
				{
					rotate_actor(m_Actor, p_Actor);
				}
			}
			if (Settings::Aimbot::enabled == 1)
			{
				if (!world_to_screen(m_IRender, p_head, v_out))
					continue;
				if ((m_weaponid == WeaponsId::Grenade) ||
					(m_weaponid == WeaponsId::Knife) ||
					(m_weaponid == WeaponsId::AmmoBox) ||
					(m_weaponid == WeaponsId::MedicineChest) ||
					(m_weaponid == WeaponsId::Defibrillator) ||
					(m_weaponid == WeaponsId::ArmorPlate) ||
					(m_weaponid == WeaponsId::Mine))
					continue;
				if (strstr(m_itemname.c_str(), XorString("arl")))
					continue;
				if (Settings::Aimbot::turets < 1 && (strstr(p_names.c_str(), XorString("Heavy")) ||
					strstr(p_names.c_str(), XorString("Turret")) ||
					strstr(p_names.c_str(), XorString("Crusher")) ||
					strstr(p_classname.c_str(), XorString("Mantis")) ||
					strstr(p_classname.c_str(), XorString("SEDSoldier")) ||
					strstr(p_classname.c_str(), XorString("Helicopter")) ||
					strstr(p_names.c_str(), XorString("_Drone_")) ||
					strstr(p_names.c_str(), XorString("IronMan")) ||
					strstr(p_names.c_str(), XorString("SED")) ||
					strstr(p_names.c_str(), XorString("Cyborg")) ||
					strstr(p_names.c_str(), XorString("Destroyer")) ||
					strstr(p_names.c_str(), XorString("Drone_MG_Normal")) ||
					strstr(p_names.c_str(), XorString("SMGHeavy")) ||
					strstr(p_names.c_str(), XorString("CQBHeavy"))))
					continue;

				Vec3 vec_aim_bone = get_bone_by_id(p_Entity, get_bone_object());
				min_dist = get_hypotenuse(m_IRender, v_out);
				if (min_dist <= max_dist)
				{
					target.p_result = p_Actor->GetActorId();
					target.bone_hit_point = vec_aim_bone;
					max_dist = min_dist;
				}

				if (target.p_result != 0)
					set_bullet_pos(m_IWeapon, m_Actor, p_Actor, target.bone_hit_point);
			}
		}
	}
}

