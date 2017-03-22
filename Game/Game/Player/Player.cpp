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
}