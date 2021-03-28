// $Rev: 9179 $ $Date: 2016-01-20 19:05:26 +0000 (Wed, 20 Jan 2016) $
// Copyright (c) 2012 Adam Billyard.
// All Rights Reserved.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <fcntl.h>

#include "StdAfx.h"

class DECLSPEC_UUID("B96EEBCA-B326-4ea5-882F-2FF5BAE021DD") myIDirect3DSurface8
{
public:
	/*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj)
	{
		if (riid == IID_IDirect3DSurface8 || riid == IID_IUnknown)
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
	STDMETHOD_(ULONG, AddRef)(THIS) {
		return m_IDirect3DSurface9->AddRef();
	}
	STDMETHOD_(ULONG, Release)(THIS) {
		ULONG count = m_IDirect3DSurface9->Release();
		if (count == 0)
		{
			delete(this);
		}
		return count;
	}

	/*** IDirect3DSurface8 methods ***/
	STDMETHOD(GetDevice)(THIS_ IDirect3DDevice8** ppDevice)
	{
		m_owner->AddRef();
		*ppDevice = (IDirect3DDevice8*)m_owner;
		return D3D_OK;
	}
	STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags) { return m_IDirect3DSurface9->SetPrivateData(refguid, pData, SizeOfData, Flags); }
	STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid, void* pData, DWORD* pSizeOfData) { return m_IDirect3DSurface9->GetPrivateData(refguid, pData, pSizeOfData); }
	STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) { return m_IDirect3DSurface9->FreePrivateData(refguid); }
	STDMETHOD(GetContainer)(THIS_ REFIID riid, void** ppContainer)
	{
		*ppContainer = m_container;
		return D3D_OK;
	}
	STDMETHOD(GetDesc)(THIS_ D3DSURFACE_DESC *pDesc) { return m_IDirect3DSurface9->GetDesc(pDesc); }
	STDMETHOD(LockRect)(THIS_ D3DLOCKED_RECT* pLockedRect, CONST RECT* pRect, DWORD Flags) { return m_IDirect3DSurface9->LockRect(pLockedRect, pRect, Flags); }
	STDMETHOD(UnlockRect)(THIS) { return m_IDirect3DSurface9->UnlockRect(); }

	myIDirect3DSurface8(myIDirect3DDevice8 *owner, void *container, IDirect3DSurface9* pOriginal) : m_owner(owner), m_container(container), m_IDirect3DSurface9(pOriginal) {}
	virtual ~myIDirect3DSurface8(void) {}

	myIDirect3DDevice8 *m_owner;
	void *m_container;
	IDirect3DSurface9 *m_IDirect3DSurface9;
};
class DECLSPEC_UUID("B96EEBCA-B326-4ea5-882F-2FF5BAE021DD") myIDirect3DTexture8
{
public:
	/*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj)
	{
		if (riid == IID_IDirect3DTexture8 || riid == IID_IUnknown)
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
	STDMETHOD_(ULONG, AddRef)(THIS) {
		return m_IDirect3DTexture9->AddRef();
	}
	STDMETHOD_(ULONG, Release)(THIS) {
		return m_IDirect3DTexture9->Release();
	}

	/*** IDirect3DBaseTexture8 methods ***/
	STDMETHOD(GetDevice)(THIS_ IDirect3DDevice8** ppDevice)
	{
		m_owner->AddRef();
		*ppDevice = (IDirect3DDevice8*)m_owner;
		return D3D_OK;
	}
	STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags) { return m_IDirect3DTexture9->SetPrivateData(refguid, pData, SizeOfData, Flags); }
	STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid, void* pData, DWORD* pSizeOfData) { return m_IDirect3DTexture9->GetPrivateData(refguid, pData, pSizeOfData); }
	STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) { return m_IDirect3DTexture9->FreePrivateData(refguid); }
	STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew) { return m_IDirect3DTexture9->SetPriority(PriorityNew); }
	STDMETHOD_(DWORD, GetPriority)(THIS) { return m_IDirect3DTexture9->GetPriority(); }
	STDMETHOD_(void, PreLoad)(THIS) { return m_IDirect3DTexture9->PreLoad(); }
	STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS) { return m_IDirect3DTexture9->GetType(); }
	STDMETHOD_(DWORD, SetLOD)(THIS_ DWORD LODNew) { return m_IDirect3DTexture9->SetLOD(LODNew); }
	STDMETHOD_(DWORD, GetLOD)(THIS) { return m_IDirect3DTexture9->GetLOD(); }
	STDMETHOD_(DWORD, GetLevelCount)(THIS) { return m_IDirect3DTexture9->GetLevelCount(); }
	STDMETHOD(GetLevelDesc)(THIS_ UINT Level, D3DSURFACE_DESC *pDesc) { return m_IDirect3DTexture9->GetLevelDesc(Level, pDesc); }
	STDMETHOD(GetSurfaceLevel)(THIS_ UINT Level, IDirect3DSurface8** ppSurfaceLevel) {
		IDirect3DSurface9 *surf;
		HRESULT hr = m_IDirect3DTexture9->GetSurfaceLevel(Level, &surf);
		*ppSurfaceLevel = (IDirect3DSurface8*)new myIDirect3DSurface8(m_owner, (void *)this, surf);
		return hr;
	}
	STDMETHOD(LockRect)(THIS_ UINT Level, D3DLOCKED_RECT* pLockedRect, CONST RECT* pRect, DWORD Flags) { return m_IDirect3DTexture9->LockRect(Level, pLockedRect, pRect, Flags); }
	STDMETHOD(UnlockRect)(THIS_ UINT Level) { return m_IDirect3DTexture9->UnlockRect(Level); }
	STDMETHOD(AddDirtyRect)(THIS_ CONST RECT* pDirtyRect) { return m_IDirect3DTexture9->AddDirtyRect(pDirtyRect); }

	myIDirect3DTexture8(myIDirect3DDevice8 *owner, IDirect3DTexture9* pOriginal) : m_owner(owner), m_IDirect3DTexture9(pOriginal) {}
	virtual ~myIDirect3DTexture8(void) {}

	myIDirect3DDevice8 *m_owner;
	IDirect3DTexture9 *m_IDirect3DTexture9;
};
class DECLSPEC_UUID("3EE5B968-2ACA-4c34-8BB5-7E0C3D19B750") myIDirect3DCubeTexture8
{
public:
	/*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj)
	{
		if (riid == IID_IDirect3DCubeTexture8 || riid == IID_IUnknown)
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
	STDMETHOD_(ULONG, AddRef)(THIS) {
		return m_IDirect3DCubeTexture9->AddRef();
	}
	STDMETHOD_(ULONG, Release)(THIS) {
		return m_IDirect3DCubeTexture9->Release();
	}

	/*** IDirect3DBaseTexture8 methods ***/
	STDMETHOD(GetDevice)(THIS_ IDirect3DDevice8** ppDevice)
	{
		m_owner->AddRef();
		*ppDevice = (IDirect3DDevice8*)m_owner;
		return D3D_OK;
	}
	STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags) { return m_IDirect3DCubeTexture9->SetPrivateData(refguid, pData, SizeOfData, Flags); }
	STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid, void* pData, DWORD* pSizeOfData) { return m_IDirect3DCubeTexture9->GetPrivateData(refguid, pData, pSizeOfData); }
	STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) { return m_IDirect3DCubeTexture9->FreePrivateData(refguid); }
	STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew) { return m_IDirect3DCubeTexture9->SetPriority(PriorityNew); }
	STDMETHOD_(DWORD, GetPriority)(THIS) { return m_IDirect3DCubeTexture9->GetPriority(); }
	STDMETHOD_(void, PreLoad)(THIS) { return m_IDirect3DCubeTexture9->PreLoad(); }
	STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS) { return m_IDirect3DCubeTexture9->GetType(); }
	STDMETHOD_(DWORD, SetLOD)(THIS_ DWORD LODNew) { return m_IDirect3DCubeTexture9->SetLOD(LODNew); }
	STDMETHOD_(DWORD, GetLOD)(THIS) { return m_IDirect3DCubeTexture9->GetLOD(); }
	STDMETHOD_(DWORD, GetLevelCount)(THIS) { return m_IDirect3DCubeTexture9->GetLevelCount(); }
	STDMETHOD(GetLevelDesc)(THIS_ UINT Level, D3DSURFACE_DESC *pDesc) { return m_IDirect3DCubeTexture9->GetLevelDesc(Level, pDesc); }
	STDMETHOD(GetCubeMapSurface)(THIS_ D3DCUBEMAP_FACES FaceType, UINT Level, IDirect3DSurface8** ppSurfaceLevel) {
		IDirect3DSurface9 *surf;
		HRESULT hr = m_IDirect3DCubeTexture9->GetCubeMapSurface(FaceType, Level, &surf);
		*ppSurfaceLevel = (IDirect3DSurface8*)new myIDirect3DSurface8(m_owner, this, surf);
		return hr;
	}

	STDMETHOD(LockRect)(THIS_ D3DCUBEMAP_FACES FaceType, UINT Level, D3DLOCKED_RECT* pLockedRect, CONST RECT* pRect, DWORD Flags) { return m_IDirect3DCubeTexture9->LockRect(FaceType, Level, pLockedRect, pRect, Flags); }
	STDMETHOD(UnlockRect)(THIS_ D3DCUBEMAP_FACES FaceType, UINT Level) { return m_IDirect3DCubeTexture9->UnlockRect(FaceType, Level); }
	STDMETHOD(AddDirtyRect)(THIS_ D3DCUBEMAP_FACES FaceType, CONST RECT* pDirtyRect) { return m_IDirect3DCubeTexture9->AddDirtyRect(FaceType, pDirtyRect); }

	myIDirect3DCubeTexture8(myIDirect3DDevice8 *owner, IDirect3DCubeTexture9* pOriginal) : m_owner(owner), m_IDirect3DCubeTexture9(pOriginal) {}
	virtual ~myIDirect3DCubeTexture8(void) {}

	myIDirect3DDevice8 *m_owner;
	IDirect3DCubeTexture9 *m_IDirect3DCubeTexture9;
};
class DECLSPEC_UUID("4B8AAAFA-140F-42ba-9131-597EAFAA2EAD") myIDirect3DVolumeTexture8
{
public:
	/*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj)
	{
		if (riid == IID_IDirect3DVolumeTexture8 || riid == IID_IUnknown)
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
	STDMETHOD_(ULONG, AddRef)(THIS) {
		return m_IDirect3DVolumeTexture9->AddRef();
	}
	STDMETHOD_(ULONG, Release)(THIS) {
		return m_IDirect3DVolumeTexture9->Release();
	}

	/*** IDirect3DBaseTexture8 methods ***/
	STDMETHOD(GetDevice)(THIS_ IDirect3DDevice8** ppDevice)
	{
		m_owner->AddRef();
		*ppDevice = (IDirect3DDevice8*)m_owner;
		return D3D_OK;
	}
	STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags) { return m_IDirect3DVolumeTexture9->SetPrivateData(refguid, pData, SizeOfData, Flags); }
	STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid, void* pData, DWORD* pSizeOfData) { return m_IDirect3DVolumeTexture9->GetPrivateData(refguid, pData, pSizeOfData); }
	STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) { return m_IDirect3DVolumeTexture9->FreePrivateData(refguid); }
	STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew) { return m_IDirect3DVolumeTexture9->SetPriority(PriorityNew); }
	STDMETHOD_(DWORD, GetPriority)(THIS) { return m_IDirect3DVolumeTexture9->GetPriority(); }
	STDMETHOD_(void, PreLoad)(THIS) { return m_IDirect3DVolumeTexture9->PreLoad(); }
	STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS) { return m_IDirect3DVolumeTexture9->GetType(); }
	STDMETHOD_(DWORD, SetLOD)(THIS_ DWORD LODNew) { return m_IDirect3DVolumeTexture9->SetLOD(LODNew); }
	STDMETHOD_(DWORD, GetLOD)(THIS) { return m_IDirect3DVolumeTexture9->GetLOD(); }
	STDMETHOD_(DWORD, GetLevelCount)(THIS) { return m_IDirect3DVolumeTexture9->GetLevelCount(); }
	STDMETHOD(GetLevelDesc)(THIS_ UINT Level, D3DVOLUME_DESC *pDesc) { return m_IDirect3DVolumeTexture9->GetLevelDesc(Level, pDesc); }
	STDMETHOD(GetVolumeLevel)(THIS_ UINT Level, IDirect3DVolume8** ppVolumeLevel)
	{
		IDirect3DVolume9 *surf;
		HRESULT hr = m_IDirect3DVolumeTexture9->GetVolumeLevel(Level, &surf);
		*ppVolumeLevel = NULL;	/// (IDirect3DVolume8*)new myIDirect3DVolume8(m_owner, this, surf);
		return hr;
	}
	STDMETHOD(LockBox)(THIS_ UINT Level, D3DLOCKED_BOX* pLockedVolume, CONST D3DBOX* pBox, DWORD Flags) { return m_IDirect3DVolumeTexture9->LockBox(Level, pLockedVolume, pBox, Flags); }
	STDMETHOD(UnlockBox)(THIS_ UINT Level) { return m_IDirect3DVolumeTexture9->UnlockBox(Level); }
	STDMETHOD(AddDirtyBox)(THIS_ CONST D3DBOX* pDirtyBox) { return m_IDirect3DVolumeTexture9->AddDirtyBox(pDirtyBox); }

	myIDirect3DVolumeTexture8(myIDirect3DDevice8 *owner, IDirect3DVolumeTexture9* pOriginal) : m_owner(owner), m_IDirect3DVolumeTexture9(pOriginal) {}
	virtual ~myIDirect3DVolumeTexture8(void) {}

	myIDirect3DDevice8 *m_owner;
	IDirect3DVolumeTexture9 *m_IDirect3DVolumeTexture9;
};
class DECLSPEC_UUID("8AEEEAC7-05F9-44d4-B591-000B0DF1CB95") myIDirect3DVertexBuffer8
{
public:
	/*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj)
	{
		if (riid == IID_IDirect3DVertexBuffer8 || riid == IID_IUnknown)
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
	STDMETHOD_(ULONG, AddRef)(THIS) {
		return m_IDirect3DVertexBuffer9->AddRef();
	}
	STDMETHOD_(ULONG, Release)(THIS) {
		return m_IDirect3DVertexBuffer9->Release();
	}

	/*** IDirect3DResource8 methods ***/
	STDMETHOD(GetDevice)(THIS_ IDirect3DDevice8** ppDevice)
	{
		m_owner->AddRef();
		*ppDevice = (IDirect3DDevice8*)m_owner;
		return D3D_OK;
	}
	STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags) { return m_IDirect3DVertexBuffer9->SetPrivateData(refguid, pData, SizeOfData, Flags); }
	STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid, void* pData, DWORD* pSizeOfData) { return m_IDirect3DVertexBuffer9->GetPrivateData(refguid, pData, pSizeOfData); }
	STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) { return m_IDirect3DVertexBuffer9->FreePrivateData(refguid); }
	STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew) { return m_IDirect3DVertexBuffer9->SetPriority(PriorityNew); }
	STDMETHOD_(DWORD, GetPriority)(THIS) { return m_IDirect3DVertexBuffer9->GetPriority(); }
	STDMETHOD_(void, PreLoad)(THIS) { return m_IDirect3DVertexBuffer9->PreLoad(); }
	STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS) { return m_IDirect3DVertexBuffer9->GetType(); }
	STDMETHOD(Lock)(THIS_ UINT OffsetToLock, UINT SizeToLock, BYTE** ppbData, DWORD Flags) { return m_IDirect3DVertexBuffer9->Lock(OffsetToLock, SizeToLock, (void **)ppbData, Flags); }
	STDMETHOD(Unlock)(THIS) { return m_IDirect3DVertexBuffer9->Unlock(); }
	STDMETHOD(GetDesc)(THIS_ D3DVERTEXBUFFER_DESC *pDesc) { return m_IDirect3DVertexBuffer9->GetDesc(pDesc); };

	myIDirect3DVertexBuffer8(myIDirect3DDevice8 *owner, IDirect3DVertexBuffer9* pOriginal) : m_owner(owner), m_IDirect3DVertexBuffer9(pOriginal) {}
	virtual ~myIDirect3DVertexBuffer8(void) {}

	myIDirect3DDevice8 *m_owner;
	IDirect3DVertexBuffer9 *m_IDirect3DVertexBuffer9;
};
class DECLSPEC_UUID("0E689C9A-053D-44a0-9D92-DB0E3D750F86") myIDirect3DIndexBuffer8
{
public:
	/*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj)
	{
		if (riid == IID_IDirect3DIndexBuffer8 || riid == IID_IUnknown)
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
	STDMETHOD_(ULONG, AddRef)(THIS) {
		return m_IDirect3DIndexBuffer9->AddRef();
	}
	STDMETHOD_(ULONG, Release)(THIS) {
		return m_IDirect3DIndexBuffer9->Release();
	}

	/*** IDirect3DResource8 methods ***/
	STDMETHOD(GetDevice)(THIS_ IDirect3DDevice8** ppDevice)
	{
		m_owner->AddRef();
		*ppDevice = (IDirect3DDevice8*)m_owner;
		return D3D_OK;
	}
	STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags) { return m_IDirect3DIndexBuffer9->SetPrivateData(refguid, pData, SizeOfData, Flags); }
	STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid, void* pData, DWORD* pSizeOfData) { return m_IDirect3DIndexBuffer9->GetPrivateData(refguid, pData, pSizeOfData); }
	STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) { return m_IDirect3DIndexBuffer9->FreePrivateData(refguid); }
	STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew) { return m_IDirect3DIndexBuffer9->SetPriority(PriorityNew); }
	STDMETHOD_(DWORD, GetPriority)(THIS) { return m_IDirect3DIndexBuffer9->GetPriority(); }
	STDMETHOD_(void, PreLoad)(THIS) { return m_IDirect3DIndexBuffer9->PreLoad(); }
	STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS) { return m_IDirect3DIndexBuffer9->GetType(); }
	STDMETHOD(Lock)(THIS_ UINT OffsetToLock, UINT SizeToLock, BYTE** ppbData, DWORD Flags) { return m_IDirect3DIndexBuffer9->Lock(OffsetToLock, SizeToLock, (void **)ppbData, Flags); }
	STDMETHOD(Unlock)(THIS) { return m_IDirect3DIndexBuffer9->Unlock(); }
	STDMETHOD(GetDesc)(THIS_ D3DINDEXBUFFER_DESC *pDesc) { return m_IDirect3DIndexBuffer9->GetDesc(pDesc); };

	myIDirect3DIndexBuffer8(myIDirect3DDevice8 *owner, IDirect3DIndexBuffer9* pOriginal) : m_owner(owner), m_IDirect3DIndexBuffer9(pOriginal) {}
	virtual ~myIDirect3DIndexBuffer8(void) {}

	myIDirect3DDevice8 *m_owner;
	IDirect3DIndexBuffer9 *m_IDirect3DIndexBuffer9;
};

