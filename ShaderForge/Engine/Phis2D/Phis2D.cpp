#include "pch.h"
#include "Phis2D.h"

using namespace DirectX;
using namespace MarcusEngine;
using namespace MarcusEngine::Phis2D;

void World2D::Update() {	
	for each (std::shared_ptr<IRigidBody2D> body in m_bodies) {
		body->Update();		
	}

	for each (Collide collide in m_pairs) {
		ResolveCollision(
			collide.A.get(),
			collide.B.get()
		);
	}
}

void World2D::ResolveCollision(IRigidBody2D* A, IRigidBody2D* B) {
	//continue;
	auto posA = A->GameObject->Position;
	auto posB = B->GameObject->Position;

	Vector2 a;
	a.x = posA.x;
	a.y = posA.y;

	Vector2 b;
	b.x = posB.x;
	b.y = posB.y;

	Vector2 v;
	v.x = 0.0f;
	v.y = 0.0f;

	// Коллизия
	if (Vector2::Lenght(a - b) < A->Radius + B->Radius) {
		Vector2 normal = (b - a).Normalize();
		Vector2 rv = B->Velocity - A->Velocity;

		// Скаляр
		float normalVelocity = Vector2::Dot(rv, normal);
		if (normalVelocity > 0.0f)
			return;

		float e = 1.0f; // Пока что абсолютно упругие тела

		// Вычисляем скаляр импульса силы
		float impulseScalar = -(1 + e) * normalVelocity;
		impulseScalar /= A->InvMass + B->InvMass;

		Vector2 impulse = normal * impulseScalar;

		A->Velocity -= impulse * A->InvMass;
		B->Velocity += impulse * B->InvMass;
	}
}



std::shared_ptr<IRigidBody2D> World2D::Attach(std::shared_ptr<IGameObject> gameObject) {
	auto body = std::shared_ptr<IRigidBody2D>(new RigidBody2D(gameObject));
	
	if (m_bodies.size() > 0) {
		// Нужно доабвить пару для коллизий
		for each (std::shared_ptr<IRigidBody2D> b in m_bodies)
		{
			Collide pair;
			pair.A = body;
			pair.B = b;
			m_pairs.push_back(pair);
		}		
	}

	m_bodies.push_back(body);


	return body;
}
