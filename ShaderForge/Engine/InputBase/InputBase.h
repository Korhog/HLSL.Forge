#pragma once

#include "pch.h"
#include <windows.gaming.input.h>

using namespace ABI::Windows::Gaming::Input;

namespace MarcusEngine {
	namespace Input {
		class InputBase {
		private:
			Microsoft::WRL::ComPtr<IGamepadStatics> m_gamepadStatics;
			bool m_connected;
			XINPUT_STATE m_state;
			GamepadReading m_gamepadReading;
			bool m_gamepad_a;

			static std::shared_ptr<InputBase> _instance;
		public:
			static std::shared_ptr<InputBase> Current();
			
			void Update();
			bool ButtonAPressed();

			__declspec(property(get = GetGamepadState)) GamepadReading Gamepad;
			GamepadReading GetGamepadState() {
				return m_gamepadReading;
			};
		protected:
			InputBase();
		};

	}
}
