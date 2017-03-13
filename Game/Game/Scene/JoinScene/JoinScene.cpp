#include "stdafx.h"
#include "JoinScene.h"
#include "../TitleScene/TitleScene.h"
#include "../SoloScene/SoloScene.h"
#include "../GameScene/GameScene.h"
#include "../Fade/Fade.h"

JoinScene::JoinScene()
{
}

JoinScene::~JoinScene()
{
}

bool JoinScene::Start()
{
	return true;
}

void JoinScene::Update()
{
	SceneChange();
}

void JoinScene::Render(CRenderContext& renderContext)
{

}

void JoinScene::SceneChange()
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