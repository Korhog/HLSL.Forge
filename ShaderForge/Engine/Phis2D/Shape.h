#pragma once

#include "pch.h"
#include "Math2D.h"

namespace MarcusEngine {
	namespace Math2D {
		// ������
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
