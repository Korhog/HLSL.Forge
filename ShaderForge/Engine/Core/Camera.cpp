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

D2D1_POINT_2F CameraPerspective::WorldToScreen(float x, float y) {
	D2D1_POINT_2F p;
	p.x = 0.0f;
	p.y = 0.0f;
	return p;
}



void CameraOrthographic::UpdateViewport(float width, float height) {
	m_screenWidth = width;
	m_screenHeight = height;

	float w = 0.0f;
	float h = 0.0f;

	m_aspectRatio = width / height;
	if (m_aspectRatio < 1.0f) {
		w = 5.0;
		h = w / m_aspectRatio;
	}
	else {
		h = 5.0;
		w = h * m_aspectRatio;
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

D2D1_POINT_2F CameraOrthographic::WorldToScreen(float x, float y) {
	float w = 0.0f;
	float h = 0.0f;

	if (m_aspectRatio < 1.0f) {
		w = 5.0;
		h = w / m_aspectRatio;
	}
	else {
		h = 5.0;
		w = h * m_aspectRatio;
	}

	D2D1_POINT_2F p;
	p.x = (x + w / 2.0f) / w * m_screenWidth;
	p.y = (h - (y + h / 2.0f)) / h * m_screenHeight;
	return p;
}
