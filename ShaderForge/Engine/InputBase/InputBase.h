#pragma once

#include "pch.h"
#include <windows.gaming.input.h>

using namespace ABI::Windows::Gaming::Input;

namespace MarcusEngine {
	namespace Input {
		class InputBase {
		private:
			bool m_connected;
			XINPUT_STATE m_state;
		public:
			void Update();

			bool ButtonAPressed();
		};
	}
}