class DECLSPEC_UUID("928C088B-76B9-4C6B-A536-A590853876CD") myIDirect3DSwapChain8
{
public:
	/*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj)
	{
		if (riid == IID_IDirect3DSwapChain8 || riid == IID_IUnknown)
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
	STDMETHOD_(ULONG, AddRef)(THIS) {
		return m_IDirect3DSwapChain9->AddRef();
	}
	STDMETHOD_(ULONG, Release)(THIS) {
		return m_IDirect3DSwapChain9->Release();
	}

	/*** IDirect3DSwapChain8 methods ***/
	STDMETHOD(Present)(THIS_ CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
	{
		return m_IDirect3DSwapChain9->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion, 0);
	}
	STDMETHOD(GetBackBuffer)(THIS_ UINT BackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface8** ppBackBuffer)
	{
		IDirect3DSurface9 *surf;
		HRESULT hr = m_IDirect3DSwapChain9->GetBackBuffer(BackBuffer, Type, &surf);

		*ppBackBuffer = (IDirect3DSurface8 *)new myIDirect3DSurface8(m_owner, NULL, surf);
		return hr;
	}

	myIDirect3DSwapChain8(myIDirect3DDevice8 *owner, IDirect3DSwapChain9* pOriginal) : m_owner(owner), m_IDirect3DSwapChain9(pOriginal) {}
	virtual ~myIDirect3DSwapChain8() {}

