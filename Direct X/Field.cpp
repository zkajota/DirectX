#include "Field.h"
#include "modelclass.h"
#include <d3d11.h>
#include <d3dx10math.h>



bool Field::Update(D3DXMATRIX *world_matrix)
{
	//m_velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	
	D3DXMatrixTranslation(world_matrix, m_position.x, m_position.y, m_position.z);
	return false;

	//myPositioninst->position = m_position;
}

Field::Field()
{
	//walkable = true;
	isGoal = false;
	direction = D3DXVECTOR3(0, 0, 0);
	goal = D3DXVECTOR3(0, 0, 0);
}


Field::~Field()
{

}

