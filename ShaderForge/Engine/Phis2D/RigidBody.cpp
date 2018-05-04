#include "pch.h"
#include "RigidBody.h"

using namespace MarcusEngine::Core;
using namespace MarcusEngine::Phis2D;

IRigidBody2D::IRigidBody2D(std::shared_ptr<IGameObject> gameObject) {
	Radius = 0.5f;
	Mass = 1.0f;

	m_gravity.x = 0.0f;
	m_gravity.y = -0.8f;

	m_gameObject = gameObject;
}

RigidBody2D::RigidBody2D(std::shared_ptr<IGameObject> gameObject) : IRigidBody2D::IRigidBody2D(gameObject) {

}