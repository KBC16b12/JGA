#include "stdafx.h"
#include "../Fade/Fade.h"
#include "../GameScene/GameScene.h"
#include "../JoinScene/JoinScene.h"
#include "../WaitScene/WaitScene.h"

WaitScene::WaitScene()
{
	m_SampleTex = TextureResources().LoadEx("Assets/sprite/Wait.png");
	m_Sample.Init(m_SampleTex);
	m_Sample.SetSize({ (float)Engine().GetScreenWidth(),(float)Engine().GetScreenHeight() });
}

WaitScene::~WaitScene()
{
}

bool WaitScene::Start()
{
	return true;
}

void WaitScene::Update()
{
	SceneChange();
}

void WaitScene::PostRender(CRenderContext& renderContext)
{
	m_Sample.Draw(renderContext);
}

void WaitScene::SceneChange()
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
		if (Pad(0).IsTrigger(enButtonStart))
		{
			m_scenedata = enJoin;

			m_runstat = enFadeOut;

			g_Fade->StartFadeOut();
			return;
		}
		if (Pad(0).IsTrigger(enButtonA))
		{
			m_scenedata = enGame;

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
			case enGame:
				g_gameScene = NewGO<GameScene>(0);
				break;
			case enJoin:
				NewGO<JoinScene>(0);
				break;
			default:
				break;
			}
			//自分を削除。
			DeleteGO(this);
			return;
		}
		break;
	default:
		break;
	}
}