#pragma once
#include "includes.h"
#include "IndexModule.h"

#define RCilentOffset 0x468EB28;
#define IndexModuleOffset 0x45D2230;


class ClassGameUI
{
public:
	ClassGameUI(const ClassGameUI&) = delete;
	static ClassGameUI* Get()
	{
		return *(ClassGameUI**)((uintptr_t)(GetModuleHandle(NULL)) + 0x44FBBE8);
	}
public:
	char pad_0000[144]; //0x0000
	class ClassUI* UI; //0x0090
	char pad_0098[1000]; //0x0098
}; //Size: 0x0480

class ClassUI
{
public:
	char pad_0000[24]; //0x0000
	class ClassMap* Map; //0x0018
	char pad_0020[104]; //0x0020
}; //Size: 0x0088

class ClassMap
{
public:
	char pad_0000[856]; //0x0000
	class ClassWaypoint* Waypoint; //0x0000
	char pad_0360[40]; //0x0360
}; //Size: 0x0388

class ClassWaypoint
{
public:
	char pad_0000[336]; //0x0000
	class ClassWaypointPosition* WaypointPosition; //0x0150
	char pad_0158[48]; //0x0158
}; //Size: 0x0188

class ClassWaypointPosition
{
public:
	char pad_0000[68]; //0x0000
	float X; //0x0044
	float Y; //0x0048
	float Z; //0x004C
	char pad_0050[76]; //0x0050
}; //Size: 0x009C


class Game
{
public:
	Game(const Game&) = delete;
	static Game* Get()
	{
		return (Game*)((uintptr_t)(GetModuleHandle(NULL)) + 0x468EB28);
	}
public:
	class ClassGameManager* GameManager; //0x0000
	char pad_0008[2848]; //0x0008
	D3DXMATRIX ViewMatrix; //0x0B28
	char pad_0B68[536]; //0x0B68
	float ResolutionX; //0x0D80
	float ResolutionY; //0x0D84
}; //Size: 0x0D88
class ClassGameManager
{
public:
	char pad_0000[288]; //0x0000
	class ClassClient* Client; //0x0120
	char pad_0128[168]; //0x0128
}; //Size: 0x01D0
//static_assert(sizeof(ClassGameManager) == 0x1D0);

class ClassClient
{
public:
	char pad_0000[40]; //0x0000
	class ClassWorld* World; //0x0028
	char pad_0030[88]; //0x0030
}; //Size: 0x0088
//static_assert(sizeof(ClassClient) == 0x88);

class ClassWorld
{
public:
	char pad_0000[120]; //0x0000
	class ClassLootList* LootList; //0x0078
	char pad_0080[592]; //0x0080
	class ClassCameraList* CameraList; //0x02D0
	char pad_02D8[360]; //0x02D8
	class ClassEntityList* EntityList; //0x0440
	int32_t NumberOfEntities; //0x0448
	int32_t MaxNumberOfEntities; //0x044C
}; //Size: 0x0450
//static_assert(sizeof(ClassWorld) == 0x450);

class ClassLootList
{
public:
	char pad_0000[24]; //0x0000
	class ClassLoot* LootArray[1]; //0x0018
	int32_t LootCount; //0x0020
}; //Size: 0x0024
//static_assert(sizeof(ClassLootList) == 0x24);

class ClassCameraList
{
public:
	char pad_0000[24]; //0x0000
	class ClassCameraArray* CameraArray; //0x0018
}; //Size: 0x0020
//static_assert(sizeof(ClassCameraList) == 0x20);

class ClassCameraArray
{
public:
	char pad_0000[176]; //0x0000
	class ClassCamera* Camera; //0x00B0
	char pad_00B8[24]; //0x00B8
}; //Size: 0x00D0
//static_assert(sizeof(ClassCameraArray) == 0xD0);

class ClassCamera
{
public:
	char pad_0000[120]; //0x0000
	class ClassAgentCamera* AgentCamera; //0x0078
}; //Size: 0x0080
//static_assert(sizeof(ClassCamera) == 0x80);

