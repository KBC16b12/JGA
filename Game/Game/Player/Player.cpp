#include "stdafx.h"
#include "Player.h"
#include "../Bar/Bar.h"

Player::Player()
{
	m_maxhp = m_hp = 500;

	m_bar = NewGO<Bar>(0);
	m_bar->SetBarPos({ -592.95f, 320.0f });
	m_bar->SetBarMaxSize({ 230.5f, 14.2f });
	m_bar->SetGaugePos({ -600.0f, 320.0f });
	m_bar->SetGaugeMaxSize({ 245.0f, 31.5f });
	m_bar->SetBarPath("Assets/sprite/Green.png");
	m_bar->SetGaugePath("Assets/sprite/Black.png");
	m_bar->SetBarBackPath("Assets/sprite/Black.png");
	m_bar->SetData(m_hp, m_maxhp);
	m_bar->SetBerQuarter(Bar::enBarQuarter::enQuaLeft);
}

Player::~Player()
{
	DeleteGO(m_bar);
}

bool Player::Start()
{
	skinModelData.LoadModelData("Assets/modelData/snowman.X", NULL);
	skinModel.Init(&skinModelData);
	g_defaultLight.SetAmbinetLight(CVector3::One);
	skinModel.SetLight(&g_defaultLight);	//デフォルトライトを設定。
	rotation.SetRotation(CVector3(0.0f, 1.0f, 0.0f), CMath::DegToRad(0.0f));

	//キャラクタコントローラの初期化。
	characterController.Init(0.5f, 1.0f, position);
	characterController.SetGravity(0.0f);

	return true;
}

void Player::Update()
{
	UpdateHPBar();
}

void Player::Render(CRenderContext& renderContext)
{

}

void Player::UpdateHPBar()
{
	if (0 < m_hp)
	{
		m_hp--;
	}
	if (50.0f < (float)m_hp / (float)m_maxhp * 100.0f)
	{
		m_bar->SetBarPath("Assets/sprite/Green.png");
	}
	else if (10.0f < (float)m_hp / (float)m_maxhp * 100.0f)
	{
		m_bar->SetBarPath("Assets/sprite/Blue.png");
	}
	else
	{
		m_bar->SetBarPath("Assets/sprite/Red.png");
	}
	m_bar->SetData(m_hp, m_maxhp);

	Move();

	//ワールド行列の更新
	skinModel.Update(position, CQuaternion::Identity/*rotation*/, CVector3::One);
	//アニメーションの更新
	Animation.Update(1.0f / 50.0f);
}

void Player::Move()
{
	CVector3 l_moveSpeed = characterController.GetMoveSpeed()/*CVector3::Zero*/;
	CMatrix l_pmatrix = skinModel.GetWorldMatrix();

	CVector3 l_moveX;
	CVector3 l_moveZ;

	//CVector3 l_moveSpeed.y = characterController.GetMoveSpeed();

	l_moveX.x = l_pmatrix.m[0][0];
	l_moveX.y = l_pmatrix.m[0][1];
	l_moveX.z = l_pmatrix.m[0][2];
	l_moveX.Normalize();
	l_moveX.Scale(1.0f);

	l_moveZ.x = l_pmatrix.m[2][0];
	l_moveZ.y = l_pmatrix.m[2][1];
	l_moveZ.z = l_pmatrix.m[2][2];
	l_moveZ.Normalize();
	l_moveZ.Scale(1.0f);

	if (Pad(0).IsPress(enButtonUp))
	{
		l_moveSpeed.Add(l_moveZ);
	}
	if (Pad(0).IsPress(enButtonDown))
	{
		l_moveSpeed.Subtract(l_moveZ);
	}
	if (Pad(0).IsPress(enButtonLeft))
	{
		l_moveSpeed.Subtract(l_moveX);
	}
	if (Pad(0).IsPress(enButtonRight))
	{
		l_moveSpeed.Add(l_moveX);
	}

	/*if (characterController.IsJump() == false && Pad(0).IsPress(enButtonRB3))
	{
		characterController.Jump();
		l_moveSpeed.y += 20.0f;
		Isjump == true;
	}*/

	if (Pad(0).IsPress(enButtonRB3))
	{
		characterController.Jump();
		l_moveSpeed.y += 2.5f;
		Isjump == true;
	}

	//決定した移動速度をキャラクタコントローラーに設定。
	characterController.SetMoveSpeed(l_moveSpeed);
	//キャラクターコントローラーを実行。
	characterController.Execute();
	//実行結果を受け取る。
	position = characterController.GetPosition();

	if (l_moveSpeed.y <= 0)
	{
		characterController.SetGravity(-5.0f);
	}

	//rotation.SetRotation(CVector3(0.0f, 1.0f, 0.0f), CMath::DegToRad(angle));
}

void Player::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext,m_camera->GetViewMatrix(),m_camera->GetProjectionMatrix());
}