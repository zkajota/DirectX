#include "Level.h"
#include <time.h>


Level::Level()
{
	width = 0;
	height = 0;
	m_goalID = 0;
	setNewGoal = false;
}


Level::~Level()
{
}

bool Level::Initialize(ID3D11Device* device, char* modelFilename, WCHAR* textureFilename, int _instanceCount, int _width, int _height)
{
	width = _width;
	height = _height;
	m_instanceCount = _instanceCount;
	bool result;
	
	// Load in the model data,
	result = LoadModel(modelFilename);
	if (!result)
	{
		return false;
	}

	// Initialize the vertex and index buffer that hold the geometry for the triangle.
	result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}
	// Load the texture for this model.
	result = LoadTexture(device, textureFilename);
	if (!result)
	{
		return false;
	}
	return true;
}

void Level::Shutdown()
{
	// Release the model data.
	ReleaseModel();
	// Release the model texture.
	ReleaseTexture();
	// Release the vertex and index buffers.
	ShutdownBuffers();
	return;
}

void Level::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);
	Update();
	return;
}

void Level::Update()
{
	for (int i = 0; i < fields.size(); ++i)
	{
		fields[i]->Update(&world_matrix);
	}
	// update vector field if new detected;
}

void Level::SetGoals(D3DXVECTOR3 &_goal)
{
	if (setNewGoal == false)
	{
		for (int i = 0; i < m_indexCount; i++)
		{
			fields[i]->goal = _goal;
		}
	}
	setNewGoal = true;
}

int Level::GetVertexCount()
{
	return m_vertexCount;
}

int Level::GetInstanceCount()
{
	return m_instanceCount;
}

int Level::GetGoalID()
{
	return m_goalID;
}

D3DXVECTOR3 Level::ReturnGoalPosition()
{
	int i = GetGoalID();
	return fields[i]->myPositioninst->position / 2;
}

int Level::GetIndexCount()
{
	return m_indexCount;
}

ID3D11ShaderResourceView* Level::GetTexture()
{
	return m_Texture->GetTexture();
}

bool Level::InitializeBuffers(ID3D11Device* device)
{
	my_device = device;
	VertexType* vertices;
	unsigned long* indices;
	InstanceTypeLevel* instances;

	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;
	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}
	// Load the vertex array and index array with data.
	for (i = 0; i<m_vertexCount; i++)
	{
		vertices[i].position = D3DXVECTOR3(m_model[i].x, m_model[i].y, m_model[i].z);
		vertices[i].texture = D3DXVECTOR2(m_model[i].tu, m_model[i].tv);
		vertices[i].normal = D3DXVECTOR3(m_model[i].nx, m_model[i].ny, m_model[i].nz);

		indices[i] = i;
	}

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;


	instanceData_vector.reserve(m_instanceCount);
	instanceData_vector.resize(m_instanceCount);

	srand(time(nullptr));
	int currentObject = 0;
	bool goalTarget = false;

	//float rowMin = 0;
	//float rowMax = width;
	//float row = rowMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rowMax - rowMin)));
	int row, column;
	row = rand() % width + 0;
	column = rand() % height + 0;

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			float LO = 0.0f; float HI = 10.0f;
			float r3 = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));

			Field * field = new Field;
			fields.push_back(field);
			//SetInstancePosition(D3DXVECTOR3(x * 2, y * 2, 0), currentObject);
			SetInstancePosition(D3DXVECTOR3(x * 2, y * 2, 0), currentObject);
			field->myPositioninst = &instanceData_vector[currentObject];
			if (r3 > 8.0f)
			{
				field->walkable = true;
				if (x >= row && y >= column)
				{
					if (goalTarget == false)
					{
						field->isGoal = true;
						goalTarget = true;
						m_goalID = currentObject;
					}
				}
			}
			else
			{
				field->walkable = false;
			}
			currentObject++;
		}
	}

	// Set up the description of the instance buffer.
	instanceBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	instanceBufferDesc.ByteWidth = sizeof(InstanceTypeLevel) * m_instanceCount;
	instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	instanceBufferDesc.CPUAccessFlags = 0;
	instanceBufferDesc.MiscFlags = 0;
	instanceBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the instance data.
	instanceData.pSysMem = &instanceData_vector[0];
	instanceData.SysMemPitch = 0;
	instanceData.SysMemSlicePitch = 0;

	// Create the instance buffer.
	result = device->CreateBuffer(&instanceBufferDesc, &instanceData, &m_instanceBuffer);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}



void Level::ShutdownBuffers()
{
	// Release the instance buffer.
	if (m_instanceBuffer)
	{
		m_instanceBuffer->Release();
		m_instanceBuffer = 0;
	}

	// Release the index buffer.
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}


void Level::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int strides[2];
	unsigned int offsets[2];
	ID3D11Buffer* bufferPointers[2];

	// Set the buffer strides.
	strides[0] = sizeof(VertexType);
	strides[1] = sizeof(InstanceTypeLevel);

	// Set the buffer offsets.
	offsets[0] = 0;
	offsets[1] = 0;

	// Set the array of pointers to the vertex and instance buffers.
	bufferPointers[0] = m_vertexBuffer;
	bufferPointers[1] = m_instanceBuffer;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 2, bufferPointers, strides, offsets);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

bool Level::LoadTexture(ID3D11Device* device, WCHAR* filename)
{
	bool result;

	// Create the texture object.
	m_Texture = new TextureClass;
	if (!m_Texture)
	{
		return false;
	}

	// Initialize the texture object.
	result = m_Texture->Initialize(device, filename);
	if (!result)
	{
		return false;
	}

	return true;
}

bool Level::LoadModel(char* filename)
{
	std::ifstream fin;
	char input;
	int i;


	// Open the model file.
	fin.open(filename);

	// If it could not open the file then exit.
	if (fin.fail())
	{
		return false;
	}

	// Read up to the value of vertex count.
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}

	// Read in the vertex count.
	fin >> m_vertexCount;

	// Set the number of indices to be the same as the vertex count.
	m_indexCount = m_vertexCount;

	// Create the model using the vertex count that was read in.
	m_model = new ModelType[m_vertexCount];
	if (!m_model)
	{
		return false;
	}

	// Read up to the beginning of the data.
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}
	fin.get(input);
	fin.get(input);

	// Read in the vertex data.
	for (i = 0; i<m_vertexCount; i++)
	{
		fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
		fin >> m_model[i].tu >> m_model[i].tv;
		fin >> m_model[i].nx >> m_model[i].ny >> m_model[i].nz;
	}

	// Close the model file.
	fin.close();

	return true;
}

void Level::ReleaseModel()
{
	if (m_model)
	{
		delete[] m_model;
		m_model = 0;
	}

	return;
}

void Level::ReleaseTexture()
{
	// Release the texture object.
	if (m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}

	return;
}

void Level::SetInstancePosition(D3DXVECTOR3 new_position, int i)
{
	instanceData_vector[i].position = new_position;
}

std::vector<Field*> Level::GetFields()
{

	return fields;
}
