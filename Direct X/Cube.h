#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "GameObject.h"


struct ConstantBuffer
{
	DirectX::XMMATRIX gWVP;
};

class Cube : public GameObject
{
public:
	Cube();
	~Cube();


	void init(ID3D11Device* device, ID3D11DeviceContext * deviceContext);
	void updateBuffer(ID3D11DeviceContext* deviceContext, DirectX::XMMATRIX worldMat);
	void Draw(DrawData* _DD) override;

private:
	// Geometry values
	DWORD mNumVertices;
	DWORD mNumFaces;
	DWORD mNumEdges;

	// DirectX objects
	ID3D11Device* md3dDevice;
	ID3D11DeviceContext* md3dDeviceContext;
	ID3D11Buffer* mVertexBuffer;
	ID3D11Buffer* mIndexBuffer;
	ID3D11Buffer* mConstantBuffer_GPU;
	ConstantBuffer* mConstantBuffer_CPU;
};