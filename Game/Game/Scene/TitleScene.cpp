#include "stdafx.h"
#include "TitleScene.h"
#include "GameScene.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
	DeleteGO(m_bgm);
}

bool TitleScene::Start()
{
	m_bgm = NewGO<CSoundSource>(0);
	m_bgm->Init("Assets/sound/TitleBGM.wav");
	m_bgm->Play(true);
	return true;
}
void TitleScene::Update()
{
	SceneChange();
}

void TitleScene::PostRender(CRenderContext& renderContext)
{
}

/*!
*@brief	画面遷移関数。
*/
void TitleScene::SceneChange()
{
	if (Pad(0).IsTrigger(enButtonStart)) {
		//ゲーム画面に遷移する。
		g_gameScene = NewGO<GameScene>(0);
		DeleteGO(this);
		return;
	}
}