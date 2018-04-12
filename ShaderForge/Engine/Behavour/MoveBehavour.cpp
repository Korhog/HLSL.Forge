#include "pch.h"
#include <math.h>
#include "MoveBehavour.h"

using namespace MarcusEngine::Core;
using namespace MarcusEngine::Mind;

MoveBehavour::MoveBehavour() {
	m_input = MarcusEngine::Input::InputBase::Current();
}

void MoveBehavour::Execute() {
	if (!m_gameObject)
		return;

	double r = m_input->Gamepad.RightThumbstickX;
	if (abs(r) > 0.15) {
		m_gameObject->Rotate(DirectX::XMFLOAT3(0.0f, 0.0f, -(float)r / 50.0f));
	}

	double f = m_input->Gamepad.LeftThumbstickY;
	if (abs(f) > 0.15) {
		auto dir = XMLoadFloat3(new XMFLOAT3(0.0f, 0.0f, 1.0f));		
		dir = XMVector3Rotate(dir, XMQuaternionRotationRollPitchYaw(0.0f, m_gameObject->Rotation.y, 0.0f));
		dir *= (f / 50.0f);

		XMFLOAT3 trans;

		XMStoreFloat3(&trans, dir);

		m_gameObject->Translate(trans);
	}	
}