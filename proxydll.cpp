// proxydll.cpp
#include "stdafx.h"
#include "proxydll.h"

// global variables
#pragma data_seg (".d3d8_shared")
HINSTANCE           gl_hOriginalDll;
HINSTANCE           gl_hThisInstance;
#pragma data_seg ()

BOOL APIENTRY DllMain(HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	// to avoid compiler lvl4 warnings 
	LPVOID lpDummy = lpReserved;
	lpDummy = NULL;

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: InitInstance(hModule); break;
	case DLL_PROCESS_DETACH: ExitInstance(); break;

	case DLL_THREAD_ATTACH:  break;
	case DLL_THREAD_DETACH:  break;
	}
	return TRUE;
}

// Exported function 
IDirect3D8* WINAPI Direct3DCreate8(UINT SDKVersion)
{
	// try to load Polystream d3d9.dll from current directory
	if (!gl_hOriginalDll) gl_hOriginalDll = ::LoadLibrary(L".\\d3d9.dll");

	// get d3d9 entrypoint and cast to d3d8 entrypoint
	typedef IDirect3D9 *(WINAPI* D3D8_Type)(UINT SDKVersion);
	D3D8_Type D3DCreate9_fn = (D3D8_Type)GetProcAddress(gl_hOriginalDll, "Direct3DCreate9");
	if (!D3DCreate9_fn)
	{
		::ExitProcess(0);
	}

	// Request pointer from Polystream d3d9  - NB using DirectX 9 D3D_SDK_VERSION
#define D3D9_SDK_VERSION   32
	IDirect3D9 *pIDirect3D9_orig = D3DCreate9_fn(D3D9_SDK_VERSION);

	// wrap our d3d9 object in our d3d8 wrapper
	myIDirect3D8* pmyIDirect3D8 = new myIDirect3D8(pIDirect3D9_orig);

	// Return pointer to hooking Object instead of "real one"
	return (IDirect3D8*)pmyIDirect3D8;
}

void InitInstance(HANDLE hModule)
{

	// Initialisation
	gl_hOriginalDll = NULL;
	gl_hThisInstance = NULL;

	// Storing Instance handle into global var
	gl_hThisInstance = (HINSTANCE)hModule;
}

void ExitInstance()
{

	// Release the system's d3d8.dll
	if (gl_hOriginalDll)
	{
		::FreeLibrary(gl_hOriginalDll);
		gl_hOriginalDll = NULL;
	}
}

