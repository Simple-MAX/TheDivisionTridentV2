#include "includes.h"

Hack Hack::s_Instance;

typedef struct {
	u64 ptr;
	b32 is_gadget;
	b32 is_player;
	u32 level;
	u32 type;
	i32 hp_cur;
	i32 hp_max;
	f32 yaw;
	f32 box_width;
	f32 dist_dot;
	vec3 pos;
	vec3 torso;
	vec3 head;
	vec3 delta;
	i8 name[24];
} Entity;

enum esp_info_position
{
	RIGHT,
	CENTER_DOWN,
	CENTER_UP
};

struct esp_info_s
{
	esp_info_s(const std::string name, const ImColor color, const int position = RIGHT)
	{
		f_name = name; f_color = color; f_position = position;
	}

	std::string f_name;
	int f_position;
	ImColor f_color;
};

D3DXVECTOR3 Subtract(D3DXVECTOR3 src, D3DXVECTOR3 dst)
{
	D3DXVECTOR3 diff;
	diff.x = src.x - dst.x;
	diff.y = src.y - dst.y;
	diff.z = src.z - dst.z;
	return diff;
};

float Magnitude(D3DXVECTOR3 vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
};

float Distance(D3DXVECTOR3 src, D3DXVECTOR3 dst)
{
	D3DXVECTOR3 diff = Subtract(src, dst);
	return Magnitude(diff);
}

D3DXVECTOR2 CalcAngle(D3DXVECTOR3 src, D3DXVECTOR3 dst)
{
	D3DXVECTOR2 angle;
	angle.x = atan2f(dst.x - src.x, dst.y - src.y);
	angle.y = asinf((dst.z - src.z) / Distance(src, dst));

	return angle;
}

bool CheckBlackList(const char* name)
{
	const char* EntName[] = {
			" ",
			"",
			"HUB",
			"Seagull",
			"Seeker Mine",
			"Tesla Trap",
			"Turrent",
			"BOO",
			"Midtown East",
			"Brooklyn",
			"Hudson Yards",
			"Roy Benitez",
			"Jessica Kandel",
			"Times Square",
			"Kips Bay",
			"Stuyvesant",
			"Murray Hill",
			"Garment",
			"Tenderloin",
			"Clinton",
			"Hells Kitchen",
			"Gramercy",
			"Turtle Bay",
			"Police Shotgun",
			"Police Pistol",
			"Gear Vendor",
			"Weapons Vendor",
			"Mods Vendor",
			"Vanity Vendor",
			"Flatiron",
			"Rat",
			"Dog",
			"Raven",
			"Raven Fx",
			"Pigeon",
			"Pigeon Fx"
	};

	for (int i = 0; i < (sizeof(EntName) / sizeof(*EntName)); i++)
	{
		if (strcmp(EntName[i], name) == 0) {
			break;
			return true;
		}
	};
	return false;
}

vec2 w2s(D3DXVECTOR3 pos, D3DXMATRIX world, f32 hx, f32 hy) {
	vec3 tv = vec3_set(world._41, world._42, world._43);
	vec3 up = vec3_set(world._21, world._22, world._23);
	vec3 ri = vec3_set(world._11, world._12, world._13);

	f32 w = (tv.x * pos.x + tv.y * pos.y + tv.z * pos.z) + world._44;

	if (w < 0.098f) {
		return vec2_zero();
	}

	f32 x = (ri.x * pos.x + ri.y * pos.y + ri.z * pos.z) + world._14;
	f32 y = (up.x * pos.x + up.y * pos.y + up.z * pos.z) + world._24;

	return vec2_set(hx * (1.0f + x / w), hy * (1.0f - y / w));
}

bool WorldToScreen(D3DXVECTOR3 pos, D3DXVECTOR2& screen, float matrix[16], int windowWidth, int windowHeight)
{
	//Matrix-vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
	D3DXVECTOR4 clipCoords;
	clipCoords.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
	clipCoords.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
	clipCoords.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
	clipCoords.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

	if (clipCoords.w < 0.098f)
		return false;

	//perspective division, dividing by clip.W = Normalized Device Coordinates
	D3DXVECTOR3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
	screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);
	return true;
}

