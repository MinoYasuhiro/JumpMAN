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
	//アニメーションクリップをロードする。
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	m_animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);


	//モデルの初期化
	m_modelRender.Init("Assets/modelData/unityChan.tkm",m_animationClips,enAnimationClip_Num,enModelUpAxisY);

	//キャラクターコントローラーの初期化
	m_characterController.Init(25.0f, 75.0f, m_position);

	if (!m_fireBall)m_fireBall = FindGO<FireBall>("fireball");

	return true;
}

void Player::Update()
{
	//移動処理
	Move();

	//回転処理
	Rotate();

	//ステート管理。
	ManageState();

	//アニメーションの再生。
	PlayAnimation();

	//射撃処理
	Shoot();

	//モデルの更新。
	m_modelRender.Update();
}

void Player::Move()
{
	//xzの移動速度を0.0fにする。
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//左スティックの入力量を取得。
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//カメラの前方向と右方向のベクトルを持ってくる。
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	//y軸方向には移動させない。
	forward.y = 0.0f;
	right.y = 0.0f;

	float speed = 1.0f;

	//走る。 padのセレクトまたは、キーボードのスペース気が押されたら。
	if (g_pad[0]->IsPress(enButtonSelect))
	{
		//移動速度が３倍になる。
		speed = 3.0f;
	}


	//左スティックの入力量に500.0fを乗算。
	right *= stickL.x * 500.0f * speed;
	forward *= stickL.y * 500.0f * speed;

	//移動速度にスティックの入力量を加算する。
	m_moveSpeed += right + forward;

	//地面についていたら。
	if (m_characterController.IsOnGround())
	{
		//重力をなくす。
		m_moveSpeed.y = 0.0f;


		//Aボタンが押されたら。
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			//ジャンプする。
			m_moveSpeed.y = 700.0f;
		}

	}
	//地面についてなかったら。
	else
	{
		//重力を発生させる。
		m_moveSpeed.y -= 25.0f;
	}
	
	//キャラクターコントローラーを使って座標を移動させる。
	m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);

	//絵描きさんに座標を教える。
	m_modelRender.SetPosition(m_position);

}

void Player::Rotate()
{
	//xかzの移動側があったら（スティックの入力があったら.)
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//キャラクターの方向を変える。
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		//絵描きさんに回転を教える。
		m_modelRender.SetRotation(m_rotation);
	}
}

void Player::ManageState()
{	//地面についていなかったら。
	if (m_characterController.IsOnGround() == false)
	{
		//ステートを１にする　（１＝ジャンプ中）
		m_playerState = 1;
	}
	//地面についていて、xかzの移動速度があったら（スティックの入力があったら。）
	else if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		if (g_pad[0]->IsPress(enButtonSelect) == true)
		{
			//ステートを３にする。（３＝走っている）
			m_playerState = 3;
		}
		else
		{
			//ステートを２にする。（２＝歩いている）
			m_playerState = 2;
		}
	}
	else	//xとzの移動速度がなかったら。
	{
		//ステートを０にする。（０＝待機）
		m_playerState = 0;
	}
}


void Player::PlayAnimation()
	{
		//ステートによってアニメーションを変える。
		switch (m_playerState)
		{
			//ステートが０だったら
		case 0: //待機アニメーションを再生する。
			m_modelRender.PlayAnimation(enAnimationClip_Idle);
			break;
			//ステートが１だったら
		case 1://ジャンプアニメーションを再生する。
			m_modelRender.PlayAnimation(enAnimationClip_Jump);
			break;
			//ステートが２だったら
		case 2://歩くアニメーションを再生する。	
			m_modelRender.PlayAnimation(enAnimationClip_Walk);
			break;
			//ステートが３だったら
		case 3://走るアニメーションを再生する。
			m_modelRender.PlayAnimation(enAnimationClip_Run);
			break;
		}
	}

void Player::Shoot()
{
	//弾を生成して発射する処理をここに書く。
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

	//アイテム数表示用フォントレンダラーの描画処理
	//プレイヤーの座標を表示する。
	//表示する座標を設定する。
	m_itemCountFont.SetPosition({ -600.0f,100.0f,0.0f });
	//表示する色を設定する。
	m_itemCountFont.SetColor(g_vec4White);
	//プレイヤーの座標を取得
	Vector3 pos = GetPosition();
	//座標を文字列に変換
	wchar_t buf[128];
	swprintf(buf, 128, L"アイテムカウント%d", m_itemCount);
	//テキストをセット
	m_itemCountFont.SetText(buf);
	//フォントを描画
	m_itemCountFont.Draw(rc);
}


