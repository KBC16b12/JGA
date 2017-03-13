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

private:
	/*!
	*@brief	画面遷移関数。
	*/
	void SceneChange();

	CSoundSource*				m_bgm;							//!<BGMソース。

	CTexture*					m_texture;							//!<背景のテクスチャ。
	CSprite						m_sprite;							//!<背景のスプライト。

	CCamera						m_camera;								//!<カメラ。
	CLight						m_light;								//!<ライト。

	Player*						m_player;

	RunStat						m_runstat = enFadeIn;

	SceneData					m_scenedata;
};

extern GameScene* g_gameScene;
