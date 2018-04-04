#pragma once

#include "pch.h"
#include "Behavour.h"

namespace MarcusEngine {
	/// Сознание
	namespace Mind {
		class MoveBehavour : public Behavour {
		protected:
			std::shared_ptr<MarcusEngine::Input::InputBase> m_input;
		public:
			MoveBehavour();
			void Execute() override;
		};
	}
}
