#pragma once
#include "pch.h"
#include <Mesh.h>

using namespace DirectX;

namespace MarcusEngine {
	// Base class game object
	class GameObject : public IUnknown {
	public:
		GameObject();
		XMMATRIX WorldMatrix();	

		virtual void Load(ID3D11Device1 *device);

		__declspec(property(get = GetPosition, put = SetPosition)) XMFLOAT3 Position;
		__declspec(property(get = GetRotation, put = SetRotation)) XMFLOAT3 Rotation;
		__declspec(property(get = GetScale, put = SetScale)) XMFLOAT3 Scale;
	private:
		XMFLOAT3 m_position;
		XMFLOAT3 m_rotation;
		XMFLOAT3 m_scale;

	protected:
		// Операции
		virtual void Translate();
		virtual void Rotate();
		virtual void SetScale();

#pragma region Свойства
		// Позиция
		XMFLOAT3 GetPosition() { return m_position; }
		void SetPosition(XMFLOAT3 position) { m_position = position; }
		// Поворот
		XMFLOAT3 GetRotation() { return m_rotation; }
		void SetRotation(XMFLOAT3 rotation) { m_rotation = rotation; }
		// Масштаб
		XMFLOAT3 GetScale() { return m_scale; }
		void SetScale(XMFLOAT3 scale) { m_scale = scale; }
#pragma endregion
	};
}
