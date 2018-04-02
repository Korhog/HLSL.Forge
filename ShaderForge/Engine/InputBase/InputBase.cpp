#include "pch.h"
#include "InputBase.h"

using namespace Microsoft::WRL::Wrappers;
using namespace MarcusEngine::Input;
using namespace ABI::Windows::Foundation::Collections;

void InputBase::Update() {
	Microsoft::WRL::ComPtr<IGamepadStatics> gamepadStatics;
	HRESULT hr = RoGetActivationFactory(
		HStringReference(L"Windows.Gaming.Input.Gamepad").Get(), 
		__uuidof(IGamepadStatics), 
		&gamepadStatics
	);

	Microsoft::WRL::ComPtr<IVectorView<Gamepad*>> gamepads;
	hr = gamepadStatics->get_Gamepads(&gamepads);

	unsigned gamepadCount;
	hr = gamepads->get_Size(&gamepadCount);

	for (UINT32 i = 0; i < gamepadCount; i++)
	{
		Microsoft::WRL::ComPtr<IGamepad> gamepad;
		hr = gamepads->GetAt(i, &gamepad);

		GamepadReading gamepadReading;
		hr = gamepad->GetCurrentReading(&gamepadReading);
	}
}

bool InputBase::ButtonAPressed() {
	if (!m_connected)
		return false;

	return (m_state.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0;
}

