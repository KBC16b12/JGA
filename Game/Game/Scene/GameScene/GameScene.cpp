#include "stdafx.h"
#include "../Fade/Fade.h"
#include "../GameScene/GameScene.h"
#include "../MenuScene/MenuScene.h"
#include "../ResultScene/ResultScene.h"
#include "Bar/Bar.h"
#include "Player/Player.h"

GameScene* g_gameScene = NULL;

GameScene::GameScene()
{
	m_killcount = 0;
	m_time = 999;
	m_SampleTex = TextureResources().LoadEx("Assets/sprite/Game.png");
	m_Sample.Init(m_SampleTex);
	m_Sample.SetSize({ (float)Engine().GetScreenWidth(),(float)Engine().GetScreenHeight() });
	
	for (int i = 0;i < 10;i++) {
		char cp[60];
		sprintf(cp, "Assets/sprite/NewNumber/%d.png", i);
		m_texture[i]= TextureResources().LoadEx(cp);
	}
	for (int i = 0;i < 3;i++) {
		m_timesprite[i].Init(m_texture[9]);
		m_timesprite[i].SetPosition({ -50.0f + i * 50,320.0f });
		m_timesprite[i].SetSize({ 50.0f,50.0f });
	}
	for (int i = 0;i < 2;i++) {
		m_killsprite[i].Init(m_texture[2]);
		m_killsprite[i].SetPosition({ 400.0f + i * 50,320.0f });
		m_killsprite[i].SetSize({ 50.0f,50.0f });
	}
}

GameScene::~GameScene()
{
	DeleteGO(m_bgm);
	DeleteGO(m_player);
}

bool GameScene::Start()
{
	m_player = NewGO<Player>(0);

	m_bgm = NewGO<CSoundSource>(0);
	m_bgm->Init("Assets/sound/GameBGM.wav");
	m_bgm->Play(true);

	//�J�������������B
	m_camera.SetPosition({ 0.0f, 0.0f, -700.0f });
	m_camera.SetNear(400.0f);
	m_camera.SetFar(1000.0f);
	m_camera.Update();

	//���C�g���������B
	m_light.SetAmbinetLight(CVector3::One);

	return true;
}

void GameScene::Update()
{
	SceneChange();


	if (m_time > 0) {
		m_time--;
	}

	int l_n1 = 0, l_n10 = 0, l_n100 = 0;

	l_n100 = m_time / 100;			//3���ڂ̐���
	l_n10 = (m_time %100 ) / 10;	//2���ڂ̐���
	l_n1 = m_time % 10;			    //1���ڂ̐���

	m_timesprite[0].SetTexture(m_texture[l_n100]);
	m_timesprite[1].SetTexture(m_texture[l_n10]);
	m_timesprite[2].SetTexture(m_texture[l_n1]);

	if (GetAsyncKeyState('2') & 0x8000) {
		if (m_killcount < 99) {
			m_killcount++;
		}
	}

	int l_num1 = 0, l_num10 = 0;
	
	l_num10 = (m_killcount % 100) / 10;
	l_num1 = m_killcount%10;
	
	m_killsprite[0].SetTexture(m_texture[l_num10]);
	m_killsprite[1].SetTexture(m_texture[l_num1]);
}

/*!
*@brief	�`��֐��B
*/
void GameScene::Render(CRenderContext& renderContext)
{
}

/*!
*@brief	�`��֐��B
*/
void GameScene::PostRender(CRenderContext& renderContext)
{
	m_Sample.Draw(renderContext);
	for (int i = 0;i < 3;i++) {
		m_timesprite[i].Draw(renderContext);
	}
	for (int i = 0;i < 2;i++) {
		m_killsprite[i].Draw(renderContext);
	}
}

/*!
*@brief	��ʑJ�ڊ֐��B
*/
void GameScene::SceneChange()
{
	switch (m_runstat)
	{
	case enFadeIn:
		if (!g_Fade->IsExecute())
		{
			g_Fade->StartFadeIn();
			m_runstat = enRun;
		}
		break;
	case enRun:
		if (Pad(0).IsTrigger(enButtonStart))
		{
			m_scenedata = enMenu;

			m_runstat = enFadeOut;

			g_Fade->StartFadeOut();
			return;
		}
		if (Pad(0).IsTrigger(enButtonA))
		{
			m_scenedata = enResult;

			m_runstat = enFadeOut;

			g_Fade->StartFadeOut();
			return;
		}
		break;
	case enFadeOut:
		if (!g_Fade->IsExecute())
		{
			switch (m_scenedata)
			{
			case enMenu:
				NewGO<MenuScene>(0);
				break;
			case enResult:
				NewGO<ResultScene>(0);
			default:
				break;
			}
			//�������폜�B
			DeleteGO(this);
			return;
		}
		break;
	default:
		break;
	}
}
