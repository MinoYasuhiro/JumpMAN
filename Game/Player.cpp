#include "stdafx.h"
#include "Player.h"
#include "FireBall.h"

Player::Player()
{

}

Player::~Player()
{

}

bool Player::Start()
{
	//�A�j���[�V�����N���b�v�����[�h����B
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	m_animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);


	//���f���̏�����
	m_modelRender.Init("Assets/modelData/unityChan.tkm",m_animationClips,enAnimationClip_Num,enModelUpAxisY);

	//�L�����N�^�[�R���g���[���[�̏�����
	m_characterController.Init(25.0f, 75.0f, m_position);

	if (!m_fireBall)m_fireBall = FindGO<FireBall>("fireball");

	return true;
}

void Player::Update()
{
	//�ړ�����
	Move();

	//��]����
	Rotate();

	//�X�e�[�g�Ǘ��B
	ManageState();

	//�A�j���[�V�����̍Đ��B
	PlayAnimation();

	//�ˌ�����
	Shoot();

	//���f���̍X�V�B
	m_modelRender.Update();
}

void Player::Move()
{
	//xz�̈ړ����x��0.0f�ɂ���B
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//���X�e�B�b�N�̓��͗ʂ��擾�B
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//�J�����̑O�����ƉE�����̃x�N�g���������Ă���B
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	//y�������ɂ͈ړ������Ȃ��B
	forward.y = 0.0f;
	right.y = 0.0f;

	float speed = 1.0f;

	//����B pad�̃Z���N�g�܂��́A�L�[�{�[�h�̃X�y�[�X�C�������ꂽ��B
	if (g_pad[0]->IsPress(enButtonSelect))
	{
		//�ړ����x���R�{�ɂȂ�B
		speed = 3.0f;
	}


	//���X�e�B�b�N�̓��͗ʂ�500.0f����Z�B
	right *= stickL.x * 500.0f * speed;
	forward *= stickL.y * 500.0f * speed;

	//�ړ����x�ɃX�e�B�b�N�̓��͗ʂ����Z����B
	m_moveSpeed += right + forward;

	//�n�ʂɂ��Ă�����B
	if (m_characterController.IsOnGround())
	{
		//�d�͂��Ȃ����B
		m_moveSpeed.y = 0.0f;


		//A�{�^���������ꂽ��B
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			//�W�����v����B
			m_moveSpeed.y = 700.0f;
		}

	}
	//�n�ʂɂ��ĂȂ�������B
	else
	{
		//�d�͂𔭐�������B
		m_moveSpeed.y -= 25.0f;
	}
	
	//�L�����N�^�[�R���g���[���[���g���č��W���ړ�������B
	m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);

	//�G�`������ɍ��W��������B
	m_modelRender.SetPosition(m_position);

}

void Player::Rotate()
{
	//x��z�̈ړ�������������i�X�e�B�b�N�̓��͂���������.)
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//�L�����N�^�[�̕�����ς���B
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		//�G�`������ɉ�]��������B
		m_modelRender.SetRotation(m_rotation);
	}
}

void Player::ManageState()
{	//�n�ʂɂ��Ă��Ȃ�������B
	if (m_characterController.IsOnGround() == false)
	{
		//�X�e�[�g���P�ɂ���@�i�P���W�����v���j
		m_playerState = 1;
	}
	//�n�ʂɂ��Ă��āAx��z�̈ړ����x����������i�X�e�B�b�N�̓��͂���������B�j
	else if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		if (g_pad[0]->IsPress(enButtonSelect) == true)
		{
			//�X�e�[�g���R�ɂ���B�i�R�������Ă���j
			m_playerState = 3;
		}
		else
		{
			//�X�e�[�g���Q�ɂ���B�i�Q�������Ă���j
			m_playerState = 2;
		}
	}
	else	//x��z�̈ړ����x���Ȃ�������B
	{
		//�X�e�[�g���O�ɂ���B�i�O���ҋ@�j
		m_playerState = 0;
	}
}


void Player::PlayAnimation()
	{
		//�X�e�[�g�ɂ���ăA�j���[�V������ς���B
		switch (m_playerState)
		{
			//�X�e�[�g���O��������
		case 0: //�ҋ@�A�j���[�V�������Đ�����B
			m_modelRender.PlayAnimation(enAnimationClip_Idle);
			break;
			//�X�e�[�g���P��������
		case 1://�W�����v�A�j���[�V�������Đ�����B
			m_modelRender.PlayAnimation(enAnimationClip_Jump);
			break;
			//�X�e�[�g���Q��������
		case 2://�����A�j���[�V�������Đ�����B	
			m_modelRender.PlayAnimation(enAnimationClip_Walk);
			break;
			//�X�e�[�g���R��������
		case 3://����A�j���[�V�������Đ�����B
			m_modelRender.PlayAnimation(enAnimationClip_Run);
			break;
		}
	}

void Player::Shoot()
{
	//�e�𐶐����Ĕ��˂��鏈���������ɏ����B
	if (m_itemCount > 0)
	{
		if (g_pad[0]->IsTrigger(enButtonB))
		{
			m_fireBall = NewGO<FireBall>(0, "fireball");

			m_fireBall->m_position = m_position;

			m_fireBall->m_position.y += 50.0f;

			m_itemCount--;
		}
	}

	/*if (m_fireBall != nullptr)
	{
		if (m_fireBall->m_isShoot)
		{
			DeleteGO(m_fireBall);
			m_fireBall = nullptr;
		}
	}*/
}
 
void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);

	//�A�C�e�����\���p�t�H���g�����_���[�̕`�揈��
	//�v���C���[�̍��W��\������B
	//�\��������W��ݒ肷��B
	m_itemCountFont.SetPosition({ -600.0f,100.0f,0.0f });
	//�\������F��ݒ肷��B
	m_itemCountFont.SetColor(g_vec4White);
	//�v���C���[�̍��W���擾
	Vector3 pos = GetPosition();
	//���W�𕶎���ɕϊ�
	wchar_t buf[128];
	swprintf(buf, 128, L"�A�C�e���J�E���g%d", m_itemCount);
	//�e�L�X�g���Z�b�g
	m_itemCountFont.SetText(buf);
	//�t�H���g��`��
	m_itemCountFont.Draw(rc);
}


