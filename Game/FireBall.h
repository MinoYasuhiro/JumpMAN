#pragma once
class Player;
class FireBall : public IGameObject
{
public:
	FireBall();
	~FireBall();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

	ModelRender m_modelRender;
	Vector3 m_position;
	Vector3 m_moveSpeed;
	CharacterController m_charaCon;
	Quaternion m_rotation;
	CollisionObject*m_collisionObject;
	Player* m_player = nullptr;
	bool m_isShoot = false;

	float m_timer = 0.0f;
};