void GetHead(ClassEntityList* EntityList,int playerIndex, D3DXVECTOR3& out)
{
	out.x = EntityList->EntityArray[playerIndex]->PositionData->BoneMatrix->Head._41;
	out.y = EntityList->EntityArray[playerIndex]->PositionData->BoneMatrix->Head._42;
	out.z = EntityList->EntityArray[playerIndex]->PositionData->BoneMatrix->Head._43;
};

void GetLeftLowerLeg(ClassEntityList* EntityList, int playerIndex, D3DXVECTOR3& out)
{
	out.x = EntityList->EntityArray[playerIndex]->PositionData->BoneMatrix->LeftLowerLeg._41;
	out.y = EntityList->EntityArray[playerIndex]->PositionData->BoneMatrix->LeftLowerLeg._42;
	out.z = EntityList->EntityArray[playerIndex]->PositionData->BoneMatrix->LeftLowerLeg._43;
};

void GetRightLowerLeg(ClassEntityList* EntityList, int playerIndex, D3DXVECTOR3& out)
{
	out.x = EntityList->EntityArray[playerIndex]->PositionData->BoneMatrix->RightLowerLeg._41;
	out.y = EntityList->EntityArray[playerIndex]->PositionData->BoneMatrix->RightLowerLeg._42;
	out.z = EntityList->EntityArray[playerIndex]->PositionData->BoneMatrix->RightLowerLeg._43;
};

void GetLeftShoulder(ClassEntityList* EntityList, int playerIndex, D3DXVECTOR3& out)
{
	out.x = EntityList->EntityArray[playerIndex]->PositionData->BoneMatrix->LeftShoulder._41;
	out.y = EntityList->EntityArray[playerIndex]->PositionData->BoneMatrix->LeftShoulder._42;
	out.z = EntityList->EntityArray[playerIndex]->PositionData->BoneMatrix->LeftShoulder._43;
};

void GetRightShoulder(ClassEntityList* EntityList, int playerIndex, D3DXVECTOR3& out)
{
	out.x = EntityList->EntityArray[playerIndex]->PositionData->BoneMatrix->RightShoulder._41;
	out.y = EntityList->EntityArray[playerIndex]->PositionData->BoneMatrix->RightShoulder._42;
	out.z = EntityList->EntityArray[playerIndex]->PositionData->BoneMatrix->RightShoulder._43;
};

void GetLeftHand(ClassEntityList* EntityList, int playerIndex, D3DXVECTOR3& out)
{
	out.x = EntityList->EntityArray[playerIndex]->PositionData->BoneMatrix->LeftHand._41;
	out.y = EntityList->EntityArray[playerIndex]->PositionData->BoneMatrix->LeftHand._42;
	out.z = EntityList->EntityArray[playerIndex]->PositionData->BoneMatrix->LeftHand._43;
};

void GetRightHand(ClassEntityList* EntityList, int playerIndex, D3DXVECTOR3& out)
{
	out.x = EntityList->EntityArray[playerIndex]->PositionData->BoneMatrix->RightHand._41;
	out.y = EntityList->EntityArray[playerIndex]->PositionData->BoneMatrix->RightHand._42;
	out.z = EntityList->EntityArray[playerIndex]->PositionData->BoneMatrix->RightHand._43;
};

float GetDistance(D3DXVECTOR3 one, D3DXVECTOR3 two)
{
	D3DXVECTOR3 delta = D3DXVECTOR3(two.x - one.x, two.y - one.y, two.z - one.z);

	return sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
};

