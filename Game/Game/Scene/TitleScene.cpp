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
*@brief	��ʑJ�ڊ֐��B
*/
void TitleScene::SceneChange()
{
	if (Pad(0).IsTrigger(enButtonStart)) {
		//�Q�[����ʂɑJ�ڂ���B
		g_gameScene = NewGO<GameScene>(0);
		DeleteGO(this);
		return;
	}
}