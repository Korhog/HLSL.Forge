#include "pch.h"
#include "Phis2D.h"

using namespace DirectX;
using namespace MarcusEngine;
using namespace MarcusEngine::Phis2D;

void World2D::Update() {	
	for each (std::shared_ptr<IRigidBody2D> body in m_bodies) {
		body->Update();
		if (pair) {
			auto posA = m_pair.A->GameObject->Position;
			auto posB = m_pair.B->GameObject->Position;

			Vector2 a;
			a.x = posA.x;
			a.y = posA.y;			
			
			Vector2 b;
			b.x = posB.x;
			b.y = posB.y;
			
			Vector2 v;
			v.x = 0.0f;
			v.y = 0.0f;

			if (Vector2::Lenght(a - b) < 1.0f) {
				m_pair.A->Velocity = v;
				m_pair.B->Velocity = v;
			}
			
		}
	}	
}


std::shared_ptr<IRigidBody2D> World2D::Attach(std::shared_ptr<IGameObject> gameObject) {
	auto body = std::shared_ptr<IRigidBody2D>(new RigidBody2D(gameObject));
	m_bodies.push_back(body);

	if (m_bodies.size() == 1) {
		m_pair.A = body;
	}
	else {
		m_pair.B = body;
		pair = true;
	}

	return body;
}
