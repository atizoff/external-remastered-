#include "CrySdk.h"

struct IPhysicalEntity;
struct ray_hit;
struct ray_hit_cached;
struct VecToScreen;
class IRender;
class IGame;
class SRWIParams;
class IPhysicalWorld;
class ISystem;
class SRWIParams;
class IEntitySystem;
class IEntityIt;
class ISkeletonPose;
class ICharacterInstance;
class IActorSystem;
class IActorIterator;
class IEntity;
class IEntityClass;
class IEntityProxy;
class IEntityProxyPhysics;
class IPhycialEntity;
class I3DEngine;
class IActor;
class IWorldQuery;
class IPlayer;
class IItem;
class IWeapon;
class IFireMode;
class IWeaponSpecific;
class IWeaponExtra;
class IWeaponCrypt;
class IWeaponAmmo;
class IGameRules;
class IActionGame;
class IGameFramework;
class ICVar;
class IEntityRenderProxy;

template <typename Type>
static bool IsValidPtr(Type* ptr)
{
	return (ptr && sizeof(ptr)) ? true : false;
}

typedef std::map<int32, IActor*> TActorMap;
TActorMap m_actors;

struct ray_hit
{
	float dist;
	IPhysicalEntity *pCollider;
	int ipart;
	int partid;
	short surface_idx;
	short idmatOrg;
	int foreignIdx;
	int iNode;
	Vec3 pt;
	Vec3 n;
	int bTerrain;
	int iPrim;
	ray_hit *next;
};

enum EWorldQuery
{
	eWQ_Raycast = 0,
	eWQ_Proximity,
	eWQ_InFrontOf,
	eWQ_BackRaycast,
	eWQ_EntitiesAround,
	eWQ_PhysicalEntitiesAround,
	eWQ_PhysicalEntitiesInFrontOf,
};

enum IsDeadFlag
{
	eUnknown = 0,
	eDead = 0xBF800000
};

enum ClassesId
{
	Stormtrooper,
	Unknow,
	Sniper,
	Medic,
	Engineer
};

enum GameModes
{
	eLobby = 0,  //лобби
	eDeathmatch, //команды
	eOccupation, //захват
	ePVE,        //ПВЕ
	eUndermining,//подрыв
	eStorm,      //Штурм
	eChopper,    //Мясорубка
	eDestruction,//уничтожение
	eDomination, //доминация
	eSurvival    //выживание
};

enum eWeaponZooming
{
	Zooming = 3,
	ZoomingToMove = 11,
	ZoomingToCrouch = 5
};

enum VisibleFlags
{
	eLineSight = 0x0F,
	eMetalSheets = 0x8,
	eGlass = 0xA
};

enum WeaponsId
{
	Rifle = 0x6C666972,
	Pistol = 0x74736970,
	Knife = 0x66696E6B,
	Grenade = 0x6E657267,
	AmmoBox = 0x6F6D6D61,
	MedicineChest = 0x6B64656D,
	Defibrillator = 0x6664,
	ArmorPlate = 0x61706572,
	Mine = 0x776E
};

enum WeaponFunctions
{
	NoiseLevel_Id = 0x4,
	SetAmmo_Id = 0x5,
	SetDamage_Id = 0x1B,
	SetRangeFire_Id = 0x1C,
	SetRecoil_Id = 0x42,
	SetSpread_Id = 0x5F,
	SetShutter_Id = 0x11,
	SpeedWeapon_Id = 0x35,
	SpeedKnife_Id = 0x53,
	SpeedKnifeLKM_Id = 0x37,
	SpeedKnifePKM_Id = 0x38,
	SpeedFire_Id = 0x50,
	SetRapidFire_Id = 0x4D,
	SpeedReload_Id = 0x48,
	SpeedChange_Id = 0x21,
	SetZoom_Id = 0x6C
};

enum eRenderNodeFlags
{
	eAllMap = 0x80018,
	eLimitDistance = 0x80008
};

/////////SilhouettesColors/////////
f32 a_Def = 0.000f;

/////////////////
f32 r_Red = 1.f;
f32 g_Red = 0.f;
f32 b_Red = 0.f;
/////////////////

/////////////////
f32 r_Green = 0.f;
f32 g_Green = 1.f;
f32 b_Green = 0.f;
/////////////////

/////////////////
f32 r_White = 1.f;
f32 g_White = 1.f;
f32 b_White = 1.f;
/////////////////

/////////////////
f32 r_Purple = 0.46f;
f32 g_Purple = 0.24f;
f32 b_Purple = 0.28f;
/////////////////

/////////////////
f32 r_Pink = 0.60f;
f32 g_Pink = 0.f;
f32 b_Pink = 0.25f;
/////////////////

/////////////////
f32 r_Yellow = 1.f;
f32 g_Yellow = 1.f;
f32 b_Yellow = 0.f;
/////////////////

/////////////////
f32 r_Orange = 1.f;
f32 g_Orange = 0.30f;
f32 b_Orange = 0.f;
/////////////////

/////////////////
f32 r_BlueSky = 0.f;
f32 g_BlueSky = 1.f;
f32 b_BlueSky = 1.f;
/////////////////
/////////SilhouettesColors/////////

