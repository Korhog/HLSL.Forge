#pragma once
#include "pch.h"

namespace MarcusEngine {
	using namespace Math2D;
	using namespace Core;

	namespace Phis2D {
		class IRigidBody2D abstract {
		protected:
			Vector2 m_gravity;
			Vector2 m_velocity;
			std::shared_ptr<Core::IGameObject> m_gameObject;
		public:
			IRigidBody2D() {};
			IRigidBody2D(std::shared_ptr<IGameObject> gameObject);

			void Update() {
				if (m_gameObject) {
					XMFLOAT3 translation = XMFLOAT3(m_velocity.x, m_velocity.y, 0.0f);
					m_gameObject->Translate(translation);

					if (m_gameObject->Position.y < -2.0f || m_gameObject->Position.y > 2.0f) {
						if (m_gameObject->Position.y < -2.0f)
							m_gameObject->Translate(XMFLOAT3(0.0f, -2.0f - m_gameObject->Position.y, 0.0f));
						else
							m_gameObject->Translate(XMFLOAT3(0.0f, 2.0f - m_gameObject->Position.y, 0.0f));

						m_velocity.y = -m_velocity.y;
					};

					if (m_gameObject->Position.x < -3.5f || m_gameObject->Position.x > 3.5f) {
						if (m_gameObject->Position.x < -3.5f)
							m_gameObject->Translate(XMFLOAT3(-3.5f - m_gameObject->Position.x, 0.0f, 0.0f));
						else 
							m_gameObject->Translate(XMFLOAT3( 3.5f - m_gameObject->Position.x, 0.0f, 0.0f));

						m_velocity.x = -m_velocity.x;
					};
				}				
			}
#pragma region Property
			__declspec(property(get = GetVelocity, put = SetVelocity)) Vector2 Velocity;
			// Скорость
			Vector2 GetVelocity() { return m_velocity; }
			void SetVelocity(Vector2 position) { m_velocity = position; }

			__declspec(property(get = GetGameObject)) std::shared_ptr<Core::IGameObject> GameObject;
			std::shared_ptr<Core::IGameObject> GetGameObject() { return m_gameObject; }
#pragma endregion

		};

		class RigidBody2D : public IRigidBody2D {
		public:
			RigidBody2D(std::shared_ptr<IGameObject> gameObject);
		};
	}
}