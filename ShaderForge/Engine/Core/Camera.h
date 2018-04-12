#pragma once
#include "pch.h"

using namespace DirectX;

namespace MarcusEngine {
	namespace Camera {
		class ICamera abstract {
		protected:
			XMMATRIX m_projection_matrix;
			XMMATRIX m_viev_matrix;			
		public:
			virtual void UpdateViewport(float width, float height) abstract;
			
			__declspec(property(get = GetProjectionMatrix)) XMMATRIX Projection;
			XMMATRIX GetProjectionMatrix() { return m_projection_matrix; }
		};

		class CameraPerspective : public ICamera {
			virtual void UpdateViewport(float width, float height) override;
		};

		class CameraOrthographic : public ICamera {
			virtual void UpdateViewport(float width, float height) override;
		};
	}
}