	myIDirect3DDevice8 *m_owner;
	IDirect3DSwapChain9 *m_IDirect3DSwapChain9;
};



//--------------------------------------------------------------------------------
myIDirect3DDevice8::myIDirect3DDevice8(myIDirect3D8 *d3d8, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice9* pOriginal)
{


	m_d3d8 = d3d8;

	m_pIDirect3DDevice9 = pOriginal; // store the pointer to original object
}

myIDirect3DDevice8::~myIDirect3DDevice8(void)
{
}

STDMETHODIMP
myIDirect3DDevice8::QueryInterface(REFIID riid, void** ppvObj)
{

	// check if original dll can provide interface. then send *our* address
	*ppvObj = NULL;

	if (riid == IID_IDirect3DDevice8 || riid == IID_IUnknown)
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
myIDirect3DDevice8::AddRef(void)
{

	return m_pIDirect3DDevice9->AddRef();
}

STDMETHODIMP_(ULONG)
myIDirect3DDevice8::Release(void)
{

	ULONG count = m_pIDirect3DDevice9->Release();
	if (count == 0)
	{
		delete(this);
	}

	return count;
}

STDMETHODIMP
myIDirect3DDevice8::TestCooperativeLevel(void)
{


	// FIXME: do we need to return D3DERR_DEVICELOST if we lose the connection?
	return D3D_OK;

	return(m_pIDirect3DDevice9->TestCooperativeLevel());
}

STDMETHODIMP_(UINT)
myIDirect3DDevice8::GetAvailableTextureMem(void)
{


	// FIXME: is this something we need to get from client profile?
	UINT tm = 256;

	if (m_pIDirect3DDevice9)
		tm = m_pIDirect3DDevice9->GetAvailableTextureMem();

	return(tm);
}

STDMETHODIMP
myIDirect3DDevice8::ResourceManagerDiscardBytes(DWORD Bytes)
{

	return D3D_OK;
}

STDMETHODIMP
myIDirect3DDevice8::GetDirect3D(IDirect3D8** ppD3D9)
{

	m_d3d8->AddRef();
	*ppD3D9 = (IDirect3D8 *)m_d3d8;
	return S_OK;
}

STDMETHODIMP
myIDirect3DDevice8::GetDeviceCaps(D3DCAPS8* pCaps)
{

	D3DCAPS9 caps;
	m_pIDirect3DDevice9->GetDeviceCaps(&caps);
	memcpy(pCaps, &caps, sizeof(D3DCAPS8));

	// deprecated stuff
	pCaps->Caps2 |= D3DCAPS2_CANRENDERWINDOWED;

	return S_OK;
}

STDMETHODIMP
myIDirect3DDevice8::GetDisplayMode(D3DDISPLAYMODE* pMode)
{

	m_pIDirect3DDevice9->GetDisplayMode(0, pMode);
	return S_OK;
}

STDMETHODIMP
myIDirect3DDevice8::GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS *pParameters)
{

	m_pIDirect3DDevice9->GetCreationParameters(pParameters);
	return S_OK;
}

