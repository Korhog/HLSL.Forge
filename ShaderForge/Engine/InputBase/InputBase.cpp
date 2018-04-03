#include "pch.h"
#include "InputBase.h"

using namespace Microsoft::WRL::Wrappers;
using namespace MarcusEngine::Input;
using namespace ABI::Windows::Foundation::Collections;

// Singleton 
std::shared_ptr<InputBase> InputBase::_instance = std::shared_ptr<InputBase>(nullptr);

std::shared_ptr<InputBase> InputBase::Current() {
	if (_instance == nullptr) {
		_instance = std::shared_ptr<InputBase>(new InputBase());
	}
	return _instance;
}

void InputBase::Update() {

	Microsoft::WRL::ComPtr<IVectorView<ABI::Windows::Gaming::Input::Gamepad*>> gamepads;
	HRESULT hr = m_gamepadStatics->get_Gamepads(&gamepads);

	unsigned gamepadCount;
	hr = gamepads->get_Size(&gamepadCount);
	
	if (hr == S_OK) {
		Microsoft::WRL::ComPtr<IGamepad> gamepad;
		for (UINT32 i = 0; i < gamepadCount; i++)
		{
			if (gamepads->GetAt(i, &gamepad) == S_OK) {
				// Читаем состояние пада.

				if (gamepad->GetCurrentReading(&m_gamepadReading) == S_OK) {

				}
			}
		}
	}
}

InputBase::InputBase() {
	HRESULT hr = RoInitialize(RO_INIT_MULTITHREADED);
	hr = RoGetActivationFactory(
		HStringReference(L"Windows.Gaming.Input.Gamepad").Get(),
		__uuidof(IGamepadStatics),
		&m_gamepadStatics
	);
}

bool InputBase::ButtonAPressed() {
	if (m_gamepad_a) {
		return m_gamepad_a;
	}
	return false;
}

