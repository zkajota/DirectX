#pragma once
#include <vector>
#include <d3d11.h>
#include <d3dx10math.h>

struct InstanceTypeLevel;

class Field
{
public:
	bool walkable;
	bool isGoal;
	D3DXVECTOR3 direction;
	D3DXVECTOR3 goal;

	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_velocity;

	bool Update(D3DXMATRIX *_world);
	InstanceTypeLevel * myPositioninst;
	Field();
	~Field();
};

