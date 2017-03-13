#include "stdafx.h"
#include "SoloScene.h"
#include "../TitleScene/TitleScene.h"
#include "../GameScene/GameScene.h"
#include "../Ranking/RankingScene.h"
#include "../MenuScene/MenuScene.h"
#include "../Fade/Fade.h"


SoloScene::SoloScene()
{
	//バーの初期化
	m_SoloTex = TextureResources().LoadEx("Assets/sprite/Title.png");
	m_Solo.Init(m_SoloTex);
	m_Solo.SetSize({ (float)Engine().GetScreenWidth(),(float)Engine().GetScreenHeight() });
}

SoloScene::~SoloScene()
{
	DeleteGO(m_bgm);
}

bool SoloScene::Start()
{
	m_bgm = NewGO<CSoundSource>(0);
	m_bgm->Init("Assets/sound/TitleBGM.wav");
	m_bgm->Play(true);
	return true;
}
void SoloScene::Update()
{
	SceneChange();
}

void SoloScene::PostRender(CRenderContext& renderContext)
{
	m_Solo.Draw(renderContext);
}

/*!
*@brief	画面遷移関数。
*/
void SoloScene::SceneChange()
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
			//自分を削除。
			DeleteGO(this);
			return;
		}
		break;
	default:
		break;
	}
}