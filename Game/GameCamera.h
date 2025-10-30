#pragma once
class Player;
class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

	Vector3 m_toCameraPos; //注視点から視点までのベクトル
	Player* m_player = nullptr;

};

