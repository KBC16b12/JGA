#pragma once

class Player;

/*!
 *@brief	ゲームシーン。
 */
class GameScene : public IGameObject
{
public:
	/*!
	 *@brief	コンストラクタ。
	 */
	GameScene();

	/*!
	 *@brief	デストラクタ。
	 */
	~GameScene();

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

	/*!
	*@brief	遅延描画関数。
	@details
	* ポストエフェクトの後で実行されます。HUDなどポストエフェクトの影響を受けたくない描画物はここでレンダリングしてください。
	*@param[in]		renderContext		レンダリングコンテキスト。
	*/
	void PostRender(CRenderContext& renderContext) override;

private:
	/*!
	*@brief	画面遷移関数。
	*/
	void SceneChange();

	CSoundSource*				m_bgm;							//!<BGMソース。

	CTexture*					m_SampleTex;						//!<サンプルのテクスチャ。
	CSprite						m_Sample;							//!<サンプルのスプライト。

	CTexture*					m_texture[10];
	CSprite						m_timesprite[3];
	CSprite						m_killsprite[2];

	CCamera						m_camera;								//!<カメラ。
	CLight						m_light;								//!<ライト。

	Player*						m_player;

	RunStat						m_runstat = enFadeIn;

	SceneData					m_scenedata;

	int m_time;				//タイマー
	int m_killcount;		//キル数
};

extern GameScene* g_gameScene;
