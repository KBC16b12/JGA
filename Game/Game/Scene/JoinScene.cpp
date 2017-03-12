#include "stdafx.h"
#include "JoinScene.h"
#include "TitleScene.h"

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
	if (Pad(0).IsTrigger(enButtonStart)) {
		//タイトル画面に遷移する。
		NewGO<TitleScene>(0);
		DeleteGO(this);
		return;
	}
}