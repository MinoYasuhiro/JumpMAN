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

	//当たり判定を可視化する。

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

	//プレイヤーにある程度近かったら
	if (diff.LengthSq() <= 700.0 * 700.0f)
	{
		////エネミーからプレイヤーに向かうベクトルを正規化する。
		//diff.Normalize();
		////エネミーの正面ベクトルと、エネミーからプレイヤーに向かうベクトルの内積を求める。
		//float cos = m_forward.Dot(diff);
		////内積から角度を求める。
		//float angle = acosf(cos);
		////角度が120°より小さければ。
		//if (angle <= (Math::PI / 180.0f * 170.0f))
		//{
		//	//プレイヤーを見つけた。
		//	return true;
		//}
		return true;
	}
	//プレイヤーを見つけられなかった。
	return false;
}
//
void Kuribo::ProcessCommonStateTransition()
{
	Vector3 diff = m_player->GetPosition() - m_position;

	//プレイヤーを見つけたら
	if (SearchPlayer() == true)
	{
		//ベクトルを正規化する。
		diff.Normalize();
		//移動速度を設定する。
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
	//プレイヤーのｘ座標とｚ座標がエネミーと近く、ｙ座標はエネミーより高く、プレイヤーが下方向に移動しているとき
	if (fabs(m_player->m_position.x - m_position.x) < 30.0f and	//fabsは絶対値を取る。
		fabs(m_player->m_position.z - m_position.z) < 30.0f and
		fabs(m_player->m_position.y - m_position.y) < 100.0f and
		m_player->m_moveSpeed.y < 0.0f)
	{
		//踏みつけたことにより跳ねる。
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


	////プレイヤーの座標を表示する。
	////表示する座標を設定する。
	//m_fontRender.SetPosition({ -600.0f,100.0f,0.0f });
	////表示する色を設定する。
	//m_fontRender.SetColor(g_vec4White);
	////プレイヤーの座標を取得
	//Vector3 pos = m_player->GetPosition();
	////座標を文字列に変換
	//wchar_t buf[128];
	//swprintf(buf, 128, L"Player Pos: X=%.1f Y=%.1f Z=%.1f", pos.x, pos.y, pos.z);
	////テキストをセット
	//m_fontRender.SetText(buf);
	////フォントを描画
	//m_fontRender.Draw(rc);
}

void Kuribo::Death()
{
	if (m_timerFlag)
	{
		m_timer += 1.0f;

		if (m_timer >= 40.0f)
		{
			//deleteする
			DeleteGO(this);
		}
	}
}