#pragma once
#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>
#include <vector>
#include "Field.h"
#include "textureclass.h"

struct InstanceTypeLevel
{
	D3DXVECTOR3 position;
	
};

class Level
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

	Level();
	~Level();

	bool Initialize(ID3D11Device*, char*, WCHAR*, int _numOfInstances, int _width, int _height);
	void Shutdown();
	void Render(ID3D11DeviceContext*);
	void Update();
	void SetGoals(D3DXVECTOR3 &_goal);

	int GetIndexCount();
	int GetVertexCount();
	int GetInstanceCount();
	int GetGoalID();
	D3DXVECTOR3 ReturnGoalPosition();

	int m_instanceCount;
	int m_goalID;

	ID3D11ShaderResourceView* GetTexture();

	void SetInstancePosition(D3DXVECTOR3 new_position, int currentObject);

	D3DXMATRIX world_matrix;

	std::vector<Field*> GetFields();

	std::vector<InstanceTypeLevel> instanceData_vector;
private:
	bool setNewGoal;
	int width, height;
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

	bool LoadModel(char*);
	void ReleaseModel();

	D3D11_BUFFER_DESC instanceBufferDesc;
	D3D11_SUBRESOURCE_DATA instanceData;
	ID3D11Device* my_device;
	ID3D11Buffer * m_vertexBuffer, *m_indexBuffer;
	ID3D11Buffer* m_instanceBuffer;
	int m_vertexCount, m_indexCount;

	TextureClass* m_Texture;
	ModelType* m_model; // reads and holds the model data, before its placed in vertex buffer

	std::vector<Field*> fields;

};

