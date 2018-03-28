#include "pch.h"
#include "XAML\DXPanelBase.h"
#include "Utils\DXTools.h"

#include <math.h> 
#include <ppltasks.h> 
#include <DirectXMath.h> 
#include <windows.ui.xaml.media.dxinterop.h>

using namespace Microsoft::WRL;
using namespace Platform;
using namespace Windows::ApplicationModel;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Graphics::Display;
using namespace Windows::System::Threading;
using namespace Windows::UI;
using namespace Windows::UI::Core;
using namespace Windows::UI::Input::Inking;
using namespace Windows::Storage::Streams;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Interop;
using namespace Concurrency;
using namespace DirectX;
using namespace D2D1;
using namespace DXControls;
using namespace DX;

static const float m_dipsPerInch = 96.0f;

namespace DXControls
{
	DXPanelBase::DXPanelBase():
		m_loadingComplete(false),
		m_backgroundColor(D2D1::ColorF(D2D1::ColorF::White)),
		m_alphaMode(DXGI_ALPHA_MODE_UNSPECIFIED), 
		m_compositionScaleX(1.0f),
		m_compositionScaleY(1.0f),
		m_height(1.0f),
		m_width(1.0f)
	{		
		this->SizeChanged += ref new Windows::UI::Xaml::SizeChangedEventHandler(this, &DXPanelBase::OnSizeChanged);
		this->CompositionScaleChanged += ref new Windows::Foundation::TypedEventHandler<SwapChainPanel^, Object^>(this, &DXPanelBase::OnCompositionScaleChanged);
		Application::Current->Suspending += ref new SuspendingEventHandler(this, &DXPanelBase::OnSuspending);
		Application::Current->Resuming += ref new EventHandler<Object^>(this, &DXPanelBase::OnResuming);		
	}

	// Создание ресурсов устройства
	void DXPanelBase::CreateDeviceResources()
	{
		
		UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(_DEBUG)
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		// уровни совместимости
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1
		};

		ComPtr<ID3D11Device> device;
		ComPtr<ID3D11DeviceContext> context;
		
		ThrowIfFailed(
			D3D11CreateDevice(
				nullptr,
				D3D_DRIVER_TYPE_HARDWARE,
				0,
				creationFlags,
				featureLevels,
				ARRAYSIZE(featureLevels),
				D3D11_SDK_VERSION,
				&device,
				NULL,
				&context
			)
		);
		
		ThrowIfFailed(device.As(&m_d3dDevice));
		ThrowIfFailed(context.As(&m_d3dContext));

		
		ComPtr<IDXGIDevice> dxgiDevice;
		ThrowIfFailed(m_d3dDevice.As(&dxgiDevice));
		ThrowIfFailed(m_d2dFactory->CreateDevice(dxgiDevice.Get(), &m_d2dDevice));

		ThrowIfFailed(
			m_d2dDevice->CreateDeviceContext(
				D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
				&m_d2dContext
			)
		);

