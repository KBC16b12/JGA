#pragma once
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();

	void Update();

	const CMatrix& GetViewMatrix() const
	{
		return m_camera.GetViewMatrix();
	}

	const CMatrix& GetProjectionMatrix() const
	{
		return m_camera.GetProjectionMatrix();
	}


private:
	CCamera				m_camera;

	CVector3			m_position;
	CVector3			m_look_position;
	
	float				m_angle;
};

extern GameCamera* g_gameCamera;