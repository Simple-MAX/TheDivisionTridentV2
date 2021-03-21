#pragma once
#include <iostream>
#include <vector>
#include <deque>
#include <Windows.h>
#include <string>
#include <math.h>
#include <d3d11.h>
#include <D3DX10math.h>
#include <dxgi.h>
#include "kiero/kiero.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "rendera.h"
#include "Game.h"
#include "Hack.h"
#include "IndexModule.h"
#include "vector.h"
#include "types.h"

/* The Division SDK */
//#include "GameManager.h"

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;