STDMETHODIMP
myIDirect3DDevice8::SetCursorProperties(UINT XHotSpot, UINT YHotSpot, IDirect3DSurface8* pCursorBitmap)
{


	m_pIDirect3DDevice9->SetCursorProperties(XHotSpot, YHotSpot, (IDirect3DSurface9*)pCursorBitmap);

	return S_OK;
}

void
myIDirect3DDevice8::SetCursorPosition(int X, int Y, DWORD Flags)
{

	m_pIDirect3DDevice9->SetCursorPosition(X, Y, Flags);
}

BOOL
myIDirect3DDevice8::ShowCursor(BOOL bShow)
{

	m_pIDirect3DDevice9->ShowCursor(bShow);

	// FIXME: should be old value
	return bShow;
}

STDMETHODIMP
myIDirect3DDevice8::CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain8** pSwapChain)
{

	IDirect3DSwapChain9 *realSwap = NULL;
	HRESULT hr = m_pIDirect3DDevice9->CreateAdditionalSwapChain(pPresentationParameters, &realSwap);

	// number of swapchains is apparently unbounded..
	myIDirect3DSwapChain8 *proxy = new myIDirect3DSwapChain8(this, realSwap);

	*pSwapChain = (IDirect3DSwapChain8 *)proxy;
	return hr;
}

STDMETHODIMP
myIDirect3DDevice8::Reset(D3DPRESENT_PARAMETERS8* pPresentationParameters)
{
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

	m_pIDirect3DDevice9->Reset(&d3dpp);

	return D3D_OK;
}

STDMETHODIMP
myIDirect3DDevice8::Present(CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
{

	return m_pIDirect3DDevice9->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

STDMETHODIMP
myIDirect3DDevice8::GetBackBuffer(UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface8** ppBackBuffer)
{

	IDirect3DSurface9 *realSurf = NULL;

	HRESULT hr = m_pIDirect3DDevice9->GetBackBuffer(0, iBackBuffer, Type, &realSurf);

	myIDirect3DSurface8 *proxy = new myIDirect3DSurface8(this, NULL, realSurf);

	D3DSURFACE_DESC desc;
	proxy->GetDesc(&desc);

	*ppBackBuffer = (IDirect3DSurface8 *)proxy;

	return S_OK;
}

STDMETHODIMP
myIDirect3DDevice8::GetRasterStatus(D3DRASTER_STATUS* pRasterStatus)
{
	return(m_pIDirect3DDevice9->GetRasterStatus(0, pRasterStatus));
}

void
myIDirect3DDevice8::SetGammaRamp(DWORD Flags, CONST D3DGAMMARAMP* pRamp)
{
	m_pIDirect3DDevice9->SetGammaRamp(0, Flags, pRamp);
}

void
myIDirect3DDevice8::GetGammaRamp(D3DGAMMARAMP* pRamp)
{

	return(m_pIDirect3DDevice9->GetGammaRamp(0, pRamp));
}

STDMETHODIMP
myIDirect3DDevice8::CreateTexture(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture8** ppTexture)
{


	// NB we always force SharedHandle to NULL and use it in proxy
	IDirect3DTexture9* realTexture = NULL;
	HRESULT hr = D3D_OK;
	if (m_pIDirect3DDevice9)
		hr = m_pIDirect3DDevice9->CreateTexture(Width, Height, Levels, Usage, Format, Pool, &realTexture, NULL);

	if (hr == S_OK)
	{
		*ppTexture = (IDirect3DTexture8 *)new myIDirect3DTexture8(this, realTexture);
	}

	return(hr);
}

STDMETHODIMP
myIDirect3DDevice8::CreateVolumeTexture(UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture8** ppVolumeTexture)
{

	IDirect3DVolumeTexture9* realTexture = NULL;
	HRESULT hr = D3D_OK;
	if (m_pIDirect3DDevice9)
		hr = m_pIDirect3DDevice9->CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, &realTexture, NULL);

	if (hr == S_OK)
	{
		*ppVolumeTexture = (IDirect3DVolumeTexture8 *)new myIDirect3DVolumeTexture8(this, realTexture);
	}

	return(hr);
}

STDMETHODIMP
myIDirect3DDevice8::CreateCubeTexture(UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture8** ppCubeTexture)
{


	IDirect3DCubeTexture9* realTexture = NULL;
	HRESULT hr = D3D_OK;
	if (m_pIDirect3DDevice9)
		hr = m_pIDirect3DDevice9->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, &realTexture, NULL);

	if (hr == S_OK)
	{
		*ppCubeTexture = (IDirect3DCubeTexture8 *)new myIDirect3DCubeTexture8(this, realTexture);
	}

	return(hr);
}

