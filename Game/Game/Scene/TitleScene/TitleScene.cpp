#include "stdafx.h"
#include "TitleScene.h"
#include "../GameScene/GameScene.h"
#include "../JoinScene/JoinScene.h"
#include "../MenuScene/MenuScene.h"
#include "../SoloScene/SoloScene.h"
#include "../Fade/Fade.h"

TitleScene::TitleScene()
{
	//バーの初期化
	m_TitleTex = TextureResources().LoadEx("Assets/sprite/Title.png");
	m_Title.Init(m_TitleTex);
	m_Title.SetSize({ (float)Engine().GetScreenWidth(),(float)Engine().GetScreenHeight() });
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
	m_Title.Draw(renderContext);
}

/*!
*@brief	画面遷移関数。
*/
void TitleScene::SceneChange()
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
		if (Pad(0).IsTrigger(enButtonA))
		{
			m_scenedata = enSolo;

			m_runstat = enFadeOut;
		}
		if (Pad(0).IsTrigger(enButtonB))
		{
		}
		break;
	case enFadeOut:
		if (!g_Fade->IsExecute())
		{
			switch (m_scenedata)
			{
			case enGame:

				break;
			case enJoin:
				break;
			case enMenu:
				break;
			case enRanking:
				break;
			case enTitle:
				break;
			case enSolo:
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