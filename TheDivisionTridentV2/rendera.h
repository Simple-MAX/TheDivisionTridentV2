#pragma once
#include "includes.h"

class Rendera
{
public:
	Rendera(const Rendera&) = delete;

	static Rendera& Get() { return s_Instance; }

	void InitImGui(HWND window, ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	{
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
		ImGui_ImplWin32_Init(window);
		ImGui_ImplDX11_Init(pDevice, pContext);
	}

	void Render(ID3D11DeviceContext* pContext, ID3D11RenderTargetView* mainRenderTargetView);
private:
	Rendera() {}
	static Rendera s_Instance;
};

