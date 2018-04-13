#include "pch.h"
#include "Math2D.h"

using namespace MarcusEngine::Math2D;

Vector2 Vector2::Normalize() {
	Vector2 result;

	float x = this->x;
	float y = this->y;

	float v = sqrtf(x * x + y * y);

	result.x = x / v;
	result.y = y / v;

	return result;
}

float Vector2::Dot(Vector2 a, Vector2 b) {
	return 0.0f;
}