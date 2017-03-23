#pragma once

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
};

extern GameCamera* g_gameCamera;