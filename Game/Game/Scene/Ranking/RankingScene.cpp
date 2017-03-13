#include "stdafx.h"
#include "RankingScene.h"
#include "../SoloScene/SoloScene.h"
#include "../TitleScene/TitleScene.h"
#include "../Fade/Fade.h"

RankingScene::RankingScene()
{
}

RankingScene::~RankingScene()
{
}

bool RankingScene::Start()
{
	return true;
}

void RankingScene::Update()
{
	SceneChange();
}

void RankingScene::PostRender(CRenderContext& renderContext)
{
}

void RankingScene::SceneChange()
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
			//©•ª‚ğíœB
			DeleteGO(this);
			return;
		}
		break;
	default:
		break;
	}
}
