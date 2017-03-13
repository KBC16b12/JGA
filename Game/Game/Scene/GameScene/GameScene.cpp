#include "stdafx.h"
#include "GameScene.h"
#include "../TitleScene/TitleScene.h"
#include "Bar/Bar.h"
#include "Player/Player.h"
#include "../Fade/Fade.h"

GameScene* g_gameScene = NULL;

GameScene::GameScene()
{
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
}

/*!
*@brief	�`��֐��B
*/
void GameScene::Render(CRenderContext& renderContext)
{
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
		break;
	case enFadeOut:
		if (!g_Fade->IsExecute())
		{
			switch (m_scenedata)
			{
			case enGame:
				break;
			case enJoin:
				break;
			case enMenu:
				break;
			case enRanking:
				break;
			case enTitle:
				break;
			case enSolo:
				break;
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
