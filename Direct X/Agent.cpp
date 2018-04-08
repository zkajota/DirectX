#include "Agent.h"
#include <d3d11.h>
#include <d3dx10math.h>
#include <random>
#include "modelclass.h"




void Agent::Update(std::vector<Agent*> *_agents, D3DXVECTOR3 *_goal)
{
	//float new_mPosX = -12.0f;

	if (m_position.x < _goal->x)
	{
		directionX = speed;
	}
	else if (m_position.x > _goal->x)
	{
		directionX = -speed;
	}
	if (m_position.y < _goal->y)
	{
		directionY = speed;
	}
	else if (m_position.y > _goal->y)
	{
		directionY = -speed;
	}

	D3DXVECTOR3 goalVelocity = D3DXVECTOR3(directionX, directionY, 0.0f);

	////m_position.x = m_position.x + directionX + KeepDistance(_agents).x;
	//m_position.y = m_position.y + directionY + KeepDistance(_agents).y;
	////D3DXMatrixTranslation(&world_matrix, m_posX, m_posY, m_posZ);

	//m_velocity.x = m_position.x + directionX + KeepDistance(_agents).x;

	m_velocity = goalVelocity;
	m_position = m_position + m_velocity;
	//m_velocity += akceleracja;
	//m_position += m_velocity; // multiply by deltatime
	//akceleracja *= 0;

	myPositioninst->position = m_position;

	//AddForce(power);
}

void Agent::AddForce(D3DXVECTOR3 _force)
{
	//akceleracja += _force;
}

Agent::Agent()
{
	//akceleracja = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_velocity = D3DXVECTOR3(0.05f, 0.05f, 0.0f);
	speed = 0.1f;
	directionX = 0.0f;
	directionY = 0.0f;
}


Agent::~Agent()
{
}
