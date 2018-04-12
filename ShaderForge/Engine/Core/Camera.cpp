#include "pch.h"
#include "Camera.h"

using namespace DirectX;
using namespace MarcusEngine::Camera;

/// Обновление экрана камеры. 
void CameraPerspective::UpdateViewport(float width, float height) {
	float aspectRatio = width / height;

	float fovAngleY = 70.0f * XM_PI / 180.0f;
	if (aspectRatio < 1.0f)
	{
		fovAngleY /= aspectRatio;
	}

	XMMATRIX perspectiveMatrix = XMMatrixPerspectiveFovRH(
		fovAngleY,
		aspectRatio,
		0.01f,
		100.0f
	);

	XMFLOAT4X4 orientation =
		XMFLOAT4X4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

	XMMATRIX orientationMatrix = XMLoadFloat4x4(&orientation);
	m_projection_matrix = perspectiveMatrix * orientationMatrix;
}


void CameraOrthographic::UpdateViewport(float width, float height) {
	float w = 0.0f;
	float h = 0.0f;

	float aspectRatio = width / height;
	if (aspectRatio < 1.0f) {
		w = 5.0;
		h = w / aspectRatio;
	}
	else {
		h = 5.0;
		w = h * aspectRatio;
	}

	XMMATRIX orthographic = XMMatrixOrthographicRH(w, h, 0.1, 50);

	XMFLOAT4X4 orientation =
		XMFLOAT4X4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

	XMMATRIX orientationMatrix = XMLoadFloat4x4(&orientation);
	m_projection_matrix = orthographic * orientationMatrix;
}