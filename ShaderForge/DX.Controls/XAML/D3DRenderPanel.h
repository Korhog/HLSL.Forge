#pragma once

#include "pch.h"

#include "Utils\ShaderStructures.h"
#include "Utils\StepTimer.h"
#include "XAML\DXPanelBase.h"
#include <string>
#include <vector>

#include <Mesh.h>
#include <InputBase.h>

using namespace std;

namespace DXControls
{
	// Панель для отрисовки D3D в XAML 
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class D3DRenderPanel sealed : public DXControls::DXPanelBase
	{
	public:
		D3DRenderPanel();

		void StartRenderLoop();
		void StopRenderLoop();

		void CompilePixelShader(Platform::String ^data);
	private protected:

		virtual void Render() override;	    
		virtual void CreateDeviceResources() override;
		virtual void CreateSizeDependentResources() override;

		Microsoft::WRL::ComPtr<IDXGIOutput> m_dxgiOutput;

		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;

		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
		
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;

		std::unique_ptr<MarcusEngine::Mesh::Mesh> m_mesh;
		std::shared_ptr<MarcusEngine::Input::InputBase> m_input;

		DX::ModelViewProjectionConstantBuffer m_constantBufferData;
		float m_degreesPerSecond = 10;

		uint32 m_indexCount;

		Windows::Foundation::IAsyncAction^ m_renderLoopWorker;
		DX::StepTimer m_timer;
	private:
		double m_rotation_y = 0;
		double m_rotation_x = 0;

		~D3DRenderPanel();
	};
}