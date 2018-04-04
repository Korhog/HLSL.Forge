#include "pch.h"
#include "GameObject.h"

using namespace DirectX;
using namespace MarcusEngine;

GameObject::GameObject() {

}

void GameObject::AddBehavour(std::shared_ptr<Mind::Behavour> behavour) {
	m_behavours.push_back(behavour);
	behavour->SetGameObject(this);
		
}

void GameObject::Update() {
	for each (auto var in m_behavours)
	{
		var->Execute();
	}
}

void GameObject::Load(ID3D11Device1 *device) {
	m_mesh = std::unique_ptr<MarcusEngine::Mesh::Mesh>(new MarcusEngine::Mesh::Box());
	m_mesh->CreateBuffers(device);
}