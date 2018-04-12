#pragma once
#include "pch.h"

using namespace DirectX;

namespace MarcusEngine {
	namespace Phisx {
		struct Vector2 {
			float x;
			float y;
		};

		struct AABB {
			Vector2 min;
			Vector2 max;
		};

		static class PhisxTools {
		public:
			static bool Collide(AABB a, AABB b) {
				if (a.max.x < b.min.x || a.min.x > b.max.x) return false;
				if (a.max.y < b.min.y || a.min.y > b.max.y) return false;
				return true;
			}

			static float Distance(Vector2 a, Vector2 b) {

			}
		};
	}
}