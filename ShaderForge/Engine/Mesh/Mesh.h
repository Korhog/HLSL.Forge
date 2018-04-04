#pragma once

namespace MarcusEngine {
	namespace Mesh {
		class Mesh {
		protected:
			UINT32 m_indexCount;

			Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
			Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;
		private:
			ULONG m_cRef;
		public:
			__declspec(property(get = GetIndexCount)) UINT32 IndexCount;
			virtual void CreateBuffers(ID3D11Device1 *device) abstract;

			ID3D11Buffer* GetVertexBuffer() { return m_vertexBuffer.Get(); }
			ID3D11Buffer* GetIndexBuffer() { return m_indexBuffer.Get(); }
			UINT32 GetIndexCount() { return m_indexCount; }	
		};

		class Mesh2D : public Mesh {
		public:
			void CreateBuffers(ID3D11Device1 *device) {};
		};

		class Mesh3D : public Mesh {	
		public:
			virtual void CreateBuffers(ID3D11Device1 *device) {};
		};

		class Box : public Mesh3D {
		public:
			virtual void CreateBuffers(ID3D11Device1 *device) override;
		};

		class Sphere : public Mesh3D{
			virtual void CreateBuffers(ID3D11Device1 *device) override;
		};
	}
}