STDMETHODIMP
myIDirect3DDevice8::CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer8** ppVertexBuffer)
{
	IDirect3DVertexBuffer9* realVB = NULL;
	HRESULT hr = S_OK;
	if (m_pIDirect3DDevice9)
		hr = m_pIDirect3DDevice9->CreateVertexBuffer(Length, Usage, FVF, Pool, &realVB, NULL);
	if (hr == S_OK)
	{
		*ppVertexBuffer = (IDirect3DVertexBuffer8 *)new myIDirect3DVertexBuffer8(this, realVB);
	}

	return(hr);
}

STDMETHODIMP
myIDirect3DDevice8::CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer8** ppIndexBuffer)
{

	IDirect3DIndexBuffer9* realIB = NULL;
	HRESULT hr = S_OK;
	if (m_pIDirect3DDevice9)
		hr = m_pIDirect3DDevice9->CreateIndexBuffer(Length, Usage, Format, Pool, &realIB, NULL);
	if (hr == S_OK)
	{
		*ppIndexBuffer = (IDirect3DIndexBuffer8 *)new myIDirect3DIndexBuffer8(this, realIB);
	}

	return(hr);
}

STDMETHODIMP
myIDirect3DDevice8::CreateRenderTarget(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface8** ppSurface)
{

	IDirect3DSurface9 *realSurf = NULL;
	HRESULT hr = D3D_OK;
	if (m_pIDirect3DDevice9)
		hr = m_pIDirect3DDevice9->CreateRenderTarget(Width, Height, Format, MultiSample, MultisampleQuality, Lockable, &realSurf, NULL);

	myIDirect3DSurface8 *proxy = new myIDirect3DSurface8(this, NULL, realSurf);
	*ppSurface = (IDirect3DSurface8 *)proxy;

	return hr;
}

STDMETHODIMP
myIDirect3DDevice8::CreateDepthStencilSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface8** ppSurface)
{

	IDirect3DSurface9 *realSurf = NULL;
	HRESULT hr = D3D_OK;
	if (m_pIDirect3DDevice9)
		hr = m_pIDirect3DDevice9->CreateDepthStencilSurface(Width, Height, Format, MultiSample, MultisampleQuality, Discard, &realSurf, NULL);

	myIDirect3DSurface8 *proxy = new myIDirect3DSurface8(this, NULL, realSurf);
	*ppSurface = (IDirect3DSurface8 *)proxy;

	return hr;
}

STDMETHODIMP
myIDirect3DDevice8::CopyRects(IDirect3DSurface8* pSourceSurface, CONST RECT* pSourceRectsArray, UINT cRects, IDirect3DSurface8* pDestinationSurface, CONST POINT* pDestPointsArray)
{

	D3DSURFACE_DESC desc;
	pDestinationSurface->GetDesc(&desc);

	RECT destrect;
	destrect.left = 0;
	destrect.top = 0;
	destrect.right = desc.Width;
	destrect.bottom = desc.Height;
	if (pDestPointsArray)
	{
		destrect.left = pDestPointsArray->x;
		destrect.top = pDestPointsArray->y;
	}
	if (pSourceRectsArray)
	{
		destrect.right = pSourceRectsArray->right - destrect.left;
		destrect.right = pSourceRectsArray->bottom - destrect.top;
	}

	IDirect3DSurface9 *mySrc = 0;
	if (pSourceSurface)
		mySrc = ((myIDirect3DSurface8*)pSourceSurface)->m_IDirect3DSurface9;
	IDirect3DSurface9 *myDst = 0;
	if (pDestinationSurface)
		myDst = ((myIDirect3DSurface8*)pDestinationSurface)->m_IDirect3DSurface9;

	return m_pIDirect3DDevice9->StretchRect(mySrc, pSourceRectsArray, myDst, &destrect, D3DTEXF_LINEAR);
}

STDMETHODIMP
myIDirect3DDevice8::UpdateTexture(IDirect3DBaseTexture8* pSourceTexture, IDirect3DBaseTexture8* pDestinationTexture)
{

	D3DRESOURCETYPE stype = D3DRTYPE_FORCE_DWORD;
	if (pSourceTexture) stype = pSourceTexture->GetType();

	D3DRESOURCETYPE dtype = D3DRTYPE_FORCE_DWORD;
	if (pDestinationTexture) dtype = pDestinationTexture->GetType();

	IDirect3DBaseTexture9 *mySrc = 0;
	IDirect3DBaseTexture9 *myDst = 0;

	if (pSourceTexture)
	{
		if (stype == D3DRTYPE_TEXTURE)
			mySrc = ((myIDirect3DTexture8 *)pSourceTexture)->m_IDirect3DTexture9;
		else
			if (stype == D3DRTYPE_CUBETEXTURE)
				mySrc = ((myIDirect3DCubeTexture8 *)pSourceTexture)->m_IDirect3DCubeTexture9;
			else
				if (stype == D3DRTYPE_VOLUMETEXTURE)
					mySrc = ((myIDirect3DVolumeTexture8 *)pSourceTexture)->m_IDirect3DVolumeTexture9;
	}


	if (pDestinationTexture)
	{
		if (dtype == D3DRTYPE_TEXTURE)
			myDst = ((myIDirect3DTexture8 *)pDestinationTexture)->m_IDirect3DTexture9;
		else if (dtype == D3DRTYPE_CUBETEXTURE)
			myDst = ((myIDirect3DCubeTexture8 *)pDestinationTexture)->m_IDirect3DCubeTexture9;
		else if (dtype == D3DRTYPE_VOLUMETEXTURE)
			myDst = ((myIDirect3DVolumeTexture8 *)pDestinationTexture)->m_IDirect3DVolumeTexture9;
		// TODO: Other types.
	}

	m_pIDirect3DDevice9->UpdateTexture(mySrc, myDst);

	return D3D_OK;
}


