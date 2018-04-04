#include "pch.h"
#include "Core.h"

using namespace MarcusEngine::Core;

IGameObject::IGameObject() {
	m_position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_size = XMFLOAT3(1.0f, 1.0f, 1.0f);
}

XMMATRIX IGameObject::WorldMatrix() {
	// 
	XMMATRIX world = XMMatrixIdentity();

	world *= XMMatrixScaling(m_size.x, m_size.y, m_size.z); // Масштаб
	world *= XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z);// Тут будет поворот
	world *= XMMatrixTranslation(m_position.x, m_position.y, m_position.z);

	return world;
}

XMMATRIX IGameObject::TransformMatrix() {
	XMMATRIX transform = XMMatrixIdentity();

	transform *= XMMatrixScaling(m_size.x, m_size.y, m_size.z); // Масштаб
	transform *= XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z);// Тут будет поворот

	return transform;
}

void IGameObject::Translate(XMFLOAT3 position) {
	m_position.x += position.x;
	m_position.y += position.y;
	m_position.z += position.z;
}

void IGameObject::Rotate(XMFLOAT3 rotation) {
	m_rotation.x += rotation.x;
	m_rotation.y += rotation.y;
	m_rotation.z += rotation.z;
}
void IGameObject::Scale(XMFLOAT3 scale) {
	m_size.x *= scale.x;
	m_size.y *= scale.y;
	m_size.z *= scale.z;
}