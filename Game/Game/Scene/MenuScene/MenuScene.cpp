#include "stdafx.h"
#include "MenuScene.h"
#include "../Fade/Fade.h"

MenuScene::MenuScene()
{
}

MenuScene::~MenuScene()
{
}

bool MenuScene::Start()
{
	return true;
}

void MenuScene::Update()
{
	SceneChange();
}

void MenuScene::Render(CRenderContext& renderContext)
{

}

void MenuScene::SceneChange()
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