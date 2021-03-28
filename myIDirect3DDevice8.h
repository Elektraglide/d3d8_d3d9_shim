// $Rev: 9179 $ $Date: 2016-01-20 19:05:26 +0000 (Wed, 20 Jan 2016) $
// Copyright (c) 2012 Adam Billyard.
// All Rights Reserved.

#pragma once

interface DECLSPEC_UUID("81BDCBCA-64D4-426d-AE8D-AD0147F4275C") IDirect3D9;
interface DECLSPEC_UUID("D0223B96-BF7A-43fd-92BD-A43B0D82B9EB") IDirect3DDevice9;

class DECLSPEC_UUID("7385E5DF-8FE8-41D5-86B6-D7B48547B6CF") myIDirect3DDevice8 //: public IDirect3DDevice8
{
public:
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj);
	STDMETHOD_(ULONG, AddRef)(THIS);
	STDMETHOD_(ULONG, Release)(THIS);

	/*** IDirect3DDevice9 methods ***/
	STDMETHOD(TestCooperativeLevel)(THIS);
	STDMETHOD_(UINT, GetAvailableTextureMem)(THIS);
	STDMETHOD(ResourceManagerDiscardBytes)(THIS_ DWORD Bytes);
	STDMETHOD(GetDirect3D)(THIS_ IDirect3D8** ppD3D9);
	STDMETHOD(GetDeviceCaps)(THIS_ D3DCAPS8* pCaps);
	STDMETHOD(GetDisplayMode)(THIS_ D3DDISPLAYMODE* pMode);
	STDMETHOD(GetCreationParameters)(THIS_ D3DDEVICE_CREATION_PARAMETERS *pParameters);
	STDMETHOD(SetCursorProperties)(THIS_ UINT XHotSpot, UINT YHotSpot, IDirect3DSurface8* pCursorBitmap);
	STDMETHOD_(void, SetCursorPosition)(THIS_ int X, int Y, DWORD Flags);
	STDMETHOD_(BOOL, ShowCursor)(THIS_ BOOL bShow);
	STDMETHOD(CreateAdditionalSwapChain)(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain8** pSwapChain);
	STDMETHOD(Reset)(THIS_ D3DPRESENT_PARAMETERS8* pPresentationParameters);
	STDMETHOD(Present)(THIS_ CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion);
	STDMETHOD(GetBackBuffer)(THIS_ UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface8** ppBackBuffer);
	STDMETHOD(GetRasterStatus)(THIS_ D3DRASTER_STATUS* pRasterStatus);
	STDMETHOD_(void, SetGammaRamp)(THIS_ DWORD Flags, CONST D3DGAMMARAMP* pRamp);
	STDMETHOD_(void, GetGammaRamp)(THIS_ D3DGAMMARAMP* pRamp);
	STDMETHOD(CreateTexture)(THIS_ UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture8** ppTexture);
	STDMETHOD(CreateVolumeTexture)(THIS_ UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture8** ppVolumeTexture);
	STDMETHOD(CreateCubeTexture)(THIS_ UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture8** ppCubeTexture);
	STDMETHOD(CreateVertexBuffer)(THIS_ UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer8** ppVertexBuffer);
	STDMETHOD(CreateIndexBuffer)(THIS_ UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer8** ppIndexBuffer);
	STDMETHOD(CreateRenderTarget)(THIS_ UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface8** ppSurface);
	STDMETHOD(CreateDepthStencilSurface)(THIS_ UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface8** ppSurface);
	STDMETHOD(CreateImageSurface)(THIS_ UINT Width, UINT Height, D3DFORMAT Format, IDirect3DSurface8** ppSurface);
	STDMETHOD(CopyRects)(THIS_ IDirect3DSurface8* pSourceSurface, CONST RECT* pSourceRectsArray, UINT cRects, IDirect3DSurface8* pDestinationSurface, CONST POINT* pDestPointsArray);
	STDMETHOD(UpdateTexture)(THIS_ IDirect3DBaseTexture8* pSourceTexture, IDirect3DBaseTexture8* pDestinationTexture);
	STDMETHOD(GetFrontBuffer)(THIS_ IDirect3DSurface8* pDestSurface);
	STDMETHOD(SetRenderTarget)(THIS_ IDirect3DSurface8* pRenderTarget, IDirect3DSurface8* pZRenderTarget);
	STDMETHOD(GetRenderTarget)(THIS_ IDirect3DSurface8** ppRenderTarget);
	STDMETHOD(GetDepthStencilSurface)(THIS_ IDirect3DSurface8** ppZStencilSurface);
	STDMETHOD(BeginScene)(THIS);
	STDMETHOD(EndScene)(THIS);
	STDMETHOD(Clear)(THIS_ DWORD Count, CONST D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil);
	STDMETHOD(SetTransform)(THIS_ D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* pMatrix);
	STDMETHOD(GetTransform)(THIS_ D3DTRANSFORMSTATETYPE State, D3DMATRIX* pMatrix);
	STDMETHOD(MultiplyTransform)(THIS_ D3DTRANSFORMSTATETYPE, CONST D3DMATRIX*);
	STDMETHOD(SetViewport)(THIS_ CONST D3DVIEWPORT8* pViewport);
	STDMETHOD(GetViewport)(THIS_ D3DVIEWPORT8* pViewport);
	STDMETHOD(SetMaterial)(THIS_ CONST D3DMATERIAL8* pMaterial);
	STDMETHOD(GetMaterial)(THIS_ D3DMATERIAL8* pMaterial);
	STDMETHOD(SetLight)(THIS_ DWORD Index, CONST D3DLIGHT8*);
	STDMETHOD(GetLight)(THIS_ DWORD Index, D3DLIGHT8*);
	STDMETHOD(LightEnable)(THIS_ DWORD Index, BOOL Enable);
	STDMETHOD(GetLightEnable)(THIS_ DWORD Index, BOOL* pEnable);
	STDMETHOD(SetClipPlane)(THIS_ DWORD Index, CONST float* pPlane);
	STDMETHOD(GetClipPlane)(THIS_ DWORD Index, float* pPlane);
	STDMETHOD(SetRenderState)(THIS_ D3DRENDERSTATETYPE State, DWORD Value);
	STDMETHOD(GetRenderState)(THIS_ D3DRENDERSTATETYPE State, DWORD* pValue);
	STDMETHOD(BeginStateBlock)(THIS);
	STDMETHOD(EndStateBlock)(THIS_ DWORD* pToken);
	STDMETHOD(ApplyStateBlock)(THIS_ DWORD Token);
	STDMETHOD(CaptureStateBlock)(THIS_ DWORD Token);
	STDMETHOD(DeleteStateBlock)(THIS_ DWORD Token);
	STDMETHOD(CreateStateBlock)(THIS_ D3DSTATEBLOCKTYPE Type, DWORD* pToken);
	STDMETHOD(SetClipStatus)(THIS_ CONST D3DCLIPSTATUS8* pClipStatus);
	STDMETHOD(GetClipStatus)(THIS_ D3DCLIPSTATUS8* pClipStatus);
	STDMETHOD(GetTexture)(THIS_ DWORD Stage, IDirect3DBaseTexture8** ppTexture);
	STDMETHOD(SetTexture)(THIS_ DWORD Stage, IDirect3DBaseTexture8* pTexture);
	STDMETHOD(GetTextureStageState)(THIS_ DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD* pValue);
	STDMETHOD(SetTextureStageState)(THIS_ DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value);
	STDMETHOD(ValidateDevice)(THIS_ DWORD* pNumPasses);
	STDMETHOD(GetInfo)(THIS_ DWORD DevInfoID, void* pDevInfoStruct, DWORD DevInfoStructSize);
	STDMETHOD(SetPaletteEntries)(THIS_ UINT PaletteNumber, CONST PALETTEENTRY* pEntries);
	STDMETHOD(GetPaletteEntries)(THIS_ UINT PaletteNumber, PALETTEENTRY* pEntries);
	STDMETHOD(SetCurrentTexturePalette)(THIS_ UINT PaletteNumber);
	STDMETHOD(GetCurrentTexturePalette)(THIS_ UINT *PaletteNumber);
	STDMETHOD(DrawPrimitive)(THIS_ D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount);
	STDMETHOD(DrawIndexedPrimitive)(THIS_ D3DPRIMITIVETYPE, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount);
	STDMETHOD(DrawPrimitiveUP)(THIS_ D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride);
	STDMETHOD(DrawIndexedPrimitiveUP)(THIS_ D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT PrimitiveCount, CONST void* pIndexData, D3DFORMAT IndexDataFormat, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride);
	STDMETHOD(ProcessVertices)(THIS_ UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer8* pDestBuffer, DWORD Flags);
	STDMETHOD(CreateVertexShader)(THIS_ CONST DWORD* pDeclaration, CONST DWORD* pFunction, DWORD* ppShader, DWORD Usage);
	STDMETHOD(SetVertexShader)(THIS_ DWORD pShader);
	STDMETHOD(GetVertexShader)(THIS_ DWORD* ppShader);
	STDMETHOD(DeleteVertexShader)(THIS_ DWORD ppShader);
	STDMETHOD(SetVertexShaderConstant)(THIS_ UINT StartRegister, CONST float* pConstantData, UINT Vector4fCount);
	STDMETHOD(GetVertexShaderConstant)(THIS_ UINT StartRegister, float* pConstantData, UINT Vector4fCount);
	STDMETHOD(GetVertexShaderDeclaration)(THIS_ DWORD Handle, void* pData, DWORD* pSizeOfData);
	STDMETHOD(GetVertexShaderFunction)(THIS_ DWORD Handle, void* pData, DWORD* pSizeOfData);
	STDMETHOD(SetStreamSource)(THIS_ UINT StreamNumber, IDirect3DVertexBuffer8* pStreamData, UINT Stride);
	STDMETHOD(GetStreamSource)(THIS_ UINT StreamNumber, IDirect3DVertexBuffer8** ppStreamData, UINT* pStride);
	STDMETHOD(SetIndices)(THIS_ IDirect3DIndexBuffer8* pIndexData);
	STDMETHOD(GetIndices)(THIS_ IDirect3DIndexBuffer8** ppIndexData);
	STDMETHOD(CreatePixelShader)(THIS_ CONST DWORD* pFunction, DWORD* ppShader);
	STDMETHOD(SetPixelShader)(THIS_ DWORD pShader);
	STDMETHOD(GetPixelShader)(THIS_ DWORD* ppShader);
	STDMETHOD(DeletePixelShader)(THIS_ DWORD Handle);
	STDMETHOD(SetPixelShaderConstant)(THIS_ UINT StartRegister, CONST float* pConstantData, UINT Vector4fCount);
	STDMETHOD(GetPixelShaderConstant)(THIS_ UINT StartRegister, float* pConstantData, UINT Vector4fCount);
	STDMETHOD(GetPixelShaderFunction)(THIS_ DWORD Handle, void* pData, DWORD* pSizeOfData);
	STDMETHOD(DrawRectPatch)(THIS_ UINT Handle, CONST float* pNumSegs, CONST D3DRECTPATCH_INFO* pRectPatchInfo);
	STDMETHOD(DrawTriPatch)(THIS_ UINT Handle, CONST float* pNumSegs, CONST D3DTRIPATCH_INFO* pTriPatchInfo);
	STDMETHOD(DeletePatch)(THIS_ UINT Handle);

	myIDirect3DDevice8(myIDirect3D8 *d3d8, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice9* pOriginal);
	virtual ~myIDirect3DDevice8(void);


	IDirect3DDevice9 *m_pIDirect3DDevice9;

private:
	myIDirect3D8 *m_d3d8;

};
