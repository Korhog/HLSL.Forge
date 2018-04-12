#include "pch.h"
#include "Mesh.h"
#include "MEVertext.h"
#include <Unknwn.h>
#include <vector>

using namespace DirectX;
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

void Sphere::CreateBuffers(ID3D11Device1 *device) {

	const double M_PI = 3.14;
	float radius = 0.5f;
	//Vertices

	std::vector<Vertex3D> vertices;

	Vertex3D topVertex{ { 0.0f,  radius, 0.0f },{ 0.0f,  1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
	Vertex3D bottomVertex{ { 0.0f, -radius, 0.0f },{ 0.0f, -1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f } };

	vertices.push_back(topVertex);

	int stackCount = 6;
	int sliceCount = 6;

	float phiStep = XM_PI / (float)stackCount;
	float thetaStep = 2.0f * XM_PI / (float)sliceCount;


	for (UINT stack = 1; stack < stackCount; stack++)
	{
		float phi = (float)stack * phiStep;
		for (UINT slice = 0; slice < sliceCount + 1; slice++)
		{
			float theta = (float)slice * thetaStep;
			Vertex3D vertex;

			vertex.pos = { 
				radius * sinf(phi) * cosf(theta),				
				radius * sinf(phi) * sinf(theta),
				radius * cosf(phi),
			};


			//vertex.textureCoord = { theta / DirectX::XM_2PI, phi / (float)M_PI };

			DirectX::XMStoreFloat3(&vertex.normal, DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&vertex.pos)));
			vertices.push_back(vertex);
		}
	}
	vertices.push_back(bottomVertex);

	D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };

	vertexBufferData.pSysMem = vertices.data();
	vertexBufferData.SysMemPitch = 0;
	vertexBufferData.SysMemSlicePitch = 0;

	CD3D11_BUFFER_DESC vertexBufferDesc(
		sizeof(Vertex3D) * vertices.size(),
		D3D11_BIND_VERTEX_BUFFER
	);

	HRESULT hr = device->CreateBuffer(
		&vertexBufferDesc,
		&vertexBufferData,
		&m_vertexBuffer
	);

	//Indices.
	//Top.
	std::vector<UINT> indices;
	for (UINT slice = 0; slice < sliceCount + 1; slice++)
	{
		indices.push_back(0);
		indices.push_back(slice + 1);
		indices.push_back(slice);		
	}
	
	//Middle.
	UINT baseIndex = 1;
	UINT ringVertexCount = sliceCount + 1;
	for (UINT stack = 0; stack < stackCount - 2; stack++)
	{
		for (UINT slice = 0; slice < sliceCount; slice++)
		{			
			indices.push_back(baseIndex + stack * ringVertexCount + slice);
			indices.push_back(baseIndex + stack * ringVertexCount + slice + 1);
			indices.push_back(baseIndex + (stack + 1) * ringVertexCount + slice);
			indices.push_back(baseIndex + (stack + 1) * ringVertexCount + slice);
			indices.push_back(baseIndex + stack * ringVertexCount + slice + 1);
			indices.push_back(baseIndex + (stack + 1) * ringVertexCount + slice + 1);	
		}
	}
	
	//Bottom.
	UINT southPoleIndex = (UINT)vertices.size() - 1;
	baseIndex = southPoleIndex - ringVertexCount;

	for (UINT slice = 0; slice < sliceCount; slice++)
	{
		indices.push_back(southPoleIndex);
		indices.push_back(baseIndex + slice);
		indices.push_back(baseIndex + slice + 1);
	}
	
	m_indexCount = indices.size();

	D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
	indexBufferData.pSysMem = indices.data();
	indexBufferData.SysMemPitch = 0;
	indexBufferData.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC indexBufferDesc(sizeof(UINT) * indices.size(), D3D11_BIND_INDEX_BUFFER);

	hr = device->CreateBuffer(
		&indexBufferDesc,
		&indexBufferData,
		&m_indexBuffer
	);
}

void Sprite::CreateBuffers(ID3D11Device1 *device) {
	float width = 0.5f;
	float height = 0.5f;
	
	static const Vertex3D cubeVertices[] =
	{
		// Спрайт
		{ XMFLOAT3( width,  height, 0.0f), XMFLOAT3(0.0f,  0.0f,  1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(-width,  height, 0.0f), XMFLOAT3(0.0f,  0.0f,  1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(-width, -height, 0.0f), XMFLOAT3(0.0f,  0.0f,  1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3( width, -height, 0.0f), XMFLOAT3(0.0f,  0.0f,  1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) }
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

	static const unsigned short cubeIndices[] =	{0, 2, 1, 0, 3, 2};

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