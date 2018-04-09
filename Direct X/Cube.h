#pragma once
#include <d3d11.h>
#include <d3dx10math.h>

struct VertexType
{
	D3DXVECTOR3 position;
	D3DXVECTOR4 color;
};

class Cube
{
public:
	Cube();
	~Cube();

	bool Initialise(ID3D11Device*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);
	int GetIndexCount();

	int GetInstanceCount();
	int GetVertexCount();

private:
	bool InitalizeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	int m_instanceCount;
};

