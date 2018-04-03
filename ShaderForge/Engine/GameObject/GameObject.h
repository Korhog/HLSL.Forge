#pragma once
#include "pch.h"

using namespace DirectX;

namespace MarcusEngine {
	// Base class game object
	class GameObject : public Core::IGameObject {
	public:
		GameObject();
		virtual void Load(ID3D11Device1 *device);
	};
}
