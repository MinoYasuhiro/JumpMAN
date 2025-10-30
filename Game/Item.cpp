#include "stdafx.h"
#include "Item.h"
#include "Player.h"
#include "Nokonoko.h"

Item::Item() {}

Item::~Item(){}

bool Item::Start()
{
	m_modelRender.Init("Assets/modelData/Enemy.tkm");

	//����������
	//m_position.y = 30.0f;

	m_modelRender.SetPosition(m_position);

	m_player = FindGO<Player>("player");

	

	return true;
}

void Item::Update()
{
	Vector3 diff = m_player->m_position - m_position;
	if (diff.Length() <= 50.0f)
	{
		//�A�C�e���J�E���g�𑝂₷�B
		m_player->m_itemCount += 1;

		//�A�C�e�����폜����B
		DeleteGO(this);
	}
	//m_qot.AddRotationDegY(4.0);
	//m_modelRender.SetRotation(m_qot);

	m_timer += g_gameTime->GetFrameDeltaTime();

	if (m_timer >= 3.0f)
	{
		m_newNokonoko = NewGO<Nokonoko>(0, "newNokonoko");

		//�b���̃|�W�V�������m�R�m�R�ɓ`����B
		m_newNokonoko->m_position = m_position;

		m_newNokonoko->m_modelRender.SetPosition(m_newNokonoko->m_position);

		//���Ԍo�߂ŃA�C�e�����폜���ăG�l�~�[�𕜊�������B
		DeleteGO(this);
	}

	m_modelRender.Update();
}

void Item::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
