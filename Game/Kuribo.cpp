#include "stdafx.h"
#include "Kuribo.h"
#include "Player.h"


Kuribo::Kuribo(){}

Kuribo::~Kuribo(){}

bool Kuribo::Start()
{
	m_modelRender.Init("Assets/modelData/Enemy.tkm");


	m_player = FindGO<Player>("player");

	m_charaCon.Init(
		20.0f,
		50.0f,
		m_position
	);

	//�����蔻�����������B

	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	 m_timer = 0.0f;

	 m_timerFlag = false;

	 m_isStamp = false;


	return true;
}

void Kuribo::Update()
{

	if (m_isStamp)
	{
		Death();
		return;
	}

	Chase();

	Rotation();

	ProcessCommonStateTransition();

	SearchPlayer();

	Stamp();

	m_modelRender.Update();
}

void Kuribo::Rotation()
{
	if (fabsf(m_moveSpeed.x) < 0.001f && fabsf(m_moveSpeed.z) < 0.001f)
	{
		return;
	}

	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);
	m_rotation.SetRotationY(-angle);

	m_modelRender.SetRotation(m_rotation);

	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);
}

void Kuribo::Chase()
{
	if (m_enemyState != enEnemyState_Chase)
	{
		return;
	}
	
	/*if (m_charaCon.IsOnGround()) {
		m_moveSpeed.y = 0.0f;
	}*/

	const float gravity = -1000.0f;
	if (!m_charaCon.IsOnGround())
	{
		m_moveSpeed.y += gravity;
	}
	else {
		m_moveSpeed.y = 0.0f;
	}

	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	
	Vector3 modelPosition = m_position;
	m_modelRender.SetPosition(modelPosition);
}

const bool Kuribo::SearchPlayer() const
{

	if (m_isStamp)
	{
		return false; 
	}

	Vector3 diff = m_player->GetPosition() - m_position;

	//�v���C���[�ɂ�����x�߂�������
	if (diff.LengthSq() <= 700.0 * 700.0f)
	{
		////�G�l�~�[����v���C���[�Ɍ������x�N�g���𐳋K������B
		//diff.Normalize();
		////�G�l�~�[�̐��ʃx�N�g���ƁA�G�l�~�[����v���C���[�Ɍ������x�N�g���̓��ς����߂�B
		//float cos = m_forward.Dot(diff);
		////���ς���p�x�����߂�B
		//float angle = acosf(cos);
		////�p�x��120����菬������΁B
		//if (angle <= (Math::PI / 180.0f * 170.0f))
		//{
		//	//�v���C���[���������B
		//	return true;
		//}
		return true;
	}
	//�v���C���[���������Ȃ������B
	return false;
}
//
void Kuribo::ProcessCommonStateTransition()
{
	Vector3 diff = m_player->GetPosition() - m_position;

	//�v���C���[����������
	if (SearchPlayer() == true)
	{
		//�x�N�g���𐳋K������B
		diff.Normalize();
		//�ړ����x��ݒ肷��B
		m_moveSpeed = diff * 400.0f;

		m_enemyState = enEnemyState_Chase;
	}

	else
	{
		m_enemyState = enEnemyState_Idle;
	}

}
//
void Kuribo::Stamp()
{
	//�v���C���[�̂����W�Ƃ����W���G�l�~�[�Ƌ߂��A�����W�̓G�l�~�[��荂���A�v���C���[���������Ɉړ����Ă���Ƃ�
	if (fabs(m_player->m_position.x - m_position.x) < 30.0f and	//fabs�͐�Βl�����B
		fabs(m_player->m_position.z - m_position.z) < 30.0f and
		fabs(m_player->m_position.y - m_position.y) < 100.0f and
		m_player->m_moveSpeed.y < 0.0f)
	{
		//���݂������Ƃɂ�蒵�˂�B
		m_player->m_moveSpeed.y =800.0f;

		m_scale = Vector3(1.0f, 0.3f, 1.0f);
		m_modelRender.SetScale(m_scale);

		m_modelRender.Update();
		m_player->m_modelRender.Update();
		
		m_charaCon.RemoveRigidBoby();
        m_charaCon.SetPosition(Vector3{ 0.0f, -10000.0f, 0.0f });

		m_timerFlag = true;
		m_isStamp = true;

		
		
	}
	
}

void Kuribo::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);


	////�v���C���[�̍��W��\������B
	////�\��������W��ݒ肷��B
	//m_fontRender.SetPosition({ -600.0f,100.0f,0.0f });
	////�\������F��ݒ肷��B
	//m_fontRender.SetColor(g_vec4White);
	////�v���C���[�̍��W���擾
	//Vector3 pos = m_player->GetPosition();
	////���W�𕶎���ɕϊ�
	//wchar_t buf[128];
	//swprintf(buf, 128, L"Player Pos: X=%.1f Y=%.1f Z=%.1f", pos.x, pos.y, pos.z);
	////�e�L�X�g���Z�b�g
	//m_fontRender.SetText(buf);
	////�t�H���g��`��
	//m_fontRender.Draw(rc);
}

void Kuribo::Death()
{
	if (m_timerFlag)
	{
		m_timer += 1.0f;

		if (m_timer >= 40.0f)
		{
			//delete����
			DeleteGO(this);
		}
	}
}