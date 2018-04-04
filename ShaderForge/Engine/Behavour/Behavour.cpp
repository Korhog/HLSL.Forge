#include "pch.h"
#include "Behavour.h"

using namespace MarcusEngine::Core;
using namespace MarcusEngine::Mind;

void Behavour::SetGameObject(IGameObject *gameObject) {
	m_gameObject = std::shared_ptr<Core::IGameObject>(gameObject);
}

