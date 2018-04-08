#pragma once
#include <d3d11.h>
#include <d3dx10math.h>

struct InstanceType;

class Agent
{
public:

	void Update();
	void AddForce(D3DXVECTOR3);

	Agent();
	~Agent();

	D3DXVECTOR3 akceleracja;
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_velocity;

	D3DXVECTOR3 power;

	InstanceType * myPositioninst;

};