STDMETHODIMP
myIDirect3DDevice8::CreateImageSurface(UINT Width, UINT Height, D3DFORMAT Format, IDirect3DSurface8** ppSurface)
{

	IDirect3DSurface9 *realSurf = NULL;
	HRESULT hr = D3D_OK;
	if (m_pIDirect3DDevice9)
		hr = m_pIDirect3DDevice9->CreateOffscreenPlainSurface(Width, Height, Format, D3DPOOL_MANAGED, &realSurf, NULL);// FIXME:  is MANAGED correct?

	myIDirect3DSurface8 *proxy = new myIDirect3DSurface8(this, NULL, realSurf);
	*ppSurface = (IDirect3DSurface8 *)proxy;

	return hr;
}
STDMETHODIMP
myIDirect3DDevice8::GetFrontBuffer(IDirect3DSurface8* pDestSurface)
{
	return D3DERR_NOTAVAILABLE;
}

STDMETHODIMP
myIDirect3DDevice8::SetRenderTarget(IDirect3DSurface8* pRenderTarget, IDirect3DSurface8* pZRenderTarget)
{

	IDirect3DSurface9 *myRT = 0;
	if (pRenderTarget)
		myRT = ((myIDirect3DSurface8 *)pRenderTarget)->m_IDirect3DSurface9;

	m_pIDirect3DDevice9->SetRenderTarget(0, myRT);

	IDirect3DSurface9 *myRTZ = 0;
	if (pZRenderTarget)
		myRTZ = ((myIDirect3DSurface8 *)pZRenderTarget)->m_IDirect3DSurface9;

	m_pIDirect3DDevice9->SetDepthStencilSurface(myRTZ);

	return D3D_OK;
}

STDMETHODIMP
myIDirect3DDevice8::GetRenderTarget(IDirect3DSurface8** ppRenderTarget)
{
	IDirect3DSurface9 *myRT;
	m_pIDirect3DDevice9->GetRenderTarget(0, &myRT);

	myIDirect3DSurface8 *proxy = new myIDirect3DSurface8(this, NULL, myRT);
	*ppRenderTarget = (IDirect3DSurface8 *)proxy;

	return S_OK;
}

STDMETHODIMP
myIDirect3DDevice8::GetDepthStencilSurface(IDirect3DSurface8** ppZStencilSurface)
{

	IDirect3DSurface9 *realSurf = NULL;
	HRESULT hr = D3D_OK;
	hr = m_pIDirect3DDevice9->GetDepthStencilSurface(&realSurf);

	myIDirect3DSurface8 *proxy = new myIDirect3DSurface8(this, NULL, realSurf);
	*ppZStencilSurface = (IDirect3DSurface8 *)proxy;

	return S_OK;
}

STDMETHODIMP
myIDirect3DDevice8::BeginScene(void)
{
	m_pIDirect3DDevice9->BeginScene();
	return D3D_OK;
}

STDMETHODIMP
myIDirect3DDevice8::EndScene(void)
{
	m_pIDirect3DDevice9->EndScene();
	return D3D_OK;
}

STDMETHODIMP
myIDirect3DDevice8::Clear(DWORD Count, CONST D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil)
{
	HRESULT hr = m_pIDirect3DDevice9->Clear(Count, pRects, Flags, Color, Z, Stencil);
	return hr;
}

STDMETHODIMP
myIDirect3DDevice8::SetTransform(D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* pMatrix)
{
	HRESULT hr = m_pIDirect3DDevice9->SetTransform(State, pMatrix);
	return hr;
}

STDMETHODIMP
myIDirect3DDevice8::GetTransform(D3DTRANSFORMSTATETYPE State, D3DMATRIX* pMatrix)
{
	HRESULT hr = m_pIDirect3DDevice9->GetTransform(State, pMatrix);
	return(D3D_OK);
}

STDMETHODIMP
myIDirect3DDevice8::MultiplyTransform(D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* pMatrix)
{
	m_pIDirect3DDevice9->MultiplyTransform(State, pMatrix);
	return D3D_OK;
}

STDMETHODIMP
myIDirect3DDevice8::SetViewport(CONST D3DVIEWPORT8* pViewport)
{

	HRESULT hr = m_pIDirect3DDevice9->SetViewport((D3DVIEWPORT9*)pViewport);
	return hr;
}

STDMETHODIMP
myIDirect3DDevice8::GetViewport(D3DVIEWPORT8* pViewport)
{
	m_pIDirect3DDevice9->GetViewport((D3DVIEWPORT9*)pViewport);
	return D3D_OK;
}

STDMETHODIMP
myIDirect3DDevice8::SetMaterial(CONST D3DMATERIAL8* pMaterial)
{

	return m_pIDirect3DDevice9->SetMaterial((D3DMATERIAL9*)pMaterial);
}

STDMETHODIMP
myIDirect3DDevice8::GetMaterial(D3DMATERIAL8* pMaterial)
{
	return 	m_pIDirect3DDevice9->GetMaterial((D3DMATERIAL9*)pMaterial);
}

STDMETHODIMP
myIDirect3DDevice8::SetLight(DWORD Index, CONST D3DLIGHT8* pLight)
{
	return(m_pIDirect3DDevice9->SetLight(Index, (D3DLIGHT9*)pLight));
}

STDMETHODIMP
myIDirect3DDevice8::GetLight(DWORD Index, D3DLIGHT8* pLight)
{
	return(m_pIDirect3DDevice9->GetLight(Index, (D3DLIGHT9*)pLight));
}

STDMETHODIMP
myIDirect3DDevice8::LightEnable(DWORD Index, BOOL Enable)
{

	return m_pIDirect3DDevice9->LightEnable(Index, Enable);
}

STDMETHODIMP
myIDirect3DDevice8::GetLightEnable(DWORD Index, BOOL* pEnable)
{

	return m_pIDirect3DDevice9->GetLightEnable(Index, pEnable);
}

STDMETHODIMP
myIDirect3DDevice8::SetClipPlane(DWORD Index, CONST float* pPlane)
{

	return m_pIDirect3DDevice9->SetClipPlane(Index, pPlane);
}

STDMETHODIMP
myIDirect3DDevice8::GetClipPlane(DWORD Index, float* pPlane)
{
	return m_pIDirect3DDevice9->GetClipPlane(Index, pPlane);
}

STDMETHODIMP
myIDirect3DDevice8::SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)
{
	return m_pIDirect3DDevice9->SetRenderState(State, Value);
}

