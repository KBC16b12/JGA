#include "stdafx.h"
#include "../Fade/Fade.h"
#include "../GameScene/GameScene.h"
#include "../MenuScene/MenuScene.h"
#include "../TitleScene/TitleScene.h"

MenuScene::MenuScene()
{
	m_SampleTex = TextureResources().LoadEx("Assets/sprite/Menu.png");
	m_Sample.Init(m_SampleTex);
	m_Sample.SetSize({ (float)Engine().GetScreenWidth(),(float)Engine().GetScreenHeight() });
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

/*!
*@brief	描画関数。
*/
void MenuScene::PostRender(CRenderContext& renderContext)
{
	m_Sample.Draw(renderContext);
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
		if (Pad(0).IsTrigger(enButtonStart))
		{
			m_scenedata = enTitle;

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
			case enTitle:
				NewGO<TitleScene>(0);
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