void DrawBox(ImDrawList* pDraw, ClassEntityList* EntityList, int index,const std::string name)
{
	static std::vector<esp_info_s> info;
	float pResolutionX = Game::Get()->ResolutionX;
	float pResolutionY = Game::Get()->ResolutionY;
	D3DXVECTOR2 footCord, headCord;
	D3DXVECTOR3 headPosition;

	GetHead(EntityList, index, headPosition);

	WorldToScreen(headPosition, headCord, Game::Get()->ViewMatrix, pResolutionX, pResolutionY);
	WorldToScreen(EntityList->EntityArray[index]->Position, footCord, Game::Get()->ViewMatrix, pResolutionX, pResolutionY);

	float height = headCord.y - footCord.y;
	float w = height / 4.f;
	float left = footCord.x - w;
	float right = footCord.x + w;

	//int deltaX = (headCord.x - footCord.x);

	pDraw->AddRect(ImVec2(left, headCord.y - 10), ImVec2(right, footCord.y), ImColor(255, 255, 250), 0.f, 0.f);
	pDraw->AddText(ImVec2(headCord.x, headCord.y), ImColor(255, 255, 250), "o");
	//pDraw->AddCircle(ImVec2(headCord.x, headCord.y), 10, ImColor(255, 48, 79), 360);

	/*int healthPro = (((EntityList->EntityArray[index]->HealthController->MaxHealth / 100 ) * (EntityList->EntityArray[index]->HealthController->Health / 100) / 100) / 100 ) / 100;

	ImVec2 healthTop, healthBottom;
	
	healthBottom.y = footCord.y;
	healthBottom.x = headCord.x + (height / 4.f) + 2;

	healthTop.y = headCord.y;
	healthTop.x = headCord.x + (height / 4.f) + 2;


	pDraw->AddLine(ImVec2(healthTop.x, healthTop.y - (healthPro * 10)), healthBottom, ImColor(34, 234, 170), 0.f);
	if (healthPro < 10)
	{
		pDraw->AddLine(healthTop, healthBottom, ImColor(34, 234, 170), 0.f);
	}
	else if (healthPro < 9)
	{
		pDraw->AddLine(ImVec2(healthTop.x, healthTop.y - 10), healthBottom, ImColor(34, 234, 170), 0.f);
	}
	else if (healthPro < 8)
	{
		pDraw->AddLine(ImVec2(healthTop.x, healthTop.y - 20), healthBottom, ImColor(34, 234, 170), 0.f);
	}
	else if (healthPro < 7)
	{
		pDraw->AddLine(ImVec2(healthTop.x, healthTop.y - 30), healthBottom, ImColor(34, 234, 170), 0.f);
	}
	else if (healthPro < 6)
	{
		pDraw->AddLine(ImVec2(healthTop.x, healthTop.y - 40), healthBottom, ImColor(34, 234, 170), 0.f);
	}
	else if (healthPro < 5)
	{
		pDraw->AddLine(ImVec2(healthTop.x, healthTop.y - 50), healthBottom, ImColor(34, 234, 170), 0.f);
	}
	else if (healthPro < 4)
	{
		pDraw->AddLine(ImVec2(healthTop.x, healthTop.y - 60), healthBottom, ImColor(34, 234, 170), 0.f);
	}
	else if (healthPro < 3)
	{
		pDraw->AddLine(ImVec2(healthTop.x, healthTop.y - 70), healthBottom, ImColor(34, 234, 170), 0.f);
	}
	else if (healthPro < 2)
	{
		pDraw->AddLine(ImVec2(healthTop.x, healthTop.y - 80), healthBottom, ImColor(34, 234, 170), 0.f);
	}
	else if (healthPro < 1)
	{
		pDraw->AddLine(ImVec2(healthTop.x, healthTop.y - 90), healthBottom, ImColor(34, 234, 170), 0.f);
	}
	

	const auto text_size = ImGui::CalcTextSize(name.c_str());

	auto pos = ImVec2(headCord.x, headCord.y);

	pos = ImVec2(headCord.x / 2  - text_size.x / 2, pos.y - 5 - text_size.y);

	pDraw->AddText(pos, ImColor(255, 255, 250), name.c_str());*/
}

