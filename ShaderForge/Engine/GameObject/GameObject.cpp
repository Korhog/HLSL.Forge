#include "pch.h"
#include "GameObject.h"

using namespace DirectX;
using namespace MarcusEngine;

GameObject::GameObject() {
	m_position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
}

void GameObject::Load(ID3D11Device1 *device) {

}

// Переместить
void GameObject::Translate() {

}

// Повернуть
void GameObject::Rotate() {

}

// Изменить масштаб
void GameObject::SetScale() {

}

XMMATRIX GameObject::WorldMatrix() {
	// 
	XMMATRIX world = XMMatrixIdentity();

	world *= XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z); // Масштаб
	world *= XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z);// Тут будет поворот
	world *= XMMatrixTranslation(m_position.x, m_position.y, m_position.z);

	return world;
}

