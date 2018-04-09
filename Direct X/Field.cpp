#include "Field.h"
#include "modelclass.h"
#include <d3d11.h>
#include <d3dx10math.h>



void Field::Update(std::vector<Field*>* fields)
{
	m_velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_position = m_position + m_velocity;
	//myPositioninst->position = m_position;
}

Field::Field()
{

}


Field::~Field()
{

}
