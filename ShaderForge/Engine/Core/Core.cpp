#include "pch.h"
#include "Core.h"

using namespace MarcusEngine::Core;

IGameObject::IGameObject() {
	m_position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
}

// Переместить
void IGameObject::Translate() {

}

// Повернуть
void IGameObject::Rotate() {

}

// Изменить масштаб
void IGameObject::SetScale() {

}

XMMATRIX IGameObject::WorldMatrix() {
	// 
	XMMATRIX world = XMMatrixIdentity();

	world *= XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z); // Масштаб
	world *= XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z);// Тут будет поворот
	world *= XMMatrixTranslation(m_position.x, m_position.y, m_position.z);

	return world;
}