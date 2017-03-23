#include "stdafx.h"
#include "../Fade/Fade.h"
#include "../GameScene/GameScene.h"
#include "../MenuScene/MenuScene.h"
#include "../ResultScene/ResultScene.h"
#include "Bar/Bar.h"
#include "Player/Player.h"
#include "../../Map/Map.h"
#include "../../Camera/GameCamera.h"

GameScene* g_gameScene = nullptr;

GameScene::GameScene()
{
	m_map = NewGO<Map>(0);
}

void GameScene::Init(std::vector<SMapInfo> map_data)
{
	m_map->Init(map_data);
}

GameScene::~GameScene()
{
	m_bgm->Stop();
	DeleteGO(m_bgm);
	DeleteGO(m_player);
	DeleteGO(m_map);
	g_gameScene = nullptr;
}

bool GameScene::Start()
{
	m_player = NewGO<Player>(0);
	m_bgm = NewGO<CSoundSource>(0);
	m_bgm->Init("Assets/sound/GameBGM.wav");
	m_bgm->Play(true);

	//ライトを初期化。
	m_light.SetAmbinetLight(CVector3::One);

	return true;
}

void GameScene::Update()
{
	SceneChange();
}

/*!
*@brief	描画関数。
*/
void GameScene::Render(CRenderContext& renderContext)
{
}

/*!
*@brief	描画関数。
*/
void GameScene::PostRender(CRenderContext& renderContext)
{
	//m_Sample.Draw(renderContext);
}

/*!
*@brief	画面遷移関数。
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
		SetActiveFlags(true);
		if (Pad(0).IsTrigger(enButtonStart))
		{
			m_scenedata = enMenu;

			m_runstat = enFadeOut;

			SetActiveFlags(false);
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
			m_runstat = enRun;
			g_gameScene->SetActiveFlag(false);
			if (m_scenedata != enMenu)
			{
				//自分を削除。
				DeleteGO(this);
			}
			return;
		}
		break;
	default:
		break;
	}
}

void GameScene::SetActiveFlags(bool flag)
{
	m_player->SetActiveFlag(flag);
	if (flag)
	{
		m_bgm->Play(true);
	}
	else
	{
		m_bgm->Stop();
	}
	m_map->SetActiveFlag(flag);
}