#pragma once
#include "pch.h"
#include <functional>
#include <InputBase.h>
#include <Core.h>
#include <Time.h>

namespace MarcusEngine {
	/// Сознание
	namespace Mind {
		class Behavour {
		protected:
			std::shared_ptr<Core::IGameObject> m_gameObject;
			std::function<void(void)> func;
		public:
			void SetGameObject(Core::IGameObject * gameObject);

			virtual void Execute() {
				if(func) func();
			};

			virtual HRESULT Compile() {	
				return S_OK;
			}
		};
	}
}