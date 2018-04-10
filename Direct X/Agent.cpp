#include "Agent.h"
#include <d3d11.h>
#include <d3dx10math.h>
#include <random>
#include "modelclass.h"




void Agent::Update(std::vector<Agent*> *_agents, D3DXVECTOR3 *_goal)
{
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
	//keepDistance

	D3DXVECTOR3 goalVelocity = D3DXVECTOR3(directionX, directionY, 0.0f);
	D3DXVECTOR3 separation = Separate(_agents);
	//goalVelocity = D3DXVECTOR3(0.1, 0, 0);
	m_velocity = goalVelocity;
	//m_velocity = m_velocity + separation;
	m_position = m_position + m_velocity;
	myPositioninst->position = m_position;
}

D3DXVECTOR3 Agent::Separate(std::vector<Agent*>* _agents)
{
		//float desiredseparation = 2;
		auto sum = D3DXVECTOR3(0,0,0);
		D3DXVECTOR3 desiredSeparation = D3DXVECTOR3(200, 200, 0);
		for (auto& agent : *_agents)
		{
			if (id != agent->id)
			{
				D3DXVECTOR3 distance = m_position - agent->m_position;
				//if (distance > 0 && distance < desiredSeparation)
				if (distance > desiredSeparation)
				{
					//_goal /= distance;
					sum += distance;
				}
			}
		}
		/*for (int i = 0; i < sizeof(_agents); i++)
		{
			if (&_agents[i]->)
			{

			}
		}*/
		return sum;
}

//DirectX::XMVECTOR Agent::Separate(std::vector<Agent*>* agents)
//{
//	float desiredseparation = 2;
//	auto sum = XMVECTOR(,0,0,0);
//	auto separation_count = 0;
//
//
//	for (auto& agent : *agents)
//	{
//		
//		const auto distance = Distance(m_position, agent->m_position);
//		if (distance > 0 && distance < desiredseparation)
//		{
//			auto direction = m_position - agent->m_position;
//			Normalize(direction);
//			direction /= distance;
//			sum += direction;
//			separation_count++;
//		}
//	}
//
//	if (separation_count > 0)
//	{
//		sum /= separation_count;
//	}
//	if (Length(sum) > 0)
//	{
//		Normalize(sum);
//		sum *= m_max_speed;
//		sum -= m_vel;
//		LimitLength(sum, m_max_force);
//	}
//
//	return sum;
//}

void Agent::AddForce(D3DXVECTOR3 _force)
{

}

Agent::Agent()
{
	m_velocity = D3DXVECTOR3(0.05f, 0.05f, 0.0f);
	speed = 0.1f;
	directionX = 0.0f;
	directionY = 0.0f;
}


Agent::~Agent()
{
}

float Agent::Distance(const D3DXVECTOR3 & v1, const D3DXVECTOR3 & v2)
{
	float dist = &v1 - &v2;
	return dist;
}