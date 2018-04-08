////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_
#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>
#include <vector>
#include "GameObject.h"
#include "Agent.h"
#include "textureclass.h"

class Agent;

struct InstanceType
{
	D3DXVECTOR3 position;
};


class ModelClass : public GameObject
{
public:

	
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;

	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*, char*, WCHAR*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);
	void Update();
	void Draw(DrawData* _DD) override;

	int GetIndexCount();
	int GetVertexCount();
	int GetInstanceCount();

	ID3D11ShaderResourceView* GetTexture();

	//matrix
	D3DXMATRIX world_matrix;
	//D3DXMATRIX translation_matrix;
	//D3DXMATRIX rotation_matrix;

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

	bool LoadModel(char*);
	void ReleaseModel();

	//float m_posX, m_posY, m_posZ;
	//float m_fPitch, m_fYaw, m_fRoll;
	D3D11_BUFFER_DESC instanceBufferDesc;
	D3D11_SUBRESOURCE_DATA instanceData;
	ID3D11Device* my_device;
	ID3D11Buffer * m_vertexBuffer, *m_indexBuffer;
	ID3D11Buffer* m_instanceBuffer;
	int m_vertexCount, m_indexCount, m_instanceCount;

	TextureClass* m_Texture;
	ModelType* m_model; // reads and holds the model data, before its placed in vertex buffer

	std::vector<InstanceType> instanceData_vector; // list of all isntances
	std::vector<Agent*> agents;//list of pointers
};

#endif
