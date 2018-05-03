#pragma once

#include "pch.h"
#include <d2d1_2.h> 
#include <concrt.h> 

using namespace DirectX;

namespace DXControls
{
	// Базовый класс для отрисовки DirectX в XAML 
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class DXPanelBase : public Windows::UI::Xaml::Controls::SwapChainPanel
	{
	protected private:
		DXPanelBase();

		// Создание ресурсов устройства
		virtual void CreateDeviceResources();
		// Создание ресурсов зависимых от устройства
		virtual void CreateDeviceIndependentResources();
		// Создание ресурсов зависимых от размера экрана
		virtual void CreateSizeDependentResources();

		// События
		virtual void OnDeviceLost();
		virtual void OnSizeChanged(Platform::Object^ sender, Windows::UI::Xaml::SizeChangedEventArgs^ e);
		virtual void OnCompositionScaleChanged(Windows::UI::Xaml::Controls::SwapChainPanel ^sender, Platform::Object ^args);
		virtual void OnSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ e);
		virtual void OnResuming(Platform::Object^ sender, Platform::Object^ args) { };

		// Рисовать
		virtual void Present();
		virtual void Render() { };

		// D3D секция
		Microsoft::WRL::ComPtr<ID3D11Device1> m_d3dDevice; // устройство D3D
		Microsoft::WRL::ComPtr<ID3D11DeviceContext1> m_d3dContext; // контекст D3D 
		Microsoft::WRL::ComPtr<IDXGISwapChain2> m_swapChain; // 

		// D2D секция
		Microsoft::WRL::ComPtr<ID2D1Factory2> m_d2dFactory;
		Microsoft::WRL::ComPtr<ID2D1Device> m_d2dDevice;
		Microsoft::WRL::ComPtr<ID2D1DeviceContext> m_d2dContext;
		Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_d2dTargetBitmap;
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> m_whiteBrush;

		D2D1_COLOR_F m_backgroundColor;
		DXGI_ALPHA_MODE m_alphaMode;
		
		bool m_loadingComplete; // загрузка завершена

		Concurrency::critical_section m_criticalSection; // секция для синхронизации

		float m_renderTargetHeight;
		float m_renderTargetWidth;

		float m_compositionScaleX;
		float m_compositionScaleY;

		float m_height;
		float m_width;
	};
}

