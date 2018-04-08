#include "Agent.h"
#include <d3d11.h>
#include <d3dx10math.h>
#include <random>
#include "modelclass.h"




void Agent::Update()
{
	

	m_velocity += akceleracja;
	m_position += m_velocity; // multiply by deltatime
	akceleracja *= 0;
	
	myPositioninst->position = m_position;
	AddForce(power);
}

void Agent::AddForce(D3DXVECTOR3 _force)
{
	akceleracja += _force;
}

Agent::Agent()
{

	akceleracja = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_velocity = D3DXVECTOR3(0.05f, 0.05f, 0.0f);
}


Agent::~Agent()
{
}
