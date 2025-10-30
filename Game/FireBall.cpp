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
	//移動速度を計算。
	m_moveSpeed = Vector3::AxisZ;
	m_rotation.Apply(m_moveSpeed);
	m_position += m_moveSpeed * 50.0f;
	m_moveSpeed *= 1200.0f;
	m_rotation.AddRotationDegY(360.0f);
	//回転を設定する。
	m_modelRender.SetRotation(m_rotation);

	//コリジョンを作成する。
	m_collisionObject = NewGO<CollisionObject>(0);
	//球状の子リジョンを作成する。
	m_collisionObject->CreateSphere(m_position, m_rotation, 35.0f);
	//コリジョンが自動で削除されないようにする。
	m_collisionObject->SetIsEnableAutoDelete(false);

	m_player = FindGO<Player>("player");


	return true;
}

void FireBall::Update()
{
	//座標を移動させる。
	m_position += m_moveSpeed * g_gameTime->GetFrameDeltaTime();
	//モデルの座標を更新する。
	m_modelRender.SetPosition(m_position);
	//コリジョンの座標を更新する。
	m_collisionObject->SetPosition(m_position);

	//タイマーを加算する。
	m_timer += g_gameTime->GetFrameDeltaTime();

	m_modelRender.Update();

	//たいーまが0.7f以上だったら
	//if (m_timer >= 0.7f)
	//{
	//	//m_player->m_fireBall = nullptr;
	//	////自分自身を削除する。
	//	//
	//	if (m_collisionObject)
	//	{
	//		nsK2Engine::CollisionObjectManager::GetInstance()->RemoveCollisionObject(m_collisionObject);
	//		DeleteGO(m_collisionObject);
	//		m_collisionObject = nullptr;
	//	}
	//	//DeleteGO(this);
	//	
	//	m_isShoot = true;  // Player側が削除するように伝える
	//	return;
	//}



}

void FireBall::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
	
