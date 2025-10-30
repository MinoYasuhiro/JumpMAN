#pragma once

#include "Level3DRender/LevelRender.h"

class Player;
class BackGround;
class GameCamera;
class Kuribo;
class Nokonoko;
class Kuppa;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	ModelRender m_modelRender;
	Vector3 m_pos;
	Player* m_player = nullptr;
	BackGround* m_backGround = nullptr;
	GameCamera* m_gameCamera = nullptr;
	Kuribo* m_kuribo = nullptr;
	Kuribo* m_kuribo1 = nullptr;
	Kuribo* m_kuribo2 = nullptr;
	Nokonoko* m_nokonoko = nullptr;
};

