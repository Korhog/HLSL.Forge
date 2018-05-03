#pragma once

#include <math.h>

namespace MarcusEngine {
	namespace Math2D {
		const float G = 9.8f;

		struct Vector2 {
			float x;
			float y;

			// operators
			
			void operator+=(const Vector2& v) {
				this->x += v.x;
				this->y += v.y;
			}

			void operator-=(const Vector2& v) {
				this->x -= v.x;
				this->y -= v.y;
			}

			Vector2 operator+(const Vector2& v) {
				Vector2 result;
				result.x = this->x + v.x;
				result.y = this->y + v.y;
				return result;
			}

			Vector2 operator-(const Vector2& v) {
				Vector2 result;
				result.x = this->x - v.x;
				result.y = this->y - v.y;
				return result;
			}

			Vector2 operator/(const float& v) {
				Vector2 result;
				result.x = this->x / v;
				result.y = this->y / v;
				return result;
			}
			Vector2 operator*(const float& v) {
				Vector2 result;
				result.x = this->x * v;
				result.y = this->y * v;
				return result;
			}
			void operator/=(const float& v) {
				this->x /= v;
				this->y /= v;				
			}

			void operator*=(const float& v) {
				this->x * v;
				this->y * v;
			}		
			static float Lenght(Vector2 v) {
				return sqrt(v.x * v.x + v.y * v.y);
			}

			static float Dot(Vector2 n, Vector2 b);
			Vector2 Normalize();
		};

		struct AABB {
			Vector2 min;
			Vector2 max;
		};

		struct Circle {
			Vector2 pos;
			float radius;
		};

		static class Intersect {
		public:
			static bool AABB(AABB a, AABB b) { return true; };
			static bool Circles(Circle a, Circle b) { 
				float r = powf(a.radius + b.radius, 2.0f);
				return r < powf(a.pos.x + b.pos.x, 2.0f) + powf(a.pos.y + b.pos.y, 2.0f);
			};
		};
	}
}
