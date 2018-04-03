#pragma once
#include "pch.h"
#include <functional>
#include <InputBase.h>

namespace MarcusEngine {
	/// Сознание
	namespace Mind {
		class Behavour {
		protected:
			std::function<void(void)> func;
		public:
			void Execute() {
				if(func) func();
			};

			HRESULT Compile() {	
				auto input = Input::InputBase::Current();
				auto f = [=]() { return input->Gamepad.RightTrigger; };	

				func = [=]() {					
					double d = f();
				};

				return S_OK;
			}
		};
	}
}