void DrawBoxNew(ImDrawList* pDraw, ClassEntityList* EntityList, int index, char* name)
{
	float pResolutionX = Game::Get()->ResolutionX;
	float pResolutionY = Game::Get()->ResolutionY;

	static D3DXVECTOR2 playerCord, headCord, leftHandCord, rightHandCord, leftLegCord, rightLegCord, myheadc;
	static D3DXVECTOR3 headPosition, leftHandPosition, rightHandPosition, myheadp;

	GetHead(EntityList, index, headPosition);
	GetRightHand(EntityList, index, rightHandPosition);
	GetLeftHand(EntityList, index, leftHandPosition);
	GetHead(EntityList, 0, myheadp);

	WorldToScreen(myheadp, myheadc, Game::Get()->ViewMatrix, pResolutionX, pResolutionY);
	WorldToScreen(headPosition, headCord, Game::Get()->ViewMatrix, pResolutionX, pResolutionY);
	WorldToScreen(leftHandPosition, leftHandCord, Game::Get()->ViewMatrix, pResolutionX, pResolutionY);
	WorldToScreen(rightHandPosition, rightHandCord, Game::Get()->ViewMatrix, pResolutionX, pResolutionY);
	WorldToScreen(EntityList->EntityArray[index]->Position, playerCord, Game::Get()->ViewMatrix, pResolutionX, pResolutionY);

	int height = ABS(headCord.y - playerCord.y);

	leftHandCord.y = rightHandCord.y = headCord.y;
	leftLegCord.y = rightLegCord.y = playerCord.y;
	leftLegCord.x = leftHandCord.x;
	rightLegCord.x = rightHandCord.x;


	int distance = Distance(EntityList->EntityArray[0]->Position, EntityList->EntityArray[index]->Position);

	std::string tmp = std::to_string(distance);
	char const* num_char = tmp.c_str();

	// currentHealt = EntityList->EntityArray[index]->HealthController->Health * 100.f / EntityList->EntityArray[index]->HealthController->MaxHealth;
	//D3DXVECTOR2 topHealt, bottomHealt;

	//bottomHealt.y = playerCord.y;
	//bottomHealt.x = leftHandCord.x - 10;

	//topHealt.y = headCord.y - currentHealt;
	//topHealt.x = leftHandCord.x - 10;

	pDraw->AddText(ImVec2(leftHandCord.x, headCord.y - 30), ImColor(255, 255, 240), num_char);
	pDraw->AddText(ImVec2(leftHandCord.x, headCord.y - 15), ImColor(255, 255, 240), name);
	pDraw->AddRect(ImVec2(leftHandCord.x, leftHandCord.y), ImVec2(rightLegCord.x, rightLegCord.y), ImColor(255, 255, 250));
	//pDraw->AddLine(ImVec2(topHealt.x, topHealt.y), ImVec2(bottomHealt.x, bottomHealt.y), ImColor(250, 0, 0), 2.f);
};

void DrawBone(ImDrawList* pDraw, ClassEntityList* EntityList, int index, char* name)
{
	float pResolutionX = Game::Get()->ResolutionX;
	float pResolutionY = Game::Get()->ResolutionY;

	static D3DXVECTOR2 playerCord, headCord, leftHandCord, rightHandCord, leftLegCord, rightLegCord, myheadc;
	static D3DXVECTOR3 headPosition, leftHandPosition, rightHandPosition, myheadp;

	GetHead(EntityList, index, headPosition);
	GetRightHand(EntityList, index, rightHandPosition);
	GetLeftHand(EntityList, index, leftHandPosition);
	GetHead(EntityList, 0, myheadp);

	WorldToScreen(myheadp, myheadc, Game::Get()->ViewMatrix, pResolutionX, pResolutionY);
	WorldToScreen(headPosition, headCord, Game::Get()->ViewMatrix, pResolutionX, pResolutionY);
	WorldToScreen(leftHandPosition, leftHandCord, Game::Get()->ViewMatrix, pResolutionX, pResolutionY);
	WorldToScreen(rightHandPosition, rightHandCord, Game::Get()->ViewMatrix, pResolutionX, pResolutionY);
	WorldToScreen(EntityList->EntityArray[index]->Position, playerCord, Game::Get()->ViewMatrix, pResolutionX, pResolutionY);

	int distance = Distance(EntityList->EntityArray[0]->Position, EntityList->EntityArray[index]->Position);

	std::string tmp = std::to_string(distance);
	char const* num_char = tmp.c_str();

	pDraw->AddRect(ImVec2(headPosition.x, headPosition.y), ImVec2(rightLegCord.x, rightLegCord.y), ImColor(0, 255, 240));
};

