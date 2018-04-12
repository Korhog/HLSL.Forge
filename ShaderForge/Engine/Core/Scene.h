#pragma once
#include "pch.h"

namespace MarcusEngine {
	namespace Core {
		class ILayer abstract {
		public:
			virtual void Render(ID3D11DeviceContext1* context) abstract;
		};

		class IScene abstract {
		public:
			virtual void Render(ID3D11DeviceContext1* context) abstract;
		};
	}
}
