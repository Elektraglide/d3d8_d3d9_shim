// $Rev: 9179 $ $Date: 2016-01-20 19:05:26 +0000 (Wed, 20 Jan 2016) $
// Copyright (c) 2012 Adam Billyard.
// All Rights Reserved.

#include "stdafx.h"

// and for non-opaque objects, we need the declarations some of which clash with d3d8 so we need to duplicate them.


myIDirect3D8::myIDirect3D8(IDirect3D9 *pOriginal)
{

	m_pmyDirect3D9 = pOriginal;
}

myIDirect3D8::~myIDirect3D8(void)
{


}

STDMETHODIMP
myIDirect3D8::QueryInterface(REFIID riid, void** ppvObj)
{


	*ppvObj = NULL;

	if (riid == IID_IDirect3D8 || riid == IID_IUnknown)
	{
		AddRef();
		*ppvObj = this;
		return S_OK;
	}
	else
	{
		return E_NOINTERFACE;
	}
}

STDMETHODIMP_(ULONG)
myIDirect3D8::AddRef(void)
{
	return m_pmyDirect3D9->AddRef();
}

STDMETHODIMP_(ULONG)
myIDirect3D8::Release(void)
{


	ULONG count = m_pmyDirect3D9->Release();
	if (count == 0)
	{
		delete(this);
	}

	return(count);
}

STDMETHODIMP
myIDirect3D8::RegisterSoftwareDevice(void* pInitializeFunction)
{


	return(m_pmyDirect3D9->RegisterSoftwareDevice(pInitializeFunction));
}

STDMETHODIMP_(UINT)
myIDirect3D8::GetAdapterCount(void)
{

	return(m_pmyDirect3D9->GetAdapterCount());
}

#define PRODUCT		1234
#define VERSION		1234
#define SUBVERSION	1234
#define BUILD		1234
STDMETHODIMP
myIDirect3D8::GetAdapterIdentifier(UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER8* pIdentifier)
{

	D3DADAPTER_IDENTIFIER9 Identitier;
	HRESULT hr = m_pmyDirect3D9->GetAdapterIdentifier(Adapter, Flags, &Identitier);

	strcpy(pIdentifier->Driver, Identitier.Driver);
	strcpy(pIdentifier->Description, Identitier.Description);
	pIdentifier->DriverVersion = Identitier.DriverVersion;
	pIdentifier->VendorId = Identitier.VendorId;
	pIdentifier->DeviceId = Identitier.DeviceId;
	pIdentifier->SubSysId = Identitier.SubSysId;
	pIdentifier->Revision = Identitier.Revision;
	pIdentifier->DeviceIdentifier = Identitier.DeviceIdentifier;
	pIdentifier->WHQLLevel = Identitier.WHQLLevel;

	return D3D_OK;
}

STDMETHODIMP_(UINT)
myIDirect3D8::GetAdapterModeCount(UINT Adapter)
{

	UINT n = m_pmyDirect3D9->GetAdapterModeCount(Adapter, D3DFMT_X8R8G8B8);
	return n;
}

STDMETHODIMP
myIDirect3D8::EnumAdapterModes(UINT Adapter, UINT Mode, D3DDISPLAYMODE* pMode)
{

	pMode->RefreshRate = 60;

	HRESULT hr = m_pmyDirect3D9->EnumAdapterModes(Adapter, D3DFMT_X8R8G8B8, Mode, pMode);

	// d3d9 g_config_info may not be setup
	if (!pMode->Width || !pMode->Height)
	{
		pMode->Width = 1280;
		pMode->Height = 720;
	}

	return hr;
}

STDMETHODIMP
myIDirect3D8::GetAdapterDisplayMode(UINT Adapter, D3DDISPLAYMODE* pMode)
{


	return(m_pmyDirect3D9->GetAdapterDisplayMode(Adapter, pMode));
}

STDMETHODIMP
myIDirect3D8::CheckDeviceType(UINT iAdapter, D3DDEVTYPE DevType, D3DFORMAT DisplayFormat, D3DFORMAT BackBufferFormat, BOOL bWindowed)
{
	// this is used to check a device can render offscreen, so d3d9 is wrongly rejecting anything not bWindowed = true
	bWindowed = true;

	return(m_pmyDirect3D9->CheckDeviceType(iAdapter, DevType, DisplayFormat, BackBufferFormat, bWindowed));
}

