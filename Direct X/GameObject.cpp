#include "GameObject.h"



GameObject::GameObject()
{
	//set the Gameobject to the origin with no rotation and unit scaling 
	m_pos = XMVectorZero();
	m_pitch = 0.0f;
	m_yaw = 0.0f;
	m_roll = 0.0f;
	m_scale = XMLoadFloat3(new XMFLOAT3(1,1,1));

	m_worldMat = XMMatrixIdentity();
	m_fudge = XMMatrixIdentity();
}


GameObject::~GameObject()
{
}

void GameObject::Tick()
{
	if (m_physicsOn)
	{
		float dt =0.01f;

		XMVECTOR newVel = m_vel + dt * (m_acc - m_drag*m_vel);
		XMVECTOR newPos = m_pos + dt * m_vel;

		m_vel = newVel;
		m_pos = newPos;
	}

	//build up the world matrix depending on the new position of the GameObject
	//the assumption is that this class will be inherited by the class that ACTUALLY changes this
	XMMATRIX  scaleMat = XMMatrixScalingFromVector(m_scale);
	m_rotMat = XMMatrixRotationRollPitchYaw(m_pitch, m_yaw, m_roll); //possible not the best way of doing this!
	XMMATRIX  transMat = XMMatrixTranslationFromVector(m_pos);

	m_worldMat = m_fudge * scaleMat * m_rotMat * transMat;

	//zero acceleration ready for the next time round
	m_acc = XMVectorZero();
}

