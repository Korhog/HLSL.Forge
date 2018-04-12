#pragma once

#include "pch.h"
#include "Math2D.h"
#include "RigidBody.h"

using namespace std;

namespace MarcusEngine {
	namespace PhisXD {
		struct Collide {
			shared_ptr<Phis2D::IRigidBody2D> A;
			shared_ptr<Phis2D::IRigidBody2D> B;
		};

		class IWorld abstract {
		public:
			virtual void Update() abstract;
			virtual shared_ptr<Phis2D::IRigidBody2D> Attach(shared_ptr<IGameObject> gameObject) abstract;
		};
	}

	using namespace PhisXD;

	namespace Phis2D {
		/// 2D world
		class World2D : public IWorld {
		protected:	
			bool pair = false;
			Collide m_pair;
			vector<shared_ptr<IRigidBody2D>> m_bodies;
		public:
			virtual void Update() override;
			virtual shared_ptr<IRigidBody2D> Attach(shared_ptr<IGameObject> gameObject) override;;
		};
	}
}