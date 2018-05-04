#pragma once

#include "pch.h"
#include "Math2D.h"
#include "RigidBody.h"

using namespace std;

namespace MarcusEngine {
	namespace PhisXD {
		struct ICollide {
			shared_ptr<Phis2D::IRigidBody2D> A;
			shared_ptr<Phis2D::IRigidBody2D> B;
			Vector2 normal;    // Нормаль касания
			float penetration; // Проникновение
		};		
		
		// Circle vs Circle
		struct CollideCC : public ICollide {

		};		
		
		// Circle vs Rect
		struct CollideCR : public ICollide {

		};		
		
		// Rect vs Rect
		struct CollideRR : public ICollide {

		};

		class IWorld abstract {
		public:
			virtual void Update() abstract;			
			virtual shared_ptr<Phis2D::IRigidBody2D> Attach(shared_ptr<IGameObject> gameObject, IShape* shape = nullptr) abstract;
		};
	}

	using namespace PhisXD;

	namespace Phis2D {
		/// 2D world
		class World2D : public IWorld {
		protected:	
			vector<shared_ptr<IRigidBody2D>> m_bodies;
			vector<ICollide> m_pairs;
		public:
			virtual void Update() override;			
			virtual shared_ptr<IRigidBody2D> Attach(shared_ptr<IGameObject> gameObject, IShape* shape = nullptr) override;
		protected:
			void ResolveCollision(ICollide* collide);

			void ResolveCollisionCC(ICollide *collide);
			void ResolveCollisionCR(ICollide *collide);
			void ResolveCollisionRR(ICollide *collide);

			void ResolveImpulse(ICollide* collide);
			void PositionalCorrection(ICollide* collide);

		};
	}
}