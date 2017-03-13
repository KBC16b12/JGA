#pragma once
class JoinScene : public IGameObject
{
public:
	/*!
	*@brief	コンストラクタ。
	*/
	JoinScene();

	/*!
	*@brief	デストラクタ。
	*/
	~JoinScene();

	/*!
	*@brief	開始関数。
	*@details
	* 初期化などをこの関数に実装してください。</br>
	* この関数がtrueを返すと本館数は以降のフレームでは呼ばれなくなります。</br>
	* そしてゲームオブジェクトの状態が初期化完了になりUpdate関数が呼ばれるようになります。</br>
	*@return	trueが帰ってきたら初期化完了。
	*/
	bool Start() override;

	/*!
	*@brief	更新関数。
	*/
	void Update() override;

	/*!
	*@brief	描画関数。
	*/
	void Render(CRenderContext& renderContext);

private:
	/*!
	*@brief	画面遷移関数。
	*/
	void SceneChange();

	CSoundSource* m_bgm = NULL;

	CTexture*					m_texture;							//!<背景のテクスチャ。
	CSprite						m_sprite;							//!<背景のスプライト。

	RunStat						m_runstat = enFadeIn;

	SceneData					m_scenedata;
};

