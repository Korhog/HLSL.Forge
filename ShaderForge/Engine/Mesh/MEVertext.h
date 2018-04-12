#pragma once

#include <DirectXMath.h>

using namespace DirectX;

struct Vertex3D {
	XMFLOAT3 pos;
	XMFLOAT3 normal;
	XMFLOAT3 color;
	XMFLOAT2 uv;
};

struct Vertex2D {
	XMFLOAT3 pos;
	XMFLOAT3 normal;
	XMFLOAT3 color;
	XMFLOAT2 uv;
};

