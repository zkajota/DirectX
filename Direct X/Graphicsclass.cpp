////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Graphicsclass.h"
#include <d3dx9math.h>


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_LightShader = 0;
	m_Light = 0;
	m_Cube = 0;
	m_ColorShader = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{

}


GraphicsClass::~GraphicsClass()
{

}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;


	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if (!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -100.0f);

	// Create the model object.
	m_Model = new ModelClass;
	//m_Model = new GameObject;
	if (!m_Model)
	{
		return false;
	}

	// Initialize the model object.
	WCHAR texture[] = L"../data/tileFloor.dds";
	char model[] = "../data/cube.txt";
	result = m_Model->Initialize(m_D3D->GetDevice(), model, texture, 10, true);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	
	char model2[] = "../data/cube.txt";
	WCHAR texture2[] = L"../data/seafloor.dds";
	int width = 20;
	int height = 20;
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			m_Cube = new ModelClass;
			result = m_Cube->Initialize(m_D3D->GetDevice(), model2, texture2, 1, false);
			m_Cube->SetInstancePosition(D3DXVECTOR3(x*2, y*2, 0));
			m_level.push_back(m_Cube);
		}
	}
	/*m_Cube = new ModelClass;
	result = m_Cube->Initialize(m_D3D->GetDevice(), model2, texture2, 1, false);
	m_Cube->SetInstancePosition(D3DXVECTOR3(1, 1, 0));*/
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the m_Cube.", L"Error", MB_OK);
		return false;
	}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	m_ColorShader = new ColorShaderClass;
	if (!m_ColorShader)
	{
		return false;
	}

	result = m_ColorShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the m_ColorShader.", L"Error", MB_OK);
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(1.0f, 0.0f, 0.0f);



	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the model object.
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	if (m_Cube)
	{
		m_Cube->Shutdown();
		delete m_Cube;
		m_Cube = 0;
	}
	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}
	return;
}


bool GraphicsClass::Frame()
{
	bool result;

	// Render the graphics scene.
	result = Render();
	if (!result)
	{
		return false;
	}
	Update();

	return true;
}

void GraphicsClass::Update()
{

}


bool GraphicsClass::Render()
{
	D3DXMATRIX viewMatrix, projectionMatrix, worldMatrix;
	bool result;
	bool cube;

	D3DXMATRIX cubeROT, cubeMOVE;

	//D3DXMatrixRotationY(&cubeROT, D3DXToRadian(45.0f));
	//D3DXMatrixTranslation(&worldMatrix, 10.0f, 2.0f, 1.0f);
	//D3DXMatrixMultiply(&worldMatrix, &(cubeROT * cubeMOVE));
	
	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Rotate the world matrix by the rotation value so that the triangle will spin.
	//D3DXMatrixRotationY(&worldMatrix, rotation);


	 //Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.

	for(auto tile :m_level)
	{
		tile->Render(m_D3D->GetDeviceContext());
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), tile->GetIndexCount(), tile->GetVertexCount(), tile->GetInstanceCount(), tile->world_matrix, viewMatrix, projectionMatrix, tile->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
		if (!result)
		{
			return false;
		}
	}
	

	m_Model->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), m_Model->GetVertexCount(), m_Model->GetInstanceCount(), m_Model->world_matrix, viewMatrix, projectionMatrix, m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
	if (!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

void GraphicsClass::ZoomCamera(bool zoomIn)
{
	m_Camera->Zoom(zoomIn);
}

void GraphicsClass::MoveCamera(int _key)
{
	D3DXVECTOR3 camPos = m_Camera->GetPosition();

	switch (_key)
	{
	case 0x57:
		m_Camera->SetPosition(camPos.x, camPos.y + 1.0f, camPos.z);
		break;
	case 0x53:
		m_Camera->SetPosition(camPos.x, camPos.y - 1.0f, camPos.z);
		break;
	case 0x41:
		m_Camera->SetPosition(camPos.x - 1.0f, camPos.y, camPos.z);
		break;
	case 0x44:
		m_Camera->SetPosition(camPos.x + 1.0f, camPos.y, camPos.z);
	default:
		break;
	}
}