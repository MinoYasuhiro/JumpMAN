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
	//�ړ�����
	void Move();
	//��]�����B
	void Rotate();
	//�X�e�[�g�Ǘ�
	void ManageState();
	//�A�j���[�V�����Ǘ�
	void PlayAnimation();
	const Vector3& GetPosition() const
	{
		return m_position;
	}
	//�ˌ�����
	void Shoot();

	ModelRender m_modelRender;
	Vector3 m_moveSpeed;	//�ړ����x
	CharacterController m_characterController;
	Vector3 m_position;
	Quaternion m_rotation;
	FireBall* m_fireBall = nullptr;
	FontRender m_itemCountFont;	//�A�C�e�����\���p�t�H���g�����_���[
	

	int m_playerState;
	int m_itemCount = 0;

	//�A�j���[�V�����̍Đ�
	enum EnAnimationClip {		//�A�j���[�V����
		enAnimationClip_Idle,	//����	
		enAnimationClip_Jump,	//�W�����v
		enAnimationClip_Walk,	//����
		enAnimationClip_Run,	//����
		enAnimationClip_Num,	//����
	};
	AnimationClip m_animationClips[enAnimationClip_Num];	//�A�j���[�V�����N���b�v�̑����̔z��

};

