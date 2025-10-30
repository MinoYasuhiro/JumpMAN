#include "stdafx.h"
#include "FireBall.h"
#include "Player.h"

FireBall::FireBall()
{
}

FireBall::~FireBall()
{
}

bool FireBall::Start()
{
	
	m_modelRender.Init("Assets/modelData/FireBall.tkm");
	//�ړ����x���v�Z�B
	m_moveSpeed = Vector3::AxisZ;
	m_rotation.Apply(m_moveSpeed);
	m_position += m_moveSpeed * 50.0f;
	m_moveSpeed *= 1200.0f;
	m_rotation.AddRotationDegY(360.0f);
	//��]��ݒ肷��B
	m_modelRender.SetRotation(m_rotation);

	//�R���W�������쐬����B
	m_collisionObject = NewGO<CollisionObject>(0);
	//����̎q���W�������쐬����B
	m_collisionObject->CreateSphere(m_position, m_rotation, 35.0f);
	//�R���W�����������ō폜����Ȃ��悤�ɂ���B
	m_collisionObject->SetIsEnableAutoDelete(false);

	m_player = FindGO<Player>("player");


	return true;
}

void FireBall::Update()
{
	//���W���ړ�������B
	m_position += m_moveSpeed * g_gameTime->GetFrameDeltaTime();
	//���f���̍��W���X�V����B
	m_modelRender.SetPosition(m_position);
	//�R���W�����̍��W���X�V����B
	m_collisionObject->SetPosition(m_position);

	//�^�C�}�[�����Z����B
	m_timer += g_gameTime->GetFrameDeltaTime();

	m_modelRender.Update();

	//�����[�܂�0.7f�ȏゾ������
	//if (m_timer >= 0.7f)
	//{
	//	//m_player->m_fireBall = nullptr;
	//	////�������g���폜����B
	//	//
	//	if (m_collisionObject)
	//	{
	//		nsK2Engine::CollisionObjectManager::GetInstance()->RemoveCollisionObject(m_collisionObject);
	//		DeleteGO(m_collisionObject);
	//		m_collisionObject = nullptr;
	//	}
	//	//DeleteGO(this);
	//	
	//	m_isShoot = true;  // Player�����폜����悤�ɓ`����
	//	return;
	//}



}

void FireBall::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
	
