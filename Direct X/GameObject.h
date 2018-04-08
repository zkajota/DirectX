#pragma once
#include <DirectXMath.h>

class Camera;
struct ID3D11DeviceContext;
struct GameData;
struct DrawData;

using namespace DirectX;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Tick();
	virtual void Draw(DrawData* _DD) =0;

	//getters
	XMVECTOR GetPos() { return m_pos; }
	XMVECTOR GetScale() { return m_scale; }

	float GetPitch() { return m_pitch; }
	float GetYaw() { return m_yaw; }
	float GetRoll() { return m_roll; }

	bool IsPhysicsOn() { return m_physicsOn; }
	float GetDrag() { return m_drag; }

	//setters
	void SetPos(XMVECTOR _pos) { m_pos = _pos; }

	//void		SetScale(float _scale) { m_scale = _scale * Vector3::One; }
	void SetScale(float _x, float _y, float _z) { m_scale = XMLoadFloat3(&XMFLOAT3(_x, _y, _z)); }
	void SetScale(XMVECTOR _scale) { m_scale = _scale; }

	void SetPitch(float _pitch) { m_pitch = _pitch; }
	void SetYaw(float _yaw) { m_yaw = _yaw; }
	void SetRoll(float _roll) { m_roll = _roll; }

	void SetPitchYawRoll(float _pitch, float _yaw, float _roll)
	{
		m_pitch = _pitch;
		m_yaw = _yaw;
		m_roll = _roll;
	}

	void SetPhysicsOn(bool _physics) { m_physicsOn = _physics; }
	void TogglePhysics() { m_physicsOn = !m_physicsOn; }
	void SetDrag(float _drag) { m_drag = _drag; }


protected:

	//World transform/matrix of this GO and it components
	XMMATRIX m_worldMat = XMMatrixIdentity();
	XMMATRIX m_rotMat = XMMatrixIdentity();
	XMMATRIX m_fudge = XMMatrixIdentity();
	XMVECTOR m_pos = XMVectorZero();
	float m_pitch, m_yaw, m_roll;
	XMVECTOR m_scale;

	//very basic physics
	bool m_physicsOn = false;
	float m_drag = 0.0f;
	XMVECTOR m_vel = XMVectorZero();
	XMVECTOR m_acc = XMVectorZero();
};