class ClassAgentCamera
{
public:
	char pad_0000[192]; //0x0000
	float Yaw; //0x00C0
	float Pitch; //0x00C4
}; //Size: 0x00C8
//static_assert(sizeof(ClassAgentCamera) == 0xC8);

class ClassEntityList
{
public:
	class ClassEntity* EntityArray[27]; //0x0000
}; //Size: 0x00D8
//static_assert(sizeof(ClassEntityList) == 0xD8);

class ClassEntity
{
public:
	char pad_0000[40]; //0x0000
	class ClassEntityInfo* EntityInfo; //0x0028
	char pad_0030[16]; //0x0030
	D3DXMATRIX TransformMatrix; //0x0040
	D3DXVECTOR3 Position; //0x0080
	float Yaw; //0x008C
	char pad_0090[256]; //0x0090
	class ClassDeadZoneInfo* DeadZoneInfo; //0x0190
	char pad_0198[40]; //0x0198
	bool IsDead; //0x01C0
	char pad_01C1[15]; //0x01C1
	class ClassPositionData* PositionData; //0x01D0
	char EntityType[8]; //0x01D8
	char pad_01E0[372]; //0x01E0
	bool IsGadget; //0x0354
	char pad_0355[27]; //0x0355
	char Name[12]; //0x0370
	char pad_037C[40]; //0x037C
	int32_t Type0; //0x03A4
	char pad_03A8[12]; //0x03A8
	int32_t Type1; //0x03B4
	char pad_03B8[24]; //0x03B8
	int32_t Level; //0x03D0
	int32_t DarkZoneLevel; //0x03D4
	char pad_03D8[12]; //0x03D8
	int32_t UndergroundLevel; //0x03E4
	char pad_03E8[8]; //0x03E8
	int32_t PvPLevel; //0x03F0
	char pad_03F4[12]; //0x03F4
	bool IsHuman; //0x0400
	char pad_0401[40]; //0x0401
	char GloballyUniqueIdentifier[37]; //0x0429
	char pad_044E[218]; //0x044E
	class ClassIndexInfo* IndexInfo; //0x0528
	char pad_0530[168]; //0x0530
	class ClassHealthController* HealthController; //0x05D8
	char pad_05E0[80]; //0x05E0
	class ClassCrosshair* Crosshair; //0x0630
	char pad_0638[204]; //0x0638
	D3DXVECTOR3 AimingPosition; //0x0704
	D3DXVECTOR3 AimingPosition1; //0x0710
	char pad_071C[24]; //0x071C
	int32_t SelectedWeaponIndex; //0x0734
	char pad_0738[16]; //0x0738
	bool IsFriendly; //0x0748
	char pad_0749[3]; //0x0749
	bool IsRunning; //0x074C
	char pad_074D[3]; //0x074D
	bool IsShooting; //0x0750
	char pad_0751[11]; //0x0751
	bool IsRogue; //0x075C
	char pad_075D[3]; //0x075D
	bool IsAiming; //0x0760
	char pad_0761[2]; //0x0761
	bool IsFriendlyNPC; //0x0763
	char pad_0764[19]; //0x0764
	bool IsNotHuman; //0x0777
	char pad_0778[184]; //0x0778
	int32_t PlayerType; //0x0830
}; //Size: 0x0834
//static_assert(sizeof(ClassEntity) == 0x834);

class ClassIndexInfo 
{
public:
	struct Info
	{
		char pad_0000[4]; //0x0000
		float value; //0x0004
		char pad_0008[56]; //0x0008
	};
public:

	Info* GetInfoByIndex(unsigned int index)
	{
		if (!m_AttributeComponent || !m_AttributeComponent->info)
			return nullptr;

		return &m_AttributeComponent->info[index];
	}

	Info* GetFireRate()
	{
		uint32_t index = 0;
		CIndexInfo::Get().GetAttribute(CIndexModule::RPMFinal, index);
		return GetInfoByIndex(index);
	}

private:
	char unknown[0x28];

