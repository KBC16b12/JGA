#include "stdafx.h"
#include "Player.h"
#include "../Bar/Bar.h"
#include "../Camera/GameCamera.h"

Player::Player()
{
	//HP�ݒ�
	m_maxhp = m_hp = 15;

	m_HPbar = NewGO<Bar>(0);
	m_HPbar->SetBarPos({ -592.95f, 320.0f });
	m_HPbar->SetBarMaxSize({ 230.5f, 14.2f });
	m_HPbar->SetGaugePos({ -600.0f, 320.0f });
	m_HPbar->SetGaugeMaxSize({ 245.0f, 31.5f });
	m_HPbar->SetBarPath("Assets/sprite/Green.png");
	m_HPbar->SetGaugePath("Assets/sprite/Black.png");
	m_HPbar->SetBarBackPath("Assets/sprite/Black.png");
	m_HPbar->SetData(m_hp, m_maxhp);
	m_HPbar->SetBerQuarter(Bar::enBarQuarter::enQuaLeft);
}

Player::~Player()
{
	DeleteGO(m_HPbar);
}

bool Player::Start()
{
	skinModelData.LoadModelData("Assets/modelData/snowman.X", NULL);
	skinModel.Init(&skinModelData);
	g_defaultLight.SetAmbinetLight(CVector3::One);
	skinModel.SetLight(&g_defaultLight);	//�f�t�H���g���C�g��ݒ�B
	rotation.SetRotation(CVector3(0.0f, 1.0f, 0.0f), CMath::DegToRad(0.0f));

	//�L�����N�^�R���g���[���̏������B
	characterController.Init(0.5f, 1.0f, position);

	return true;
}

void Player::Update()
{
	UpdateHPBar();
}

void Player::UpdateHPBar()
{
	if (m_maxhp <= 0)
	{
		return;
	}

	//HP50%�ȏ�
	if (50.0f < (float)m_hp / (float)m_maxhp * 100.0f)
	{
		m_HPbar->SetBarPath("Assets/sprite/Green.png");
	}
	//HP10%�ȏ�50%�ȉ�
	else if (10.0f < (float)m_hp / (float)m_maxhp * 100.0f)
	{
		m_HPbar->SetBarPath("Assets/sprite/Blue.png");
	}
	//HP10%����
	else
	{
		m_HPbar->SetBarPath("Assets/sprite/Red.png");
	}
	m_bar->SetData(m_hp, m_maxhp);

	Move();

	//���[���h�s��̍X�V
	skinModel.Update(position, rotation, { 5.0f,5.0f,5.0f });
	//�A�j���[�V�����̍X�V
	Animation.Update(1.0f / 50.0f);
}

void Player::Move()
{
	float move;
	move = -5.0f; //�ړ����x
	CVector3 l_moveSpeed = characterController.GetMoveSpeed();
	CVector3 l_moveX;
	CVector3 l_moveZ;
	l_moveSpeed.x = 0.0f;
	l_moveSpeed.z = 0.0f;
	CMatrix l_pmatrix = skinModel.GetWorldMatrix();

	l_moveX.x = l_pmatrix.m[0][0];
	l_moveX.y = l_pmatrix.m[0][1];
	l_moveX.z = l_pmatrix.m[0][2];
	l_moveX.Normalize();
	l_moveX.Scale(move);

	l_moveZ.x = l_pmatrix.m[2][0];
	l_moveZ.y = l_pmatrix.m[2][1];
	l_moveZ.z = l_pmatrix.m[2][2];
	l_moveZ.Normalize();
	l_moveZ.Scale(move);

	/*�ړ�*/
	l_moveX.Scale(Pad(0).GetLStickXF());
	l_moveZ.Scale(Pad(0).GetLStickYF());
	l_moveSpeed.Add(l_moveX);
	l_moveSpeed.Add(l_moveZ);
	
	/*�A���O��*/
	if (Pad(0).GetRStickXF() > 0.0f)
	{
		angle += 5.0f;
	}
	if (Pad(0).GetRStickXF() < 0.0f)
	{
		angle -= 5.0f;
	}

	/*�W�����v*/
	if (characterController.IsJump() == false && Pad(0).IsPress(enButtonRB1))
	{
		characterController.Jump();
		l_moveSpeed.y += 15.0f;
	}

	//���肵���ړ����x���L�����N�^�R���g���[���[�ɐݒ�B
	characterController.SetMoveSpeed(l_moveSpeed);
	//�L�����N�^�[�R���g���[���[�����s�B
	characterController.Execute();
	//���s���ʂ��󂯎��B
	position = characterController.GetPosition();


	rotation.SetRotation(CVector3(0.0f, 1.0f, 0.0f), CMath::DegToRad(angle));
}

void Player::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext,g_gameCamera->GetViewMatrix(),g_gameCamera->GetProjectionMatrix());
}