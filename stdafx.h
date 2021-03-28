// stdafx.h 
#pragma once


#define WIN32_LEAN_AND_MEAN		
#include <windows.h>

#undef DIRECT3D_VERSION
#include "d3d9.h"
#undef D3D_SDK_VERSION
#undef DIRECT3D_VERSION
#define DIRECT3D_VERSION         0x0800

// NB modified dx8 headers to avoid redeclaring shared structs etc
#include "d3d8.h"
#include "myIDirect3D8.h"
#include "myIDirect3DDevice8.h"
