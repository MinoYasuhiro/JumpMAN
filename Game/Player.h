#pragma once
class FireBall;	
class Player :public IGameObject
{
public:
	Player();
	~Player();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
	//移動処理
	void Move();
	//回転処理。
	void Rotate();
	//ステート管理
	void ManageState();
	//アニメーション管理
	void PlayAnimation();
	const Vector3& GetPosition() const
	{
		return m_position;
	}
	//射撃処理
	void Shoot();

	ModelRender m_modelRender;
	Vector3 m_moveSpeed;	//移動速度
	CharacterController m_characterController;
	Vector3 m_position;
	Quaternion m_rotation;
	FireBall* m_fireBall = nullptr;
	FontRender m_itemCountFont;	//アイテム数表示用フォントレンダラー
	

	int m_playerState;
	int m_itemCount = 0;

	//アニメーションの再生
	enum EnAnimationClip {		//アニメーション
		enAnimationClip_Idle,	//立ち	
		enAnimationClip_Jump,	//ジャンプ
		enAnimationClip_Walk,	//歩く
		enAnimationClip_Run,	//走る
		enAnimationClip_Num,	//総数
	};
	AnimationClip m_animationClips[enAnimationClip_Num];	//アニメーションクリップの総数の配列

};

