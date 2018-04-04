#pragma once
#include "pch.h"
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
	protected:
		std::unique_ptr<MarcusEngine::Mesh::Mesh> m_mesh;
	private:
		std::vector<std::shared_ptr<Mind::Behavour>> m_behavours;		
	};
}
