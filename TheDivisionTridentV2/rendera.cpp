#include "includes.h"

Rendera Rendera::s_Instance;

static bool pShowMenu = false;
static bool pShowConsole = false;
static bool pShowESPPVP = false;
static bool pShowESPPVE = true;
static bool pShowCrosshair = false;
static bool teleportToWayPoint = false;
static bool pRender = true;
static bool pActivate = false;
static bool pRecoil = false;
static float RPMValue = 0;
static bool pNoSpread = false;
static bool pMovementSpeed = false;
static bool pNoReload = false;

void Style()
{
	ImGuiStyle* style = &ImGui::GetStyle();
	style->WindowPadding = ImVec2(15, 15);
	style->WindowRounding = 2.5f;
	style->FramePadding = ImVec2(5, 5);
	style->FrameRounding = 4.0f;
	style->ItemSpacing = ImVec2(12, 8);
	style->ItemInnerSpacing = ImVec2(8, 6);
	style->IndentSpacing = 25.0f;
	style->ScrollbarSize = 15.0f;
	style->ScrollbarRounding = 9.0f;
	style->GrabMinSize = 5.0f;
	style->GrabRounding = 3.0f;

	style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
};

void Rendera::Render(ID3D11DeviceContext* pContext, ID3D11RenderTargetView* mainRenderTargetView)
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	Style();
	ImGui::NewFrame();

	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		pShowMenu = !pShowMenu;
	}

	if (pShowMenu)
	{
		ImGui::Begin("TheDivisionTridentV2");
		ImGui::Columns(3);

		ImGui::BeginGroup();
		if (ImGui::Button("pShowConsole", ImVec2(150, 25))) { pShowConsole = !pShowConsole; }
		if (ImGui::Button("Close", ImVec2(150, 25))) { pRender = !pRender; }
		if (ImGui::Button("TeleportToWayPoint", ImVec2(150, 25))) { teleportToWayPoint = true; }
		ImGui::EndGroup();
		ImGui::NextColumn();

		ImGui::BeginGroup();
		ImGui::Text("Visual");
		ImGui::Checkbox("ESP-PVE", &pShowESPPVE);
		ImGui::Checkbox("ESP-PVP", &pShowESPPVP);
		ImGui::Checkbox("Crosshair", &pShowCrosshair);
		ImGui::EndGroup();
		ImGui::NextColumn();

		ImGui::BeginGroup();
		ImGui::Text("Weapon");
		ImGui::Checkbox("No Recoil", &pRecoil);
		ImGui::Checkbox("No Spread", &pNoSpread);
		ImGui::Checkbox("ChangeClipSize", &pNoReload);
		ImGui::Checkbox("Activate RPM", &pActivate);
		ImGui::SliderFloat("RPM", &RPMValue, Hack::Get().GetRPM(), 5000.f);
		ImGui::EndGroup();

		ImGui::Columns(2);
		ImGui::Checkbox("Player speed", &pMovementSpeed);
		ImGui::Columns(1);
		ImGui::TextColored(ImColor(255, 48, 79, 255), "[?]When closing disable all features first then hit close and then end key to exit the tool.");
		ImGui::End();
	}
	
	if (pRender)
	{
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(ImVec2((int)Game::Get()->ResolutionX, (int)Game::Get()->ResolutionY));
		ImGui::Begin("Overlay", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground);
		auto pDrawList = ImGui::GetBackgroundDrawList();

		if (pShowESPPVP)
		{
			Hack::Get().EPSPVP(pDrawList);
		}
		if (pShowESPPVE)
		{
			Hack::Get().EPSPVE(pDrawList);
		}
		if (pShowCrosshair)
		{
			Hack::Get().Crosshair(pDrawList);
		}
		if (teleportToWayPoint)
		{
			Hack::Get().TeleportToWayPoint();
			teleportToWayPoint = false;
		}
		if (pRecoil)
		{
			Hack::Get().NoRecoil();
		}
		if (pActivate)
		{
			Hack::Get().SetRPM(RPMValue);
		}
		if (pNoSpread)
		{
			Hack::Get().NoSpread();
		}
		if (pNoReload)
		{
			Hack::Get().ChangeClipSize();
		}
		if (pMovementSpeed)
		{
			Hack::Get().MovementSpeed();
		}

		pDrawList->AddText(ImVec2(10, 10), ImColor(255, 255, 255), "TheDivisionTridentV2");
		ImGui::End();
	}
	
	ImGui::Render();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
};