	struct AttributeComponent
	{
		char unknown[0x78];
		Info* info;
	} *m_AttributeComponent;
};

class ClassEntityInfo
{
public:
	char pad_0000[136]; //0x0000
}; //Size: 0x0088
//static_assert(sizeof(ClassEntityInfo) == 0x88);

class ClassDeadZoneInfo
{
public:
	char pad_0000[136]; //0x0000
}; //Size: 0x0088
//static_assert(sizeof(ClassDeadZoneInfo) == 0x88);

class ClassPositionData
{
public:
	char pad_0000[544]; //0x0000
	class ClassPlayerCoordinate* PlayerCoordinate; //0x0220
	char pad_0228[4664]; //0x0228
	class ClassBoneMatrix* BoneMatrix; //0x1460
	int32_t MaxBones; //0x1468
}; //Size: 0x146C
//static_assert(sizeof(ClassPositionData) == 0x146C);

class ClassBoneMatrix
{
public:
	D3DXMATRIX Lowerbody; //0x0000
	D3DXMATRIX Centerbody; //0x0040
	D3DXMATRIX Midbody; //0x0080
	D3DXMATRIX Upperbody; //0x00C0
	D3DXMATRIX Neck; //0x0100
	D3DXMATRIX Head; //0x0140
	D3DXMATRIX bone6; //0x0180
	D3DXMATRIX LeftShoulder; //0x01C0
	D3DXMATRIX bone8; //0x0200
	D3DXMATRIX bone9; //0x0240
	D3DXMATRIX bone10; //0x0280
	D3DXMATRIX LeftHand; //0x02C0
	D3DXMATRIX bone12; //0x0300
	D3DXMATRIX bone13; //0x0340
	D3DXMATRIX bone14; //0x0380
	D3DXMATRIX bone15; //0x03C0
	D3DXMATRIX bone16; //0x0400
	D3DXMATRIX bone17;
	D3DXMATRIX bone18;
	D3DXMATRIX bone19;
	D3DXMATRIX bone20; //0x0280
	D3DXMATRIX bone21; //0x02C0
	D3DXMATRIX bone22; //0x0300
	D3DXMATRIX bone23; //0x0340
	D3DXMATRIX bone24; //0x0380
	D3DXMATRIX bone25; //0x03C0
	D3DXMATRIX bone26; //0x0400
	D3DXMATRIX bone27;
	D3DXMATRIX bone28;
	D3DXMATRIX bone29;
	D3DXMATRIX bone30; //0x0280
	D3DXMATRIX bone31; //0x02C0
	D3DXMATRIX bone32; //0x0300
	D3DXMATRIX bone33; //0x0340
	D3DXMATRIX bone34; //0x0380
	D3DXMATRIX bone35; //0x03C0
	D3DXMATRIX bone36; //0x0400
	D3DXMATRIX RightShoulder;
	D3DXMATRIX bone38;
	D3DXMATRIX bone39;
	D3DXMATRIX bone40; //0x0280
	D3DXMATRIX RightHand; //0x02C0
	D3DXMATRIX bone42; //0x0300
	D3DXMATRIX bone43; //0x0340
	D3DXMATRIX bone44; //0x0380
	D3DXMATRIX bone45; //0x03C0
	D3DXMATRIX bone46; //0x0400
	D3DXMATRIX bone47;
	D3DXMATRIX bone48;
	D3DXMATRIX bone49;
	D3DXMATRIX bone50; //0x0280
	D3DXMATRIX bone51; //0x02C0
	D3DXMATRIX bone52; //0x0300
	D3DXMATRIX bone53; //0x0340
	D3DXMATRIX bone54; //0x0380
	D3DXMATRIX bone55; //0x03C0
	D3DXMATRIX bone56; //0x0400
	D3DXMATRIX bone57;
	D3DXMATRIX bone58;
	D3DXMATRIX bone59;
	D3DXMATRIX bone60; //0x0280
	D3DXMATRIX bone61; //0x02C0
	D3DXMATRIX bone62; //0x0300
	D3DXMATRIX bone63; //0x0340
	D3DXMATRIX bone64; //0x0380
	D3DXMATRIX bone65; //0x03C0
	D3DXMATRIX bone66; //0x0400
	D3DXMATRIX bone67;
	D3DXMATRIX bone68;
	D3DXMATRIX bone69;
	D3DXMATRIX bone70; //0x0280
	D3DXMATRIX bone71; //0x02C0
	D3DXMATRIX bone72; //0x0300
	D3DXMATRIX bone73; //0x0340
	D3DXMATRIX RightMidLeg; //0x0380
	D3DXMATRIX bone75; //0x03C0
	D3DXMATRIX LeftLowerLeg; //0x0400LeftLowerLeg
	D3DXMATRIX bone77;
	D3DXMATRIX bone78;
	D3DXMATRIX RightUpperLeg;
	D3DXMATRIX bone80; //0x0280
	D3DXMATRIX bone81; //0x02C0
	D3DXMATRIX LeftMidLeg; //0x0300
	D3DXMATRIX bone83; //0x0340
	D3DXMATRIX RightLowerLeg; //0x0380
	D3DXMATRIX bone85; //0x03C0
	D3DXMATRIX bone86; //0x0400
	D3DXMATRIX LeftUpperLeg;
	D3DXMATRIX bone88;
	D3DXMATRIX bone89;
	D3DXMATRIX bone90; //0x0280
	D3DXMATRIX bone91; //0x02C0
	D3DXMATRIX bone92; //0x0300
	D3DXMATRIX bone93; //0x0340
	D3DXMATRIX bone94; //0x0380
	D3DXMATRIX bone95; //0x03C0
}; //Size: 0x0440

