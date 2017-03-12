#include "stdafx.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "Bar/Bar.h"
#include "Player/Player.h"

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

	//カメラを初期化。
	m_camera.SetPosition({ 0.0f, 0.0f, -700.0f });
	m_camera.SetNear(400.0f);
	m_camera.SetFar(1000.0f);
	m_camera.Update();

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
*@brief	画面遷移関数。
*/
void GameScene::SceneChange()
{
	if (Pad(0).IsTrigger(enButtonStart)) {
		//タイトル画面に遷移する。
		NewGO<TitleScene>(0);
		DeleteGO(this);
		return;
	}
}
