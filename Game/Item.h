#pragma once
class Player;
class Nokonoko;
class Item : public IGameObject
{
public:
	Item();
	~Item();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
	void Rotation();

	ModelRender m_modelRender;
	Quaternion m_qot;
	Vector3 m_position;
	Player* m_player;
	float m_timer;
	Nokonoko* m_newNokonoko;

	
	
};

