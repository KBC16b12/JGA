#include "stdafx.h"
#include "../Fade/Fade.h"
#include "../GameScene/GameScene.h"
#include "../MenuScene/MenuScene.h"
#include "../ResultScene/ResultScene.h"
#include "Bar/Bar.h"
#include "Player/Player.h"
#include "../../Map/Map.h"

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
	//BGM停止
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
}

/*!
*@brief	画面遷移関数。
*/
void GameScene::SceneChange()
{
	switch (m_runstat)
	{
	case enFadeIn:
		//フェードイン
		if (!g_Fade->IsExecute())
		{
			g_Fade->StartFadeIn();
			m_runstat = enRun;
		}
		break;
	case enRun:
		//動作中
		SetActiveFlags(true);
		//スタートボタン押下
		if (Pad(0).IsTrigger(enButtonStart))
		{
			//メニューへ遷移
			m_scenedata = enMenu;

			m_runstat = enFadeOut;

			SetActiveFlags(false);
			return;
		}
		if (Pad(0).IsTrigger(enButtonA))
		{
			//リザルトへ遷移
			m_scenedata = enResult;

			m_runstat = enFadeOut;

			g_Fade->StartFadeOut();
			return;
		}
		break;
	case enFadeOut:
		if (!g_Fade->IsExecute())
		{
			//画面生成
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
			
			//メニュー画面への遷移でない
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
	//ここで生成したオブジェクトの動作変更
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