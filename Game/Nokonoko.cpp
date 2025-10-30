#include "stdafx.h"
#include "Nokonoko.h"
#include "Player.h"
#include "Item.h"

Nokonoko::Nokonoko(){}

Nokonoko::~Nokonoko(){}

bool Nokonoko::Start()
{
	m_modelRender.Init("Assets/modelData/unityChan.tkm");

	m_item = FindGO<Item>("item");

	m_player = FindGO<Player>("player");

	m_charaCon.Init(
		20.0f,
		50.0f,
		m_position
	);


	return true;
}

void Nokonoko::Update()
{
	Chase();

	Rotation();

	ProcessCommonStateTransition();

	SearchPlayer();

	Stamp();

	m_modelRender.Update();
}

void Nokonoko::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}

void Nokonoko::Rotation()
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

void Nokonoko::Chase()
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

const bool Nokonoko::SearchPlayer() const
{
	Vector3 diff = m_player->GetPosition() - m_position;

	//�v���C���[�ɂ�����x�߂�������
	if (diff.LengthSq() <= 700.0 * 700.0f)
	{
		return true;
	}
	//�v���C���[���������Ȃ������B
	return false;
}

void Nokonoko::ProcessCommonStateTransition()
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

	void Nokonoko::Stamp()
	{
		//�v���C���[�̂����W�Ƃ����W���G�l�~�[�Ƌ߂��A�����W�̓G�l�~�[��荂���A�v���C���[���������Ɉړ����Ă���Ƃ�
		if (fabs(m_player->m_position.x - m_position.x) < 30.0f and	//fabs�͐�Βl�����B
			fabs(m_player->m_position.z - m_position.z) < 30.0f and
			fabs(m_player->m_position.y - m_position.y) < 100.0f and
			m_player->m_moveSpeed.y < 0.0f)
		{
			//���݂������Ƃɂ�蒵�˂�B
			m_player->m_moveSpeed.y = 800.0f;

			m_player->m_modelRender.Update();

			m_item = NewGO<Item>(0, "item");

			m_item->m_position = m_position;

			//delete����
			DeleteGO(this);
		}

	}