STDMETHODIMP
myIDirect3DDevice8::GetRenderState(D3DRENDERSTATETYPE State, DWORD* pValue)
{
	return m_pIDirect3DDevice9->GetRenderState(State, pValue);
}

STDMETHODIMP
myIDirect3DDevice8::CreateStateBlock(D3DSTATEBLOCKTYPE Type, DWORD* ppSB)
{


	IDirect3DStateBlock9 *realBlock = NULL;
	HRESULT hr = m_pIDirect3DDevice9->CreateStateBlock(Type, &realBlock);
	*ppSB = (DWORD)realBlock;

	return hr;
}

STDMETHODIMP
myIDirect3DDevice8::BeginStateBlock(void)
{

	return m_pIDirect3DDevice9->BeginStateBlock();
}

STDMETHODIMP
myIDirect3DDevice8::EndStateBlock(DWORD* ppSB)
{


	IDirect3DStateBlock9 *realBlock = NULL;
	HRESULT hr = m_pIDirect3DDevice9->EndStateBlock(&realBlock);
	*ppSB = (DWORD)realBlock;
	return hr;
}

STDMETHODIMP
myIDirect3DDevice8::ApplyStateBlock(DWORD Token)
{
	IDirect3DStateBlock9 *realBlock = (IDirect3DStateBlock9 *)Token;
	return realBlock->Apply();
}

STDMETHODIMP
myIDirect3DDevice8::CaptureStateBlock(DWORD Token)
{
	IDirect3DStateBlock9 *realBlock = (IDirect3DStateBlock9 *)Token;
	return realBlock->Capture();
}

STDMETHODIMP
myIDirect3DDevice8::DeleteStateBlock(DWORD Token)
{
	IDirect3DStateBlock9 *realBlock = (IDirect3DStateBlock9 *)Token;
	realBlock->Release();
	return D3D_OK;
}


STDMETHODIMP
myIDirect3DDevice8::SetClipStatus(CONST D3DCLIPSTATUS8* pClipStatus)
{
	return(m_pIDirect3DDevice9->SetClipStatus((D3DCLIPSTATUS9*)pClipStatus));
}

STDMETHODIMP
myIDirect3DDevice8::GetClipStatus(D3DCLIPSTATUS8* pClipStatus)
{

	return(m_pIDirect3DDevice9->GetClipStatus((D3DCLIPSTATUS9*)pClipStatus));
}

STDMETHODIMP
myIDirect3DDevice8::GetTexture(DWORD Stage, IDirect3DBaseTexture8** ppTexture)
{
	IDirect3DBaseTexture9 *realtex;
	m_pIDirect3DDevice9->GetTexture(Stage, &realtex);

	D3DRESOURCETYPE type = D3DRTYPE_FORCE_DWORD;
	if (realtex) type = realtex->GetType();


	return(D3D_OK);
}

STDMETHODIMP
myIDirect3DDevice8::SetTexture(DWORD Stage, IDirect3DBaseTexture8* pTexture)
{


	D3DRESOURCETYPE type = D3DRTYPE_FORCE_DWORD;
	if (pTexture) type = pTexture->GetType();

	IDirect3DBaseTexture9 *mySrc = 0;
	if (pTexture)
	{
		if (type == D3DRTYPE_TEXTURE)
			mySrc = ((myIDirect3DTexture8 *)pTexture)->m_IDirect3DTexture9;
		else
			if (type == D3DRTYPE_CUBETEXTURE)
				mySrc = ((myIDirect3DCubeTexture8 *)pTexture)->m_IDirect3DCubeTexture9;
			else
				if (type == D3DRTYPE_VOLUMETEXTURE)
					mySrc = ((myIDirect3DVolumeTexture8 *)pTexture)->m_IDirect3DVolumeTexture9;
	}

	m_pIDirect3DDevice9->SetTexture(Stage, mySrc);

	return D3D_OK;
}

STDMETHODIMP
myIDirect3DDevice8::GetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD* pValue)
{
	return 	m_pIDirect3DDevice9->GetTextureStageState(Stage, Type, pValue);
}

STDMETHODIMP
myIDirect3DDevice8::SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value)
{
	// between D3DTSS_ADDRESSU and D3DTSS_MAXANISOTROPY
	if (Type >= 13 && Type <= 21)
	{
		D3DSAMPLERSTATETYPE map2ss[] = {
			D3DSAMP_ADDRESSU,
			D3DSAMP_ADDRESSV,
			D3DSAMP_BORDERCOLOR,
			D3DSAMP_MAGFILTER,
			D3DSAMP_MINFILTER,
			D3DSAMP_MIPFILTER,
			D3DSAMP_MIPMAPLODBIAS,
			D3DSAMP_MAXMIPLEVEL,
			D3DSAMP_MAXANISOTROPY
		};

		D3DSAMPLERSTATETYPE ss = map2ss[Type - 13];
		return 	m_pIDirect3DDevice9->SetSamplerState(Stage, ss, Value);
	}
	else
	{
		return 	m_pIDirect3DDevice9->SetTextureStageState(Stage, Type, Value);
	}
}

STDMETHODIMP
myIDirect3DDevice8::ValidateDevice(DWORD* pNumPasses)
{

	return m_pIDirect3DDevice9->ValidateDevice(pNumPasses);
}

STDMETHODIMP
myIDirect3DDevice8::GetInfo(DWORD DevInfoID, void* pDevInfoStruct, DWORD DevInfoStructSize)
{

	return E_FAIL;
}

STDMETHODIMP
myIDirect3DDevice8::SetPaletteEntries(UINT PaletteNumber, CONST PALETTEENTRY* pEntries)
{

	return(m_pIDirect3DDevice9->SetPaletteEntries(PaletteNumber, pEntries));
}

STDMETHODIMP
myIDirect3DDevice8::GetPaletteEntries(UINT PaletteNumber, PALETTEENTRY* pEntries)
{
	return(m_pIDirect3DDevice9->GetPaletteEntries(PaletteNumber, pEntries));
	return D3D_OK;
}

STDMETHODIMP
myIDirect3DDevice8::SetCurrentTexturePalette(UINT PaletteNumber)
{

	return(m_pIDirect3DDevice9->SetCurrentTexturePalette(PaletteNumber));
}

STDMETHODIMP
myIDirect3DDevice8::GetCurrentTexturePalette(UINT *PaletteNumber)
{

	return(m_pIDirect3DDevice9->GetCurrentTexturePalette(PaletteNumber));
}


STDMETHODIMP
myIDirect3DDevice8::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
{
	return m_pIDirect3DDevice9->DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);
}

STDMETHODIMP
myIDirect3DDevice8::DrawIndexedPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT PrimitiveCount)
{

	return m_pIDirect3DDevice9->DrawIndexedPrimitive(PrimitiveType, 0, MinVertexIndex, NumVertices, startIndex, PrimitiveCount);
}

