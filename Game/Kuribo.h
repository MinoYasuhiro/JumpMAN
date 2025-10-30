#pragma once

class Player;
class Kuribo : public IGameObject
	{

	public:
		enum EnEnemyState {
			enEnemyState_Idle,	//�ҋ@
			enEnemyState_Chase, //�ǐՁB
		};
public:
	Kuribo();
	~Kuribo();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
	void Chase();	//�ǐՏ���
	const bool SearchPlayer() const;
	const Vector3& GetPosition() const
	{
		return m_position;
	}
	void ProcessCommonStateTransition();
	void Rotation();
	void Stamp();	//���݂�����
	void Death();

	ModelRender					m_modelRender;
	EnEnemyState				m_enemyState = enEnemyState_Idle;			//�G�l�~�[�X�e�[�g
	Vector3						m_position;
	Vector3						m_moveSpeed;
	CharacterController			m_charaCon;
	Player* m_player = nullptr;
	Vector3						m_forward = Vector3::AxisZ;
	Quaternion					m_rotation;
	FontRender					m_fontRender;
	Vector3						m_scale;
	float m_timer = 0.0f;
	bool m_timerFlag;
	bool m_isStamp;
	Vector3 m_pos;


};
