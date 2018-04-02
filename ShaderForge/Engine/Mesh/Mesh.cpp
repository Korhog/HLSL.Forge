#include "pch.h"
#include "Mesh.h"
#include "MEVertext.h"
#include <Unknwn.h>

using namespace MarcusEngine::Mesh;

void Box::CreateBuffers(ID3D11Device1 *device) {


#pragma region VertexBuffer
	static const Vertex3D cubeVertices[] =
	{
		// Передняя грань
		{ XMFLOAT3( 0.5f,  0.5f,  0.5f), XMFLOAT3( 0.0f,  0.0f,  1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(-0.5f,  0.5f,  0.5f), XMFLOAT3( 0.0f,  0.0f,  1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(-0.5f, -0.5f,  0.5f), XMFLOAT3( 0.0f,  0.0f,  1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3( 0.5f, -0.5f,  0.5f), XMFLOAT3( 0.0f,  0.0f,  1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) },
		// Задняя грань
		{ XMFLOAT3( 0.5f,  0.5f, -0.5f), XMFLOAT3( 0.0f,  0.0f, -1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f) },
		{ XMFLOAT3(-0.5f,  0.5f, -0.5f), XMFLOAT3( 0.0f,  0.0f, -1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f) },
		{ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3( 0.0f,  0.0f, -1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f) },
		{ XMFLOAT3( 0.5f, -0.5f, -0.5f), XMFLOAT3( 0.0f,  0.0f, -1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f) },

		// Нижняя грань
		{ XMFLOAT3( 0.5f, -0.5f, -0.5f), XMFLOAT3( 0.0f, -1.0f,  0.0f), XMFLOAT3(1.0f, 0.0f, 0.0f) },
		{ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3( 0.0f, -1.0f,  0.0f), XMFLOAT3(1.0f, 0.0f, 0.0f) },
		{ XMFLOAT3(-0.5f, -0.5f,  0.5f), XMFLOAT3( 0.0f, -1.0f,  0.0f), XMFLOAT3(1.0f, 0.0f, 0.0f) },
		{ XMFLOAT3( 0.5f, -0.5f,  0.5f), XMFLOAT3( 0.0f, -1.0f,  0.0f), XMFLOAT3(1.0f, 0.0f, 0.0f) },
		// Верхняя грань
		{ XMFLOAT3( 0.5f,  0.5f, -0.5f), XMFLOAT3( 0.0f,  1.0f,  0.0f), XMFLOAT3(1.0f, 1.0f, 0.0f) },
		{ XMFLOAT3(-0.5f,  0.5f, -0.5f), XMFLOAT3( 0.0f,  1.0f,  0.0f), XMFLOAT3(1.0f, 1.0f, 0.0f) },
		{ XMFLOAT3(-0.5f,  0.5f,  0.5f), XMFLOAT3( 0.0f,  1.0f,  0.0f), XMFLOAT3(1.0f, 1.0f, 0.0f) },
		{ XMFLOAT3( 0.5f,  0.5f,  0.5f), XMFLOAT3( 0.0f,  1.0f,  0.0f), XMFLOAT3(1.0f, 1.0f, 0.0f) },
		// левая грань
		{ XMFLOAT3(-0.5f,  0.5f, -0.5f), XMFLOAT3(-1.0f,  0.0f,  0.0f), XMFLOAT3(1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(-0.5f,  0.5f,  0.5f), XMFLOAT3(-1.0f,  0.0f,  0.0f), XMFLOAT3(1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(-0.5f, -0.5f,  0.5f), XMFLOAT3(-1.0f,  0.0f,  0.0f), XMFLOAT3(1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3(-1.0f,  0.0f,  0.0f), XMFLOAT3(1.0f, 0.0f, 1.0f) },
		// Верхняя грань
		{ XMFLOAT3( 0.5f,  0.5f, -0.5f), XMFLOAT3( 1.0f,  0.0f,  0.0f), XMFLOAT3(0.0f, 1.0f, 1.0f) },
		{ XMFLOAT3( 0.5f,  0.5f,  0.5f), XMFLOAT3( 1.0f,  0.0f,  0.0f), XMFLOAT3(0.0f, 1.0f, 1.0f) },
		{ XMFLOAT3( 0.5f, -0.5f,  0.5f), XMFLOAT3( 1.0f,  0.0f,  0.0f), XMFLOAT3(0.0f, 1.0f, 1.0f) },
		{ XMFLOAT3( 0.5f, -0.5f, -0.5f), XMFLOAT3( 1.0f,  0.0f,  0.0f), XMFLOAT3(0.0f, 1.0f, 1.0f) },
	};

	D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
	
	vertexBufferData.pSysMem = cubeVertices;
	vertexBufferData.SysMemPitch = 0;
	vertexBufferData.SysMemSlicePitch = 0;
	
	CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(cubeVertices), D3D11_BIND_VERTEX_BUFFER);
	
	HRESULT hr = device->CreateBuffer(
		&vertexBufferDesc,
		&vertexBufferData,
		&m_vertexBuffer
	);	
#pragma endregion

	static const unsigned short cubeIndices[] =
	{
		0,  2,  1, // +z
		0,  3,  2,
		4,  5,  6, // -z 
		4,  6,  7,
		8,  9, 10, // -y 
		8, 10, 11,
		12, 14, 13, // -y 
		12, 15, 14,
		16, 17, 18, // -x
		16, 18, 19,
		20, 22, 21, // -x
		20, 23, 22,
	};

	m_indexCount = ARRAYSIZE(cubeIndices);

	D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
	indexBufferData.pSysMem = cubeIndices;
	indexBufferData.SysMemPitch = 0;
	indexBufferData.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC indexBufferDesc(sizeof(cubeIndices), D3D11_BIND_INDEX_BUFFER);
	
	hr = device->CreateBuffer(
		&indexBufferDesc,
		&indexBufferData,
		&m_indexBuffer
	);
}