STDMETHODIMP
myIDirect3DDevice8::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{

	return m_pIDirect3DDevice9->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
}

STDMETHODIMP
myIDirect3DDevice8::DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT PrimitiveCount, CONST void* pIndexData, D3DFORMAT IndexDataFormat, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{

	return m_pIDirect3DDevice9->DrawIndexedPrimitiveUP(PrimitiveType, MinVertexIndex, NumVertices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
}

STDMETHODIMP
myIDirect3DDevice8::ProcessVertices(UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer8* pDestBuffer, DWORD Flags)
{

	return(m_pIDirect3DDevice9->ProcessVertices(SrcStartIndex, DestIndex, VertexCount, ((myIDirect3DVertexBuffer8*)pDestBuffer)->m_IDirect3DVertexBuffer9, NULL, Flags));
}




STDMETHODIMP
myIDirect3DDevice8::CreateVertexShader(CONST DWORD* pDeclaration, CONST DWORD* pFunction, DWORD* ppShader, DWORD Usage)
{

	IDirect3DVertexShader9* realShader = NULL;
	HRESULT hr = m_pIDirect3DDevice9->CreateVertexShader(pFunction, &realShader);
	*ppShader = (DWORD)realShader;
	return hr;
}

STDMETHODIMP
myIDirect3DDevice8::SetVertexShader(DWORD pShader)
{
	m_pIDirect3DDevice9->SetVertexShader(NULL);
	return m_pIDirect3DDevice9->SetFVF(pShader);
}

STDMETHODIMP
myIDirect3DDevice8::GetVertexShader(DWORD* ppShader)
{
	return m_pIDirect3DDevice9->GetFVF(ppShader);
}

STDMETHODIMP
myIDirect3DDevice8::DeleteVertexShader(DWORD ppShader)
{
	IDirect3DVertexShader9* realShader = (IDirect3DVertexShader9*)ppShader;
	return realShader->Release();
}

STDMETHODIMP
myIDirect3DDevice8::SetVertexShaderConstant(UINT StartRegister, CONST float* pConstantData, UINT Vector4fCount)
{

	return m_pIDirect3DDevice9->SetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);

}

STDMETHODIMP
myIDirect3DDevice8::GetVertexShaderConstant(UINT StartRegister, float* pConstantData, UINT Vector4fCount)
{
	return m_pIDirect3DDevice9->GetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

STDMETHODIMP
myIDirect3DDevice8::GetVertexShaderDeclaration(DWORD Handle, void* pData, DWORD* pSizeOfData)
{

	return NULL;
}
STDMETHODIMP
myIDirect3DDevice8::GetVertexShaderFunction(DWORD Handle, void* pData, DWORD* pSizeOfData)
{

	return NULL;
}

STDMETHODIMP
myIDirect3DDevice8::SetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer8* pStreamData, UINT Stride)
{
	IDirect3DVertexBuffer9 *vbo = 0;
	if (pStreamData)
		vbo = ((myIDirect3DVertexBuffer8*)pStreamData)->m_IDirect3DVertexBuffer9;

	return m_pIDirect3DDevice9->SetStreamSource(StreamNumber, vbo, 0, Stride);
}

STDMETHODIMP
myIDirect3DDevice8::GetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer8** ppStreamData, UINT* pStride)
{
	IDirect3DVertexBuffer9 *vbo;
	UINT OffsetInBytes;
	m_pIDirect3DDevice9->GetStreamSource(StreamNumber, &vbo, &OffsetInBytes, pStride);

	// no way of getting back to dx8 VBO...

	return D3D_OK;
}


STDMETHODIMP
myIDirect3DDevice8::SetIndices(IDirect3DIndexBuffer8* pIndexData)
{

	IDirect3DIndexBuffer9 *ibo = 0;
	if (pIndexData)
		ibo = ((myIDirect3DIndexBuffer8*)pIndexData)->m_IDirect3DIndexBuffer9;

	return m_pIDirect3DDevice9->SetIndices(ibo);
}

STDMETHODIMP
myIDirect3DDevice8::GetIndices(IDirect3DIndexBuffer8** ppIndexData)
{
	IDirect3DIndexBuffer9 *ibo;
	return m_pIDirect3DDevice9->GetIndices(&ibo);

	// no way of getting back to dx8
}

STDMETHODIMP
myIDirect3DDevice8::CreatePixelShader(CONST DWORD* pFunction, DWORD* ppShader)
{


	IDirect3DPixelShader9* realShader = NULL;
	HRESULT hr = m_pIDirect3DDevice9->CreatePixelShader(pFunction, &realShader);
	*ppShader = (DWORD)realShader;
	return hr;
}

STDMETHODIMP
myIDirect3DDevice8::SetPixelShader(DWORD pShader)
{

	return m_pIDirect3DDevice9->SetPixelShader((IDirect3DPixelShader9*)pShader);
}

STDMETHODIMP
myIDirect3DDevice8::GetPixelShader(DWORD* ppShader)
{

	return m_pIDirect3DDevice9->GetPixelShader((IDirect3DPixelShader9**)ppShader);
}

STDMETHODIMP
myIDirect3DDevice8::DeletePixelShader(DWORD ppShader)
{
	IDirect3DPixelShader9* realShader = (IDirect3DPixelShader9*)ppShader;
	return realShader->Release();
}


STDMETHODIMP
myIDirect3DDevice8::SetPixelShaderConstant(UINT StartRegister, CONST float* pConstantData, UINT Vector4fCount)
{

	return m_pIDirect3DDevice9->SetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

STDMETHODIMP
myIDirect3DDevice8::GetPixelShaderConstant(UINT StartRegister, float* pConstantData, UINT Vector4fCount)
{
	return m_pIDirect3DDevice9->GetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

STDMETHODIMP
myIDirect3DDevice8::GetPixelShaderFunction(DWORD Handle, void* pData, DWORD* pSizeOfData)
{

	return NULL;
}


STDMETHODIMP
myIDirect3DDevice8::DrawRectPatch(UINT Handle, CONST float* pNumSegs, CONST D3DRECTPATCH_INFO* pRectPatchInfo)
{
	return m_pIDirect3DDevice9->DrawRectPatch(Handle, pNumSegs, pRectPatchInfo);
}

STDMETHODIMP
myIDirect3DDevice8::DrawTriPatch(UINT Handle, CONST float* pNumSegs, CONST D3DTRIPATCH_INFO* pTriPatchInfo)
{
	return m_pIDirect3DDevice9->DrawTriPatch(Handle, pNumSegs, pTriPatchInfo);
}

STDMETHODIMP
myIDirect3DDevice8::DeletePatch(UINT Handle)
{

	return m_pIDirect3DDevice9->DeletePatch(Handle);
}

