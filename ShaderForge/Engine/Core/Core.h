#pragma once
#include "pch.h"

using namespace DirectX;

namespace MarcusEngine {
	namespace Core {
		class IGameObject abstract {
		public:
			IGameObject();
			__declspec(property(get = GetPosition, put = SetPosition)) XMFLOAT3 Position;
			__declspec(property(get = GetRotation, put = SetRotation)) XMFLOAT3 Rotation;
			__declspec(property(get = GetSize, put = SetSize)) XMFLOAT3 Size;

			XMMATRIX TransformMatrix();
			XMMATRIX WorldMatrix();

			virtual void Translate(XMFLOAT3 position);
			virtual void Rotate(XMFLOAT3 rotation);
			virtual void Scale(XMFLOAT3 scale);

#pragma region Свойства
			// Позиция
			XMFLOAT3 GetPosition() { return m_position; }
			void SetPosition(XMFLOAT3 position) { m_position = position; }
			// Поворот
			XMFLOAT3 GetRotation() { return m_rotation; }
			void SetRotation(XMFLOAT3 rotation) { m_rotation = rotation; }
			// Масштаб
			XMFLOAT3 GetSize() { return m_size; }
			void SetSize(XMFLOAT3 scale) { m_size = scale; }
#pragma endregion	
		protected:
			XMFLOAT3 m_position;
			XMFLOAT3 m_rotation;
			XMFLOAT3 m_size;		
		};
	}
}