enum EEntityProxy
{
	ENTITY_PROXY_RENDER,
	ENTITY_PROXY_PHYSICS,
	ENTITY_PROXY_SCRIPT,
	ENTITY_PROXY_SOUND,
	ENTITY_PROXY_AI,
	ENTITY_PROXY_AREA,
	ENTITY_PROXY_BOIDS,
	ENTITY_PROXY_BOID_OBJECT,
	ENTITY_PROXY_CAMERA,
	ENTITY_PROXY_FLOWGRAPH,
	ENTITY_PROXY_SUBSTITUTION,
	ENTITY_PROXY_TRIGGER,
	ENTITY_PROXY_ROPE,
	ENTITY_PROXY_ENTITYNODE,
	ENTITY_PROXY_USER,
	ENTITY_PROXY_LAST
};

enum ERWIFlagsShot
{
	eAmmoFlags = 0x31F,
	eAmmoWallShot = 0x10,
	eAmmoWallShotF = 0x75,
	eAmmoWallShotE = 0x7E
};

enum Bones
{
	Bone_Pose,
	Bone_Pelvis,
	Bone_Locomotion,
	Bone_Spine,
	Bone_L_Thigh,
	Bone_R_Thigh,
	Bone_Groin_Back,
	Bone_Groin_Front,
	Bone_Spine1,
	Bone_Spine2,
	Bone_Spine3,
	Bone_Wep_Law,
	Bone_Neck,
	Bone_Head,
	Bone_L_Clavicle,
	Bone_R_Clavicle,
	Bone_L_Eye,
	Bone_R_Eye,
	Bone_Camera,
	Bone_L_Eye_01,
	Bone_R_Eye_01,
	Bone_HNeck,
	Bone_Camera_01,
	Bone_HNeck_End,
	Bone_L_UpperArm,
	Bone_L_Forearm,
	Bone_L_Hand,
	Bone_L_ForeTwist,
	Bone_L_Finger0,
	Bone_L_Finger1,
	Bone_L_Finger2,
	Bone_L_Finger3,
	Bone_L_Finger4,
	Bone_Wep_Alt,
	Bone_L_Hand_Push,
	Bone_L_Finger01,
	Bone_L_Finger02,
	Bone_L_Finger11,
	Bone_L_Finger12,
	Bone_L_Finger21,
	Bone_L_Finger22,
	Bone_L_Finger31,
	Bone_L_Finger32,
	Bone_L_Finger41,
	Bone_L_Finger42,
	Bone_L_ForeTwist_1,
	Bone_L_ForeTwist_2,
	Bone_R_UpperArm,
	Bone_R_Forearm,
	Bone_R_Hand,
	Bone_R_ForeTwist,
	Bone_R_Finger0,
	Bone_R_Finger1,
	Bone_R_Finger2,
	Bone_R_Finger3,
	Bone_R_Finger4,
	Bone_WepBone,
	Bone_R_Hand_Push,
	Bone_R_Finger01,
	Bone_R_Finger02,
	Bone_R_Finger11,
	Bone_R_Finger12,
	Bone_R_Finger21,
	Bone_R_Finger22,
	Bone_R_Finger31,
	Bone_R_Finger32,
	Bone_R_Finger41,
	Bone_R_Finger42,
	Bone_R_ForeTwist_1,
	Bone_R_ForeTwist_2,
	Bone_L_Calf,
	Bone_L_Foot,
	Bone_L_Toe0,
	Bone_L_Heel,
	Bone_L_Heel01,
	Bone_L_Toe0Nub,
	Bone_L_Toe0Nub01,
	Bone_R_Calf,
	Bone_R_Foot,
	Bone_R_Toe0,
	Bone_R_Heel,
	Bone_R_Heel01,
	Bone_R_Toe0Nub,
	Bone_R_Toe0Nub01,
	Bone_Groin_Back_End,
	Bone_Groin_Front_End,
	Bone_Locator_Collider
};

bool IsFocusWindow(const wchar_t* ClassName, const wchar_t* WindowName)
{
	DWORD lProcessId = -2;
	DWORD processId = -1;
	HWND hWnd = FindWindowW(ClassName, WindowName);
	GetWindowThreadProcessId(hWnd, &processId);
	HWND foregroundWindow = GetForegroundWindow();
	GetWindowThreadProcessId(foregroundWindow, &lProcessId);
	return processId == lProcessId;
}

#define VK_CAPSLOCK			0x14
#define VK_0				0x30
#define VK_1				0x31
#define VK_2				0x32
#define VK_3				0x33
#define VK_4				0x34
#define VK_5				0x35
#define VK_6				0x36
#define VK_7				0x37
#define VK_8				0x38
#define VK_9				0x39
#define VK_A				0x41
#define VK_B				0x42
#define VK_C				0x43
#define VK_D				0x44
#define VK_E				0x45
#define VK_F				0x46
#define VK_G				0x47
#define VK_H				0x48
#define VK_I				0x49
#define VK_J				0x4A
#define VK_K				0x4B
#define VK_L				0x4C
#define VK_M				0x4D
#define VK_N				0x4E
#define VK_O				0x4F
#define VK_P				0x50
#define VK_Q				0x51
#define VK_R				0x52
#define VK_S				0x53
#define VK_T				0x54
#define VK_U				0x55
#define VK_V				0x56
#define VK_W				0x57
#define VK_X				0x58
#define VK_Y				0x59
#define VK_Z				0x5A
#define VK_LSHIFT			0xA0
#define VK_RSHIFT			0xA1
#define VK_LCONTROL			0xA2
#define VK_RCONTROL			0xA3
#define VK_LMENU			0xA4
#define VK_RMENU			0xA5
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)
#define RND_RANGE(min,max) (min + (rand() % (int)(max - min + 1)))