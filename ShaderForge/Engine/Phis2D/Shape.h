#pragma once

#include "pch.h"
#include "Math2D.h"

namespace MarcusEngine {
	namespace Math2D {
		// Фигура
		class IShape abstract {
		public:
			AABB m_aabb;
		protected:
			//virtual void UpdateAABB() abstract;
		};

		class CircleShape : public IShape {

		};
	}
}
