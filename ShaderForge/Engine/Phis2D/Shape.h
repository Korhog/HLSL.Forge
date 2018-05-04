#pragma once

#include "pch.h"
#include "Math2D.h"
#include <d2d1_1.h>

namespace MarcusEngine {
	namespace Math2D {
		// Фигура
		class IShape abstract {
		public:
			AABB m_aabb;
			Vector2 Position;

			virtual void DrawShape(ID2D1DeviceContext* context) abstract;
		protected:
			
			//virtual void UpdateAABB() abstract;
		};

		class RectShape : public IShape {
		public:
			float Radius;
			virtual void DrawShape(ID2D1DeviceContext* context) override {};
		};	

		class CircleShape : public IShape {
		public:
			float Radius;
			virtual void DrawShape(ID2D1DeviceContext* context) override;
		};

		class PolygonShape : public IShape {

		};
	}
}
