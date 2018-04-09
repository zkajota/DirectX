#pragma once
#include <vector>
#include <d3d11.h>
#include <d3dx10math.h>

struct InstanceTypeLevel;

class Field
{
public:
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_velocity;

	void Update(std::vector<Field*> *fields);
	InstanceTypeLevel * myPositioninst;
	Field();
	~Field();
};

