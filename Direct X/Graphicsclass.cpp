////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Graphicsclass.h"
#include <d3dx9math.h>
#include <vector>


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_LightShader = 0;
	m_Light = 0;
	m_Cube = 0;
	m_ColorShader = 0;
	m_level = 0;
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

	WCHAR texture[] = L"../data/tileFloor.dds";
	WCHAR texture2[] = L"../data/seafloor.dds";
	char model[] = "../data/cube.txt";
	char model2[] = "../data/cube2.txt";

	m_level = new Level;
	if (!m_level)
	{
		return false;
	}
	result = m_level->Initialize(m_D3D->GetDevice(), model2, texture, 40000, 200, 200);
	if (!result)
	{
		MessageBox(hwnd, L"znowu cos spierdolilem.", L"Error", MB_OK);
		return false;
	}

	m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}

	result = m_Model->Initialize(m_D3D->GetDevice(), model, texture2, 100, true);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
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
	if (m_level)
	{
		m_level->Shutdown();
		delete m_level;
		m_level = 0;
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
	
	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);	

	//D3DXVECTOR3 goal = D3DXVECTOR3(10, 25, 0);
	D3DXVECTOR3 goal = m_level->ReturnGoalPosition();
	m_level->SetGoals(goal);
	m_Model->Render(m_D3D->GetDeviceContext(), goal);
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), m_Model->GetVertexCount(), m_Model->GetInstanceCount(), m_Model->world_matrix, viewMatrix, projectionMatrix, m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
	if (!result)
	{
		return false;
	}

	m_level->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_level->GetIndexCount(), m_level->GetVertexCount(), m_level->GetInstanceCount(), m_level->world_matrix, viewMatrix, projectionMatrix, m_level->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
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