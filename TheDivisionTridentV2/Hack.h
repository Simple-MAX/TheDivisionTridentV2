#pragma once
#include "includes.h"

#define M_PI_2 1.57079632679
#define M_PI 3.14159265359f
#define M_3_PI_2 4.71238898038f
#define M_2_PI 6.28318530718f
#define PI 3.14159265
#define ABS(x) ((x < 0) ? (-x) : (x))

class Hack
{
public:
	Hack(const Hack&) = delete;

	static Hack& Get() { return s_Instance; }

	void EPSPVE(ImDrawList* pDraw);
	void EPSPVP(ImDrawList* pDraw);
	void Crosshair(ImDrawList* pDraw);
	void TeleportTo();
	void TeleportToWayPoint();
	void Aimbot();

	float GetRPM();
	void SetRPM(int);
	void NoRecoil();
	void NoSpread();
	void MovementSpeed();
	void NoReload();
	void ChangeClipSize();

private:
	Hack() {}
	static Hack s_Instance;

	/*TheDivisionSDK::Snowdrop::GameManager* GameManager = TheDivisionSDK::Snowdrop::GameManager::Get();
	TheDivisionSDK::Snowdrop::RClientClass* RClient = TheDivisionSDK::Snowdrop::RClientClass::Get();
	TheDivisionSDK::Snowdrop::ClientClass* Client = TheDivisionSDK::Snowdrop::ClientClass::Get();
	TheDivisionSDK::Snowdrop::WorldClass* World = TheDivisionSDK::Snowdrop::WorldClass::Get();*/
};

