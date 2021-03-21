#include "includes.h"
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static bool init = false;
static bool pRender = true;

FILE* fp;

HMODULE hModule;
Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

DWORD __stdcall EjectThread(LPVOID lpParameter) {
	Sleep(100);
	DisableThreadLibraryCalls(hModule);
	FreeLibraryAndExitThread(hModule, 0);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)& pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)& pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			Rendera::Get().InitImGui(window, pDevice, pContext);
			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}
	
	if (GetAsyncKeyState(VK_RBUTTON))
	{
		Hack::Get().Aimbot();
	}
	
	/*if (GetAsyncKeyState(VK_F3) & 1)
	{
		
		* 		IndexModule* indexModule = IndexModule::Get();
		if (!indexModule)
		{
			std::cout << "indexModule is nullptr" << std::endl;
		}
		// returns the index of the module
		ClassEntity* Entity = Game::Get()->GameManager->Client->World->EntityList->EntityArray[0]; // get entity
		std::cout << index << std::endl;
		float AttributeArray = Entity->AttributeComponent->AttributeDictionary->AttributeArray->value;
		//std::cout << AttributeArray->value << std::endl;
		ClassEntity* Entity = Game::Get()->GameManager->Client->World->EntityList->EntityArray[0];

		
		std::cout << Entity->IndexInfo->GetInfoByIndex(index)->value << std::endl;
	}*/

	if (GetAsyncKeyState(VK_F2) & 1) 
	{
		Hack::Get().TeleportTo();
	}

	if (GetAsyncKeyState(VK_END) & 1)
	{
		pRender = false;
		ImGui_ImplWin32_Shutdown();
		ImGui_ImplDX11_Shutdown();
		ImGui::DestroyContext();

		fclose(fp);
		FreeConsole();

		kiero::unbind(8);
		pDevice->Release();
		pContext->Release();

		SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)oWndProc);
		CreateThread(nullptr, 0, EjectThread, nullptr, 0, nullptr);
	}

	if (pRender)
	{
		Rendera::Get().Render(pContext, mainRenderTargetView);
	}
	
	return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)& oPresent, hkPresent);
			AllocConsole();
			freopen_s(&fp, "CONOUT$", "w", stdout);
			std::cout << "Debugging" << std::endl;
			init_hook = true;
		}
	} while (!init_hook);
	return TRUE;
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		hModule = hMod;
		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}