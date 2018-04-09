//#include <d3d11.h>
//#include <DirectXMath.h>
//#include <vector>
//
//using namespace DirectX;
//
//class GeometryGenerator
//{
//public:
//	struct Vertex
//	{
//		Vertex() {}
//		Vertex(const XMFLOAT3& p,
//			const XMFLOAT3& n,
//			const XMFLOAT3& t,
//			const XMFLOAT2& uv)
//			: Position(p), Normal(n), TangentU(t), TexC(uv) {}
//		Vertex(
//			float px, float py, float pz,
//			float nx, float ny, float nz,
//			float tx, float ty, float tz,
//			float u, float v)
//			: Position(px, py, pz), Normal(nx, ny, nz),
//			TangentU(tx, ty, tz), TexC(u, v) {}
//		XMFLOAT3 Position;
//		XMFLOAT3 Normal;
//		XMFLOAT3 TangentU;
//		XMFLOAT2 TexC;
//	};
//	struct MeshData
//	{
//		std::vector<Vertex> Vertices;
//		std::vector<int> Indices;
//	};
//
//	ID3D11Device* my_device;
//	ID3D11Buffer * m_vertexBuffer, *m_indexBuffer;
//	ID3D11Buffer* m_instanceBuffer;
//
//	void CreateGrid(float width, float depth, int m, int n, MeshData& meshData, ID3D11Device *mydevice);
//	GeometryGenerator();
//	~GeometryGenerator();
//};