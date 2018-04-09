//#include "GeometryGenerator.h"
//
//
//
//GeometryGenerator::GeometryGenerator()
//{
//}
//
//
//GeometryGenerator::~GeometryGenerator()
//{
//}
//
//void GeometryGenerator::CreateGrid(float width, float depth, int m, int n, MeshData& meshData, ID3D11Device *_my_device)
//{
//	int vertexCount = m * n;
//	int faceCount = (m - 1)*(n - 1) * 2;
//	//
//	// Create the vertices.
//	//
//	float halfWidth = 0.5f*width;
//	float halfDepth = 0.5f*depth;
//	float dx = width / (n - 1);
//	float dz = depth / (m - 1);
//	float du = 1.0f / (n - 1);
//	float dv = 1.0f / (m - 1);
//	meshData.Vertices.resize(vertexCount);
//	for (int i = 0; i < m; ++i)
//	{
//		float z = halfDepth - i * dz;
//		for (int j = 0; j < n; ++j)
//		{
//			float x = -halfWidth + j * dx;
//			meshData.Vertices[i*n + j].Position = XMFLOAT3(x, 0.0f, z);
//			// Ignore for now, used for lighting.
//			meshData.Vertices[i*n + j].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
//			meshData.Vertices[i*n + j].TangentU = XMFLOAT3(1.0f, 0.0f, 0.0f);
//			// Ignore for now, used for texturing.
//			meshData.Vertices[i*n + j].TexC.x = j * du;
//			meshData.Vertices[i*n + j].TexC.y = i * dv;
//		}
//	}
//	meshData.Indices.resize(faceCount * 3); // 3 indices per face
//											// Iterate over each quad and compute indices.
//	int k = 0;
//	for (int i = 0; i < m - 1; ++i)
//	{
//		for (int j = 0; j < n - 1; ++j)
//		{
//			meshData.Indices[k] = i * n + j;
//			meshData.Indices[k + 1] = i * n + j + 1;
//			meshData.Indices[k + 2] = (i + 1)*n + j;
//			meshData.Indices[k + 3] = (i + 1)*n + j;
//			meshData.Indices[k + 4] = i * n + j + 1;
//			meshData.Indices[k + 5] = (i + 1)*n + j + 1;
//			k += 6; // next quad
//		}
//	}
//
//
//	GeometryGenerator::MeshData grid;
//	GeometryGenerator geoGen;
//	geoGen.CreateGrid(160.0f, 160.0f, 50, 50, grid);
//	mGridIndexCount = grid.Indices.size();
//
//	D3D11_BUFFER_DESC vbd;
//	vbd.Usage = D3D11_USAGE_IMMUTABLE;
//	vbd.ByteWidth = sizeof(Vertex) * grid.Vertices.size();
//	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//	vbd.CPUAccessFlags = 0;
//	vbd.MiscFlags = 0;
//	D3D11_SUBRESOURCE_DATA vinitData;
//	vinitData.pSysMem = &vertices[0];
//	HR(_my_device->CreateBuffer(&vbd, &vinitData, &mVB));
//
//	D3D11_BUFFER_DESC ibd;
//	ibd.Usage = D3D11_USAGE_IMMUTABLE;
//	ibd.ByteWidth = sizeof(UINT) * mGridIndexCount;
//	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
//	ibd.CPUAccessFlags = 0;
//	ibd.MiscFlags = 0;
//	D3D11_SUBRESOURCE_DATA iinitData;
//	iinitData.pSysMem = &grid.Indices[0];
//	HR(md3dDevice->CreateBuffer(&ibd, &iinitData, &mIB));
//}
