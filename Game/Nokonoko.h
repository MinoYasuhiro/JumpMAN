#pragma once
class Player;
class Item;
class Nokonoko:public IGameObject
{
public:
	enum EnEnemyState {
		enEnemyState_Idle,	//待機
		enEnemyState_Chase, //追跡。
	};

public:
	Nokonoko();
	~Nokonoko();
	virtual bool Start() override;
	virtual void Update() override;
	void Render(RenderContext& rc) override;
	void Chase();	//追跡処理
	virtual const bool SearchPlayer() const;
	const Vector3& GetPosition() const
	{
		return m_position;
	}
	virtual void ProcessCommonStateTransition();
	void Rotation();
	virtual void Stamp();	//踏みつけ処理

	ModelRender					m_modelRender;
	EnEnemyState				m_enemyState = enEnemyState_Idle;			//エネミーステート
	Vector3						m_position;
	Vector3						m_moveSpeed;
	CharacterController			m_charaCon;
	Player*						m_player = nullptr;
	Vector3						m_forward = Vector3::AxisZ;
	Quaternion					m_rotation;
	FontRender					m_fontRender;
	Item* m_item;
};

