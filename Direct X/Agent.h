#pragma once
#include <d3d11.h>
#include <d3dx10math.h>
#include <vector>

struct InstanceType;

class Agent
{
public:
	int id;
	void Update(std::vector<Agent*> *agents, D3DXVECTOR3 *_goal);
	void AddForce(D3DXVECTOR3);

	D3DXVECTOR3 KeepDistance(std::vector<Agent*> *agents);

	Agent();
	~Agent();


	//D3DXVECTOR3 akceleracja;
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_velocity;

	D3DXVECTOR3 power;

	InstanceType * myPositioninst;
	
private:
	float speed;
	float directionX, directionY;

};