class ClassBoneMatrixArray
{
public:
	D3DXMATRIX bone[95]; //0x0000
}; //Size: 0x0440


class ClassPlayerCoordinate
{
public:
	char pad_0000[632]; //0x0000
	class ClassLocalPlayerCoordinate* LocalPlayerCoordinate; //0x0278
}; //Size: 0x0280
//static_assert(sizeof(ClassPlayerCoordinate) == 0x280);

class ClassLocalPlayerCoordinate
{
public:
	char pad_0000[112]; //0x0000
	float PositionX; //0x0070
	float PositionY; //0x0074
	float PositionZ; //0x0078
}; //Size: 0x007C
//static_assert(sizeof(ClassLocalPlayerCoordinate) == 0x7C);

class ClassAttributeComponent
{
public:
	char pad_0000[40]; //0x0000
	class ClassAttributeDictionary* AttributeDictionary; //0x0028
}; //Size: 0x0030
//static_assert(sizeof(ClassAttributeComponent) == 0x30);

class ClassAttributeDictionary
{
public:
	char pad_0000[120]; //0x0000
	class ClassAttribute* AttributeArray; //0x0078
}; //Size: 0x9CB8
//static_assert(sizeof(ClassAttributeDictionary) == 0x9CB8);

class ClassAttribute
{
public:
	char pad_0000[4]; //0x0000
	float value; //0x0004
	char pad_0008[56]; //0x0008
}; //Size: 0x000C
//static_assert(sizeof(ClassAttribute) == 0xC);

class ClassLoot
{
public:
}; //Size: 0x0000
//static_assert(sizeof(ClassLoot) == 0x0);

class ClassCrosshair
{
public:
	char pad_0000[13128]; //0x0000
	float Pitch; //0x3348
	char pad_334C[32]; //0x334C
	float Yaw; //0x336C
	char pad_3370[2612]; //0x3370
}; //Size: 0x3DA4
//static_assert(sizeof(ClassCrosshair) == 0x3894);

class ClassHealthController
{
public:
	char pad_0000[168]; //0x0000
	int32_t Health; //0x00A8
	int32_t MaxHealth; //0x00AC
}; //Size: 0x00B0
//static_assert(sizeof(ClassHealthController) == 0xB0);