STDMETHODIMP
myIDirect3D8::CheckDeviceFormat(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat)
{

	HRESULT devicehr = m_pmyDirect3D9->CheckDeviceFormat(Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat);
	return devicehr;
}

STDMETHODIMP
myIDirect3D8::CheckDeviceMultiSampleType(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType)
{
	return(m_pmyDirect3D9->CheckDeviceMultiSampleType(Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType, NULL));
}

STDMETHODIMP
myIDirect3D8::CheckDepthStencilMatch(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat)
{

	HRESULT hr = m_pmyDirect3D9->CheckDepthStencilMatch(Adapter, DeviceType, AdapterFormat, RenderTargetFormat, DepthStencilFormat);

	return hr;
}

STDMETHODIMP
myIDirect3D8::GetDeviceCaps(UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS8* pCaps)
{

	D3DCAPS9 caps;
	HRESULT hr = m_pmyDirect3D9->GetDeviceCaps(Adapter, DeviceType, &caps);
	memcpy(pCaps, &caps, sizeof(D3DCAPS8));

	// deprecated stuff
	pCaps->Caps2 |= D3DCAPS2_CANRENDERWINDOWED;

	return hr;
}

STDMETHODIMP_(HMONITOR)
myIDirect3D8::GetAdapterMonitor(UINT Adapter)
{

	return(m_pmyDirect3D9->GetAdapterMonitor(Adapter));
}

STDMETHODIMP
myIDirect3D8::CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS8* pPresentationParameters, IDirect3DDevice8** ppReturnedDeviceInterface)
{

	// we intercept this call 
	*ppReturnedDeviceInterface = NULL;
	HRESULT hres = D3D_OK;

	D3DPRESENT_PARAMETERS d3dpp;

	// dx8 not identical!
	d3dpp.Windowed = pPresentationParameters->Windowed;
	d3dpp.SwapEffect = pPresentationParameters->SwapEffect;
	d3dpp.BackBufferFormat = pPresentationParameters->BackBufferFormat;
	d3dpp.BackBufferWidth = pPresentationParameters->BackBufferWidth;
	d3dpp.BackBufferHeight = pPresentationParameters->BackBufferHeight;
	d3dpp.BackBufferCount = pPresentationParameters->BackBufferCount;
	d3dpp.hDeviceWindow = pPresentationParameters->hDeviceWindow;
	d3dpp.EnableAutoDepthStencil = pPresentationParameters->EnableAutoDepthStencil;
	d3dpp.AutoDepthStencilFormat = pPresentationParameters->AutoDepthStencilFormat;
	d3dpp.MultiSampleType = pPresentationParameters->MultiSampleType;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.Flags = pPresentationParameters->Flags;
	d3dpp.FullScreen_RefreshRateInHz = pPresentationParameters->FullScreen_RefreshRateInHz;
	d3dpp.PresentationInterval = pPresentationParameters->FullScreen_PresentationInterval;

	// framebuffer devices can't be MSAA
	if (d3dpp.Windowed)
	{
		//	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	}

	// project64 Jabbo driver passes in Adapter=1, force it to be 0
	Adapter = 0;

	IDirect3DDevice9 *d3d9dev;
	m_pmyDirect3D9->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, &d3dpp, &d3d9dev);

	// FIXME: why do some calls increment Refcount and some dont?

	// FIXME:  not sure I understand the difference between DeviceWindow and FocusWindow..
	if (pPresentationParameters->hDeviceWindow == NULL)
	{
		pPresentationParameters->hDeviceWindow = hFocusWindow;
	}

	// Create our own Device object and store it in global pointer
	// note: the object will delete itself once Ref count is zero (similar to COM objects)
	myIDirect3DDevice8 *pmyIDirect3DDevice8 = new myIDirect3DDevice8(this, &d3dpp, d3d9dev);

	// store our pointer (the fake one) for returning it to the calling progam
	*ppReturnedDeviceInterface = (IDirect3DDevice8 *)pmyIDirect3DDevice8;

	// always succeed
	return D3D_OK;
}
