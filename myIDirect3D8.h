// $Rev: 9142 $ $Date: 2015-12-10 14:01:17 +0000 (Thu, 10 Dec 2015) $
// Copyright (c) 2012 Adam Billyard.
// All Rights Reserved.

#pragma once

// dx8 version is different but has same name!
typedef struct _D3DPRESENT_PARAMETERS8_
{
	UINT                BackBufferWidth;
	UINT                BackBufferHeight;
	D3DFORMAT           BackBufferFormat;
	UINT                BackBufferCount;

	D3DMULTISAMPLE_TYPE MultiSampleType;

	D3DSWAPEFFECT       SwapEffect;
	HWND                hDeviceWindow;
	BOOL                Windowed;
	BOOL                EnableAutoDepthStencil;
	D3DFORMAT           AutoDepthStencilFormat;
	DWORD               Flags;

	/* Following elements must be zero for Windowed mode */
	UINT                FullScreen_RefreshRateInHz;
	UINT                FullScreen_PresentationInterval;

} D3DPRESENT_PARAMETERS8;


interface DECLSPEC_UUID("81BDCBCA-64D4-426d-AE8D-AD0147F4275C") IDirect3D9;
interface DECLSPEC_UUID("D0223B96-BF7A-43fd-92BD-A43B0D82B9EB") IDirect3DDevice9;

class DECLSPEC_UUID("1DD9E8DA-1C77-4d40-B0CF-98FEFDFF9512") myIDirect3D8
{
public:

	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj);
	STDMETHOD_(ULONG, AddRef)(THIS);
	STDMETHOD_(ULONG, Release)(THIS);

	// The original DX9 function definitions
	STDMETHOD(RegisterSoftwareDevice)(THIS_ void* pInitializeFunction);
	STDMETHOD_(UINT, GetAdapterCount)(THIS);
	STDMETHOD(GetAdapterIdentifier)(THIS_ UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER8* pIdentifier);
	STDMETHOD_(UINT, GetAdapterModeCount)(THIS_ UINT Adapter);
	STDMETHOD(EnumAdapterModes)(THIS_ UINT Adapter, UINT Mode, D3DDISPLAYMODE* pMode);
	STDMETHOD(GetAdapterDisplayMode)(THIS_ UINT Adapter, D3DDISPLAYMODE* pMode);
	STDMETHOD(CheckDeviceType)(THIS_ UINT iAdapter, D3DDEVTYPE DevType, D3DFORMAT DisplayFormat, D3DFORMAT BackBufferFormat, BOOL bWindowed);
	STDMETHOD(CheckDeviceFormat)(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat);
	STDMETHOD(CheckDeviceMultiSampleType)(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType);
	STDMETHOD(CheckDepthStencilMatch)(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat);
	STDMETHOD(GetDeviceCaps)(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS8* pCaps);
	STDMETHOD_(HMONITOR, GetAdapterMonitor)(THIS_ UINT Adapter);
	STDMETHOD(CreateDevice)(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS8* pPresentationParameters, IDirect3DDevice8** ppReturnedDeviceInterface);
	// The original DX9 function definitions

	myIDirect3D8(IDirect3D9 *pOriginal);
	virtual ~myIDirect3D8(void);

	//private:
	IDirect3D9 *m_pmyDirect3D9;

};
