#include "pch.h"
#include "Phis2D.h"
#include <typeinfo>

using namespace DirectX;
using namespace MarcusEngine;
using namespace MarcusEngine::Phis2D;

void World2D::Update() {	
	for each (std::shared_ptr<IRigidBody2D> body in m_bodies) {
		body->Update();		
	}

	for each (ICollide collide in m_pairs) {
		ResolveCollision(&collide);
	}
}

void World2D::ResolveCollision(ICollide* collide) {
	if (dynamic_cast<MarcusEngine::Math2D::CircleShape*>(collide->A->Shape)) {
		if (dynamic_cast<MarcusEngine::Math2D::CircleShape*>(collide->B->Shape)) {
			ResolveCollisionCC(collide);
		}

		if (dynamic_cast<MarcusEngine::Math2D::RectShape*>(collide->B->Shape)) {
			ResolveCollisionCR(collide);
		}
	}

	if (dynamic_cast<MarcusEngine::Math2D::RectShape*>(collide->A->Shape)) {
		if (dynamic_cast<MarcusEngine::Math2D::CircleShape*>(collide->B->Shape)) {
			ResolveCollisionCR(collide);
		}

		if (dynamic_cast<MarcusEngine::Math2D::RectShape*>(collide->B->Shape)) {
			ResolveCollisionRR(collide);
		}
	}
}

float Clamp(float min, float max, float v) {
	if (v < min) return min;
	if (v > max) return max;
	return v;
}

void World2D::ResolveCollisionCC(ICollide *collide) {
	//continue;
	IRigidBody2D *A = collide->A.get();
	IRigidBody2D *B = collide->B.get();

	// Вектор от A к B
	Vector2 a = Vector2(
		A->GameObject->Position.x,
		A->GameObject->Position.y
	);

	Vector2 b = Vector2(
		B->GameObject->Position.x,
		B->GameObject->Position.y
	);

	Vector2 v = Vector2(0, 0);

	// Коллизия
	float l = Vector2::Lenght(a - b);
	float r = A->Radius + B->Radius;
	if (l < r) {
		// Если расстояние между окружностями не равно нулю
		if (l != 0)
		{
			// Расстояние - это разность между радиусом и расстоянием
			collide->penetration = r - l;
			collide->normal = (b - a).Normalize();
		}

		// Окружности имеют одинаковое положение
		else
		{
			// Выбираем случайные (но согласованные) значения
			collide->penetration = A->Radius;
			collide->normal = Vector2(1, 0);
		}
		
		ResolveImpulse(collide);
	}
}

void World2D::ResolveCollisionCR(ICollide *collide) {	
	IRigidBody2D *A = collide->A.get();
	IRigidBody2D *B = collide->B.get();
	// Вектор от A к B
	Vector2 pA = Vector2(
		A->GameObject->Position.x,
		A->GameObject->Position.y
	);

	Vector2 pB = Vector2(
		B->GameObject->Position.x,
		B->GameObject->Position.y
	);

	Vector2 n = pB - pA;

	// Ближайшая к центру B точка A
	Vector2 closest = n;

	// Вычисление половины ширины вдоль каждой оси
	float x_extent = B->Radius;
	float y_extent = B->Radius;

	// Ограничиваем точку ребром AABB
	closest.x = Clamp(-x_extent, x_extent, closest.x);
	closest.y = Clamp(-y_extent, y_extent, closest.y);

	bool inside = false;

	// Окружность внутри AABB, поэтому нам нужно ограничить центр окружности
	// до ближайшего ребра
	if (n == closest)
	{
		inside = true;
		// Находим ближайшую ось
		if (abs(n.x) > abs(n.y)) {
			// Отсекаем до ближайшей ширины
			if (closest.x > 0)
				closest.x = x_extent;
			else
				closest.x = -x_extent;
		}
		// ось y короче
		else {
			// Отсекаем до ближайшей ширины
			if (closest.y > 0)
				closest.y = y_extent;
			else
				closest.y = -y_extent;
		}
	}

	collide->normal = n - closest;
	float d = Vector2::Lenght(collide->normal);
	float r = A->Radius;

	// Если радиус меньше, чем расстояние до ближайшей точки и
	// Окружность не находится внутри AABB
	if (d * d > r * r && !inside)
		return;

	// Если окружность была внутри AABB, то нормаль коллизии нужно отобразить
	// в точку снаружи
	if (inside)
	{
		collide->normal = (n * -1).Normalize();
	}
	else
	{
		collide->normal = n.Normalize();
	}

	ResolveImpulse(collide);
}

