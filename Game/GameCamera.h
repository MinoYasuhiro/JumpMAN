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

	Vector3 m_toCameraPos; //�����_���王�_�܂ł̃x�N�g��
	Player* m_player = nullptr;

};

