#pragma once
#include "pch.h"
#include <d2d1_1.h>

using namespace DirectX;

namespace MarcusEngine {
	namespace Camera {
		class ICamera abstract {
		protected:
			XMMATRIX m_projection_matrix;
			XMMATRIX m_viev_matrix;		

			float m_aspectRatio;
			float m_screenWidth;
			float m_screenHeight;
		public:
			virtual D2D1_POINT_2F WorldToScreen(float x, float y) abstract;
			virtual void UpdateViewport(float width, float height) abstract;
			
			__declspec(property(get = GetProjectionMatrix)) XMMATRIX Projection;
			XMMATRIX GetProjectionMatrix() { return m_projection_matrix; }
		};

		class CameraPerspective : public ICamera {
			virtual D2D1_POINT_2F WorldToScreen(float x, float y) override;
			virtual void UpdateViewport(float width, float height) override;
		};

		class CameraOrthographic : public ICamera {
			virtual D2D1_POINT_2F WorldToScreen(float x, float y) override;
			virtual void UpdateViewport(float width, float height) override;
		};
	}
}