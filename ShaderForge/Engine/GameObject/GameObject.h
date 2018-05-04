#pragma once
#include "pch.h"
#include <Phis2D.h>
#include <Behavour.h>
#include <vector>

using namespace DirectX;

namespace MarcusEngine {	
	using namespace Mind;
	// Base class game object
	class GameObject : public Core::IGameObject {
	public:		
		GameObject();
		virtual void Load(ID3D11Device1 *device);

		void Update();
		void AddBehavour(std::shared_ptr<Mind::Behavour> behavour);

		MarcusEngine::Mesh::Mesh* Render() { return m_mesh.get(); }

#pragma region Параметры
		// Твердое тело
		std::shared_ptr<Phis2D::IRigidBody2D> GetRigidBody() { return m_rigidBody; }
		void SetRigidBody(std::shared_ptr<Phis2D::IRigidBody2D> body) { m_rigidBody = body; }
		__declspec(property(get = GetRigidBody)) std::shared_ptr<Phis2D::IRigidBody2D> RigidBody2D;
#pragma endregion

	protected:
		std::unique_ptr<MarcusEngine::Mesh::Mesh> m_mesh;
	private:
		std::shared_ptr<Phis2D::IRigidBody2D> m_rigidBody;
		std::vector<std::shared_ptr<Mind::Behavour>> m_behavours;		
	};
}
