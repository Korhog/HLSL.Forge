#include "pch.h"
#include "Game.h"
#include <GameObject.h>
#include <MEVertext.h>


using namespace MarcusEngine;
using namespace MarcusEngine::Phis2D;
using namespace MarcusEngine::Phis2D;

IGame::IGame() {
	m_world = std::unique_ptr<World2D>(new World2D());
}

void Game2D::Update() {
	m_world->Update();
}

void Game2D::Render(ID3D11DeviceContext1* context) {
	for each (std::shared_ptr<GameObject> gameObject in m_game_objects)
	{
		auto render = gameObject->Render();

		// Each vertex is one instance of the VertexPositionColor struct. 
		UINT stride = sizeof(Vertex3D);
		UINT offset = 0;

		auto vertexBuffer = render->GetVertexBuffer();
		context->IASetVertexBuffers(
			0,
			1,
			&vertexBuffer,
			&stride,
			&offset
		);

		context->IASetIndexBuffer(
			render->GetIndexBuffer(),
			DXGI_FORMAT_R16_UINT, // Each index is one 16-bit unsigned integer (short). 
			0
		);

		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		// Draw the objects. 
		context->DrawIndexed(
			render->GetIndexCount(),
			0,
			0
		);
	}
}

void Game2D::AddGameObject(std::shared_ptr<GameObject> gameObject) {
	m_game_objects.push_back(gameObject);	
}