		m_d2dContext->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);		
	}

	// Создание ресурсов зависимых от устройства
	void DXPanelBase::CreateDeviceIndependentResources()
	{
		D2D1_FACTORY_OPTIONS options;
		ZeroMemory(&options, sizeof(D2D1_FACTORY_OPTIONS));

#if defined(_DEBUG) 
		// Enable D2D debugging via SDK Layers when in debug mode. 
		options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#endif 

		ThrowIfFailed(
			D2D1CreateFactory(
				D2D1_FACTORY_TYPE_SINGLE_THREADED,
				__uuidof(ID2D1Factory2),
				&options,
				&m_d2dFactory
			)
		);
	}
	// Создание ресурсов зависимых от размера экрана
	void DXPanelBase::CreateSizeDependentResources()
	{		
		m_d2dContext->SetTarget(nullptr);
		m_d2dTargetBitmap = nullptr;
		
		m_d3dContext->OMSetRenderTargets(0, nullptr, nullptr);		
		m_d3dContext->Flush();

		m_renderTargetWidth = m_width * m_compositionScaleX;
		m_renderTargetHeight = m_height * m_compositionScaleY;	
		
		// Если цепочка уже существует, надо поменять ее размер
		if (m_swapChain != nullptr) {
			HRESULT hr = m_swapChain->ResizeBuffers(
				2,
				static_cast<UINT>(m_renderTargetWidth),
				static_cast<UINT>(m_renderTargetHeight),
				DXGI_FORMAT_B8G8R8A8_UNORM,
				0
			);

			if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET) {
				OnDeviceLost();
				return;
			}
			else {
				ThrowIfFailed(hr);
			}
		}
		else { // Если нет, создаем новую
			DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };

			swapChainDesc.Width = static_cast<UINT>(m_renderTargetWidth);
			swapChainDesc.Height = static_cast<UINT>(m_renderTargetHeight);
			swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
			swapChainDesc.Stereo = false;
			swapChainDesc.SampleDesc.Count = 1;
			swapChainDesc.SampleDesc.Quality = 0;
			swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapChainDesc.BufferCount = 2;
			swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
			swapChainDesc.Flags = 0;
			swapChainDesc.AlphaMode = m_alphaMode;

			ComPtr<IDXGIDevice1> dxgiDevice;
			ThrowIfFailed(m_d3dDevice.As(&dxgiDevice));

			ComPtr<IDXGIAdapter> dxgiAdapter;
			ThrowIfFailed(dxgiDevice->GetAdapter(&dxgiAdapter));

			ComPtr<IDXGIFactory2> dxgiFactory;
			ThrowIfFailed(dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory)));

			ComPtr<IDXGISwapChain1> swapChain;
			ThrowIfFailed(
				dxgiFactory->CreateSwapChainForComposition(
					m_d3dDevice.Get(),
					&swapChainDesc,
					nullptr,
					&swapChain
				)
			);

			swapChain.As(&m_swapChain);

			ThrowIfFailed(dxgiDevice->SetMaximumFrameLatency(1));

			Dispatcher->RunAsync(
				CoreDispatcherPriority::Normal, ref new DispatchedHandler([=]() {
					ComPtr<ISwapChainPanelNative> panelNative;
					ThrowIfFailed(
						reinterpret_cast<IUnknown*>(this)->QueryInterface(IID_PPV_ARGS(&panelNative))
					);

					ThrowIfFailed(
						panelNative->SetSwapChain(m_swapChain.Get())
					);
				}, CallbackContext::Any
			));
		}

		DXGI_MATRIX_3X2_F inverseScale = { 0 };
		inverseScale._11 = 1.0f / m_compositionScaleX;
		inverseScale._22 = 1.0f / m_compositionScaleY;

		m_swapChain->SetMatrixTransform(&inverseScale);

		D2D1_BITMAP_PROPERTIES1 bitmapProperties = BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
			PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
			m_dipsPerInch * m_compositionScaleX,
			m_dipsPerInch * m_compositionScaleY
		);

		ComPtr<IDXGISurface> dxgiBackBuffer;
		ThrowIfFailed(m_swapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiBackBuffer)));

		ThrowIfFailed(m_d2dContext->CreateBitmapFromDxgiSurface(
			dxgiBackBuffer.Get(),
			&bitmapProperties,
			&m_d2dTargetBitmap
		));

		m_d2dContext->SetDpi(m_dipsPerInch * m_compositionScaleX, m_dipsPerInch * m_compositionScaleY);
		m_d2dContext->SetTarget(m_d2dTargetBitmap.Get());		
	}

	void DXPanelBase::Present() {
		DXGI_PRESENT_PARAMETERS params = { 0 };
		params.DirtyRectsCount = 0;
		params.pDirtyRects = nullptr;
		params.pScrollOffset = nullptr;
		params.pScrollRect = nullptr;

		HRESULT hr = S_OK;

		hr = m_swapChain->Present1(1, 0, &params);

		if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
		{
			OnDeviceLost();
		}
		else
		{
			ThrowIfFailed(hr);
		}
	}

	void DXPanelBase::OnSuspending(Object^ sender, SuspendingEventArgs^ e)
	{
		critical_section::scoped_lock lock(m_criticalSection);
		ComPtr<IDXGIDevice3> dxgiDevice;
		m_d3dDevice.As(&dxgiDevice);

		// Hints to the driver that the app is entering an idle state and that its memory can be used temporarily for other apps. 
		dxgiDevice->Trim();
	}

	void DXPanelBase::OnSizeChanged(Object^ sender, SizeChangedEventArgs^ e)
	{
		if (m_width != e->NewSize.Width || m_height != e->NewSize.Height)
		{
			critical_section::scoped_lock lock(m_criticalSection);

			m_width = max(e->NewSize.Width, 1.0f);
			m_height = max(e->NewSize.Height, 1.0f);

			CreateSizeDependentResources();
		}
	}

	void DXPanelBase::OnCompositionScaleChanged(SwapChainPanel ^sender, Object ^args)
	{
		if (m_compositionScaleX != CompositionScaleX || m_compositionScaleY != CompositionScaleY)
		{
			critical_section::scoped_lock lock(m_criticalSection);
			m_compositionScaleX = this->CompositionScaleX;
			m_compositionScaleY = this->CompositionScaleY;
			CreateSizeDependentResources();
		}
	}

	void DXPanelBase::OnDeviceLost()
	{
		m_loadingComplete = false;

		m_swapChain = nullptr;

		m_d3dContext->OMSetRenderTargets(0, nullptr, nullptr);

		m_d2dContext->SetTarget(nullptr);
		m_d2dTargetBitmap = nullptr;

		m_d2dContext = nullptr;
		m_d2dDevice = nullptr;

		m_d3dContext->Flush();

		CreateDeviceResources();
		CreateSizeDependentResources();
	}
}