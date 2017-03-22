#pragma once
#include "tkEngine/character/tkCharacterController.h"

class Bar;

class Player : public IGameObject
{
public:
	Player();
	~Player();

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

	void SetCamera(CCamera* camera)
	{
		m_camera = camera;
	}

	void Move();

private:
	/*!
	*@brief	HPバー更新関数。
	*/
	void UpdateHPBar();

	Bar*			m_bar;
	int				m_hp;
	int				m_maxhp;

	CSkinModel				skinModel;					//スキンモデル
	CSkinModelData			skinModelData;				//スキンモデルデータ
	CQuaternion				rotation;					//回転
	CAnimation				Animation;					//アニメーション
	CCharacterController	characterController;		//キャラクタ―コントローラー。
	CVector3				position = { 0.0f, -20.0f, 0.0f };
	CCamera*				m_camera;

	int						currentAnimationNo;
	float					angle = 180;
	bool					Isjump;
};

