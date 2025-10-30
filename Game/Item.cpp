#include "stdafx.h"
#include "Item.h"
#include "Player.h"
#include "Nokonoko.h"

Item::Item() {}

Item::~Item(){}

bool Item::Start()
{
	m_modelRender.Init("Assets/modelData/Enemy.tkm");

	//少し浮かす
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
		//アイテムカウントを増やす。
		m_player->m_itemCount += 1;

		//アイテムを削除する。
		DeleteGO(this);
	}
	//m_qot.AddRotationDegY(4.0);
	//m_modelRender.SetRotation(m_qot);

	m_timer += g_gameTime->GetFrameDeltaTime();

	if (m_timer >= 3.0f)
	{
		m_newNokonoko = NewGO<Nokonoko>(0, "newNokonoko");

		//甲羅のポジションをノコノコに伝える。
		m_newNokonoko->m_position = m_position;

		m_newNokonoko->m_modelRender.SetPosition(m_newNokonoko->m_position);

		//時間経過でアイテムを削除してエネミーを復活させる。
		DeleteGO(this);
	}

	m_modelRender.Update();
}

void Item::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