void Hack::EPSPVE(ImDrawList* pDraw)
{
	// todo fix the bones
	int NumberOfEntities = Game::Get()->GameManager->Client->World->NumberOfEntities;
	ClassEntityList* EntityList = Game::Get()->GameManager->Client->World->EntityList;
	float pResolutionX = Game::Get()->ResolutionX;
	float pResolutionY = Game::Get()->ResolutionY;
	static D3DXVECTOR2 headCord, playerCord, leftHandCord, rightHandCord, leftLegCord, rightLegCord;
	static D3DXVECTOR3 headPosition, playerPosition, leftHandPosition, rightHandPosition, leftLegPosition, rightLegPosition;

	for (int i = 0; i < NumberOfEntities; i++)
	{
		if (EntityList->EntityArray[i]->IsDead) continue;
		if (EntityList->EntityArray[i]->PlayerType < 0) continue;
		if (EntityList->EntityArray[i]->IsFriendly) continue;
		if (EntityList->EntityArray[i]->IsGadget) continue;
		if (i == 0) continue;
		if (strcmp(" ", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("HUB", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Pigeon Fx", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Pigeon", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Raven Fx", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Raven", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Dog", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Rat", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Flatiron", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Vanity Vendor", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Mods Vendor", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Weapons Vendor", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Gear Vendor", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Police Pistol", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Police Shotgun", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Turtle Bay", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Gramercy", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Hells Kitchen", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Clinton", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Tenderloin", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Garment", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Murray Hill", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Stuyvesant", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Kips Bay", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Times Square", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Jessica Kandel", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Roy Benitez", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Hudson Yards", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Brooklyn", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Midtown East", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("BOO", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Turrent", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Tesla Trap", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Seeker Mine", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Seagull", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Civilian", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("JTF", EntityList->EntityArray[i]->Name) == 0) continue;
		if (!WorldToScreen(EntityList->EntityArray[i]->Position, playerCord, Game::Get()->ViewMatrix, pResolutionX, pResolutionY)) continue;
		DrawBox(pDraw, EntityList, i, EntityList->EntityArray[i]->Name);
		//DrawBoxNew(pDraw, EntityList, i, EntityList->EntityArray[i]->Name);
		//pDraw->AddLine(ImVec2(playerCord.x, playerCord.y), ImVec2(pResolutionX / 2, pResolutionY), ImColor(0, 255, 240));
	}
};

void Hack::EPSPVP(ImDrawList* pDraw)
{
	int NumberOfEntities = Game::Get()->GameManager->Client->World->NumberOfEntities;
	ClassEntityList* EntityList = Game::Get()->GameManager->Client->World->EntityList;
	float pResolutionX = Game::Get()->ResolutionX;
	float pResolutionY = Game::Get()->ResolutionY;
	static D3DXVECTOR2 playerCord;
	static D3DXVECTOR2 HeadCord;
	static D3DXVECTOR3 HeadPosition;

	
	for (int i = 0; i < NumberOfEntities; i++)
	{
		if (EntityList->EntityArray[i]->IsDead) continue;
		if (EntityList->EntityArray[i]->PlayerType != -1) continue;
		if (i == 0 ) continue; 
		if (!WorldToScreen(EntityList->EntityArray[i]->Position, playerCord, Game::Get()->ViewMatrix, pResolutionX, pResolutionY)) continue;
		
		DrawBox(pDraw, EntityList, i, EntityList->EntityArray[i]->Name);
		//DrawBoxNew(pDraw, EntityList, i, EntityList->EntityArray[i]->Name);
		//pDraw->AddLine(ImVec2(playerCord.x, playerCord.y), ImVec2(pResolutionX / 2, pResolutionY), ImColor(0, 255, 240));
	}
};

void Hack::Crosshair(ImDrawList* pDraw)
{
	static int CrosshairSize = 10;
	static float pResolutionX = Game::Get()->ResolutionX;
	static float pResolutionY = Game::Get()->ResolutionY;

	pDraw->AddLine(ImVec2(pResolutionX / 2, pResolutionY / 2), ImVec2(pResolutionX / 2, pResolutionY / 2 + CrosshairSize), ImColor(33, 230, 193));
	pDraw->AddLine(ImVec2(pResolutionX / 2, pResolutionY / 2), ImVec2(pResolutionX / 2 + CrosshairSize, pResolutionY / 2), ImColor(33, 230, 193));
	pDraw->AddLine(ImVec2(pResolutionX / 2 - CrosshairSize, pResolutionY / 2), ImVec2(pResolutionX / 2, pResolutionY / 2), ImColor(33, 230, 193));
	pDraw->AddLine(ImVec2(pResolutionX / 2, pResolutionY / 2 - CrosshairSize), ImVec2(pResolutionX / 2, pResolutionY / 2), ImColor(33, 230, 193));
	pDraw->AddCircle(ImVec2(pResolutionX / 2, pResolutionY / 2), CrosshairSize * 5, ImColor(33, 230, 193), 100);
};

void AimBotModule(int index)
{
	ClassEntityList* EntityList = Game::Get()->GameManager->Client->World->EntityList;
	ClassAgentCamera* AgentCamera = Game::Get()->GameManager->Client->World->CameraList->CameraArray->Camera->AgentCamera;
	float pResolutionX = Game::Get()->ResolutionX;
	float pResolutionY = Game::Get()->ResolutionY;

	D3DXVECTOR3 entityHead, camPos, aim_delta, aim_pos;
	GetHead(EntityList, index, entityHead);

	aim_pos = D3DXVECTOR3(entityHead.x, entityHead.y + 0.095f, entityHead.z);

	camPos = EntityList->EntityArray[index]->AimingPosition;

	aim_delta = D3DXVECTOR3(aim_pos.x - camPos.x, aim_pos.y - camPos.y, aim_pos.z - camPos.z);

	float len = sqrtf(aim_delta.x * aim_delta.x + aim_delta.y * aim_delta.y + aim_delta.z * aim_delta.z);

	if (len == 0.0f) {
		return;
	}

	float new_pitch = asinf(aim_delta.y / len);
	float cos_pitch = cosf(new_pitch);

	if (cos_pitch == 0.0f) {
		return;
	}

	float new_yaw = asin(aim_delta.x / (cos_pitch * len));

	float yaw = EntityList->EntityArray[0]->Crosshair->Yaw;
	float pitch = EntityList->EntityArray[0]->Crosshair->Pitch;

	if (yaw > M_3_PI_2) {
		new_yaw = M_2_PI - new_yaw;
	}
	else if (yaw > M_PI_2) {
		new_yaw = M_PI + new_yaw;
	}

	if (new_yaw > 0.0 && new_pitch < M_2_PI && new_pitch > -M_PI_2 && new_pitch) {
		// Write out the view angles.
		yaw = new_yaw;
		pitch = new_pitch;

		// Write out the view angles into the crosshair as well.
		AgentCamera->Pitch = new_pitch;
		AgentCamera->Yaw = new_yaw;
	}
}

void AimAt(int index)
{
	// angle are in redians

	ClassEntityList* EntityList = Game::Get()->GameManager->Client->World->EntityList;
	ClassAgentCamera* AgentCamera = Game::Get()->GameManager->Client->World->CameraList->CameraArray->Camera->AgentCamera;

	D3DXVECTOR3 aim, to, dis;

	aim = EntityList->EntityArray[0]->AimingPosition;
	
	GetHead(EntityList, index, to);

	dis = D3DXVECTOR3(aim.x - to.x, aim.y - to.y, aim.z - to.z);

	float magnitude = Magnitude(dis);

	float pitch = asinf(dis.y / magnitude);
	float cos_pitch = cosf(pitch);
	float yaw = asin(dis.x / (cos_pitch * magnitude));
	//float pitch = asin(dis.z / magnitude) * (PI / 180);
	//float yaw = -atan2(dis.y, dis.x) / (180 * PI);

	std::cout << "pitch " << pitch << std::endl;
	std::cout << "yaw " << yaw << std::endl;

	EntityList->EntityArray[0]->Crosshair->Pitch = pitch;
	EntityList->EntityArray[0]->Crosshair->Yaw = yaw;
	AgentCamera->Pitch = pitch;
	AgentCamera->Yaw = yaw;

	/*if (pitch >= 1.222f && pitch <= -1.396f && yaw >= 0 && yaw <= 6.280f)
	{
		EntityList->EntityArray[0]->Crosshair->Pitch = pitch;
		EntityList->EntityArray[0]->Crosshair->Yaw = yaw;
		AgentCamera->Pitch = pitch;
		AgentCamera->Yaw = yaw;
		
	}*/
}

void Hack::Aimbot()
{
	int NumberOfEntities = Game::Get()->GameManager->Client->World->NumberOfEntities;
	ClassEntityList* EntityList = Game::Get()->GameManager->Client->World->EntityList;
	float pResolutionX = Game::Get()->ResolutionX;
	float pResolutionY = Game::Get()->ResolutionY;
	static float currentDis;
	static D3DXVECTOR2 headCord, playerCord, leftHandCord, rightHandCord, leftLegCord, rightLegCord;
	static D3DXVECTOR3 headPosition, playerPosition, leftHandPosition, rightHandPosition, leftLegPosition, rightLegPosition;

	for (int i = 0; i < NumberOfEntities; i++)
	{
		if (EntityList->EntityArray[i]->IsDead) continue;
		if (EntityList->EntityArray[i]->PlayerType < 0) continue;
		if (EntityList->EntityArray[i]->IsFriendly) continue;
		if (EntityList->EntityArray[i]->IsGadget) continue;
		if (i == 0) continue;
		if (strcmp(" ", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("HUB", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Pigeon Fx", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Pigeon", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Raven Fx", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Raven", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Dog", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Rat", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Flatiron", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Vanity Vendor", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Mods Vendor", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Weapons Vendor", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Gear Vendor", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Police Pistol", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Police Shotgun", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Turtle Bay", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Gramercy", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Hells Kitchen", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Clinton", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Tenderloin", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Garment", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Murray Hill", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Stuyvesant", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Kips Bay", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Times Square", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Jessica Kandel", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Roy Benitez", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Hudson Yards", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Brooklyn", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Midtown East", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("BOO", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Turrent", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Tesla Trap", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Seeker Mine", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Seagull", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("Civilian", EntityList->EntityArray[i]->Name) == 0) continue;
		if (strcmp("JTF", EntityList->EntityArray[i]->Name) == 0) continue;
		if (!WorldToScreen(EntityList->EntityArray[i]->Position, playerCord, Game::Get()->ViewMatrix, pResolutionX, pResolutionY)) continue;

		currentDis = GetDistance(EntityList->EntityArray[0]->Position, EntityList->EntityArray[i]->Position);

		if (currentDis < 50)
		{
			AimBotModule(i);
			std::cout << EntityList->EntityArray[i]->Name << std::endl;
		}
	}
};

void Hack::TeleportTo()
{
	ClassEntityList* EntityList = Game::Get()->GameManager->Client->World->EntityList;
	EntityList->EntityArray[0]->PositionData->PlayerCoordinate->LocalPlayerCoordinate->PositionX = EntityList->EntityArray[0]->AimingPosition.x;
	EntityList->EntityArray[0]->PositionData->PlayerCoordinate->LocalPlayerCoordinate->PositionY = EntityList->EntityArray[0]->AimingPosition.y;
	EntityList->EntityArray[0]->PositionData->PlayerCoordinate->LocalPlayerCoordinate->PositionZ = EntityList->EntityArray[0]->AimingPosition.z;
};

void Hack::TeleportToWayPoint()
{
	ClassEntityList* EntityList = Game::Get()->GameManager->Client->World->EntityList;
	EntityList->EntityArray[0]->PositionData->PlayerCoordinate->LocalPlayerCoordinate->PositionX = ClassGameUI::Get()->UI->Map->Waypoint->WaypointPosition->X;
	EntityList->EntityArray[0]->PositionData->PlayerCoordinate->LocalPlayerCoordinate->PositionY = ClassGameUI::Get()->UI->Map->Waypoint->WaypointPosition->Y;
	EntityList->EntityArray[0]->PositionData->PlayerCoordinate->LocalPlayerCoordinate->PositionZ = ClassGameUI::Get()->UI->Map->Waypoint->WaypointPosition->Z + 1;
};

void Hack::NoRecoil() 
{
	ClassEntity* Entity = Game::Get()->GameManager->Client->World->EntityList->EntityArray[0];
	uint32_t indexRecoilBaseFinal, indexRecoilIncreasePerBulletFinal, indexRecoilMaxFinal, indexRecoilMinFinal;
	CIndexInfo::Get().GetAttribute(CIndexModule::RecoilBaseFinal, indexRecoilBaseFinal);
	CIndexInfo::Get().GetAttribute(CIndexModule::RecoilIncreasePerBulletFinal, indexRecoilIncreasePerBulletFinal);
	CIndexInfo::Get().GetAttribute(CIndexModule::RecoilMaxFinal, indexRecoilMaxFinal);
	CIndexInfo::Get().GetAttribute(CIndexModule::RecoilMinFinal, indexRecoilMinFinal);
	Entity->IndexInfo->GetInfoByIndex(indexRecoilBaseFinal)->value = 0.f;
	Entity->IndexInfo->GetInfoByIndex(indexRecoilIncreasePerBulletFinal)->value = 0.f;
	Entity->IndexInfo->GetInfoByIndex(indexRecoilMaxFinal)->value = 0.f;
	Entity->IndexInfo->GetInfoByIndex(indexRecoilMinFinal)->value = 0.f;
}

void Hack::NoSpread()
{
	ClassEntity* Entity = Game::Get()->GameManager->Client->World->EntityList->EntityArray[0];
	uint32_t indexAimSpreadMaxFinal, AimSpreadMinFinal;
	CIndexInfo::Get().GetAttribute(CIndexModule::AimSpreadMaxFinal, indexAimSpreadMaxFinal);
	CIndexInfo::Get().GetAttribute(CIndexModule::AimSpreadMinFinal, AimSpreadMinFinal);
	Entity->IndexInfo->GetInfoByIndex(indexAimSpreadMaxFinal)->value = 0.f;
	Entity->IndexInfo->GetInfoByIndex(AimSpreadMinFinal)->value = 0.f;
};

void Hack::NoReload()
{
	ClassEntity* Entity = Game::Get()->GameManager->Client->World->EntityList->EntityArray[0];
	uint32_t indexInitialShellReloadTimeMSFinal, ReloadTimeMSFinal;
	CIndexInfo::Get().GetAttribute(CIndexModule::InitialShellReloadTimeMSFinal, indexInitialShellReloadTimeMSFinal);
	CIndexInfo::Get().GetAttribute(CIndexModule::ReloadTimeMSFinal, ReloadTimeMSFinal);
	Entity->IndexInfo->GetInfoByIndex(indexInitialShellReloadTimeMSFinal)->value = 1.f;
	Entity->IndexInfo->GetInfoByIndex(ReloadTimeMSFinal)->value = 1.f;
};

void Hack::ChangeClipSize()
{
	ClassEntity* Entity = Game::Get()->GameManager->Client->World->EntityList->EntityArray[0];
	uint32_t ClipSizeFinal;
	CIndexInfo::Get().GetAttribute(CIndexModule::ClipSizeFinal, ClipSizeFinal);
	Entity->IndexInfo->GetInfoByIndex(ClipSizeFinal)->value = 500;
};

void Hack::MovementSpeed()
{
	ClassEntity* Entity = Game::Get()->GameManager->Client->World->EntityList->EntityArray[0];
	uint32_t indexMovementSpeed;
	CIndexInfo::Get().GetAttribute(CIndexModule::MovementSpeedModFinal, indexMovementSpeed);
	Entity->IndexInfo->GetInfoByIndex(indexMovementSpeed)->value = 100.f;
};

void Hack::SetRPM(int rpm) 
{
	ClassEntity* Entity = Game::Get()->GameManager->Client->World->EntityList->EntityArray[0];
	uint32_t index = 0;
	CIndexInfo::Get().GetAttribute(CIndexModule::RPMFinal, index);
	Entity->IndexInfo->GetInfoByIndex(index)->value = (float)rpm;
};

float Hack::GetRPM() 
{
	ClassEntity* Entity = Game::Get()->GameManager->Client->World->EntityList->EntityArray[0];
	uint32_t index = 0;
	CIndexInfo::Get().GetAttribute(CIndexModule::RPMFinal, index);

	return Entity->IndexInfo->GetInfoByIndex(index)->value;
};