void World2D::ResolveCollisionRR(ICollide *collide) {	
	IRigidBody2D *A = collide->A.get();
	IRigidBody2D *B = collide->B.get();
	// Вектор от A к B
	Vector2 pA = Vector2(
		A->GameObject->Position.x,
		A->GameObject->Position.y
	);

	Vector2 pB = Vector2(
		B->GameObject->Position.x,
		B->GameObject->Position.y
	);

	Vector2 n = pB - pA;


	float r = A->Radius;
	float a_extent_x = r;
	float a_extent_y = r;

	r = B->Radius;
	float b_extent_x = r;
	float b_extent_y = r;	

	// Вычисление наложения по оси x
	float x_overlap = a_extent_x + b_extent_x - abs(n.x);
	// Проверка SAT по оси x
	bool coll = false;
	if (x_overlap > 0)
	{
		// Вычисление наложения по оси y
		float y_overlap = a_extent_y + b_extent_y - abs(n.y);
		// Проверка SAT по оси y
		if (y_overlap > 0)
		{
			// Определяем, по какой из осей проникновение наименьшее
			if (x_overlap < y_overlap)
			{
				// Указываем в направлении B, зная, что n указывает в направлении от A к B
				if (n.x < 0)
					collide->normal = Vector2(-1, 0);
				else
					collide->normal = Vector2(1, 0);
				
			}
			else
			{
				// Указываем в направлении B, зная, что n указывает в направлении от A к B
				if (n.y < 0)
					collide->normal = Vector2(0, -1);
				else
					collide->normal = Vector2(0, 1);
			
			}

			coll = true;
		}
	}

	if (coll) ResolveImpulse(collide);
}

void World2D::ResolveImpulse(ICollide* collide) {
	IRigidBody2D *A = collide->A.get();
	IRigidBody2D *B = collide->B.get();

	Vector2 rv = B->Velocity - A->Velocity;
	// Скаляр
	float normalVelocity = Vector2::Dot(rv, collide->normal);
	if (normalVelocity > 0.0f)
		return;

	float e = 0.3f; // Пока что абсолютно упругие тела

					// Вычисляем скаляр импульса силы
	float impulseScalar = -(1 + e) * normalVelocity;
	impulseScalar /= A->InvMass + B->InvMass;

	Vector2 impulse = collide->normal * impulseScalar;

	A->Velocity -= impulse * A->InvMass;
	B->Velocity += impulse * B->InvMass;

	PositionalCorrection(collide);
}

void World2D::PositionalCorrection(ICollide * collide) 
{
	IRigidBody2D *A = collide->A.get();
	IRigidBody2D *B = collide->B.get();

	const float percent = 0.2; // обычно от 20% до 80%
	const float slop = 0.03f;  // обычно от 0.01 до 0.1

	Vector2 correction = collide->normal * max(collide->penetration - slop, 0.0f) / (A->InvMass + B->InvMass) * percent;
	
	Vector2 a = correction * A->InvMass * -1;
	Vector2 b = correction * B->InvMass ;
	
	A->GameObject->Translate(XMFLOAT3(a.x, a.y, 0.0f));
	B->GameObject->Translate(XMFLOAT3(b.x, b.y, 0.0f));
}

std::shared_ptr<IRigidBody2D> World2D::Attach(std::shared_ptr<IGameObject> gameObject, IShape* shape) {
	auto body = std::shared_ptr<IRigidBody2D>(new RigidBody2D(gameObject));
	if (shape) {
		body->Shape = shape;
	}
	else {
		auto circle = new CircleShape();
		body->Shape = circle;
	}	
	
	if (m_bodies.size() > 0) {
		// Нужно доабвить пару для коллизий
		for each (std::shared_ptr<IRigidBody2D> b in m_bodies)
		{
			ICollide pair;
			pair.A = body;
			pair.B = b;
			m_pairs.push_back(pair);
		}		
	}

	m_bodies.push_back(body);
	return body;
}
