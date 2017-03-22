#pragma once
#include "tkEngine/character/tkCharacterController.h"

class Bar;

class Player : public IGameObject
{
public:
	Player();
	~Player();

	/*!
	*@brief	�J�n�֐��B
	*@details
	* �������Ȃǂ����̊֐��Ɏ������Ă��������B</br>
	* ���̊֐���true��Ԃ��Ɩ{�ِ��͈ȍ~�̃t���[���ł͌Ă΂�Ȃ��Ȃ�܂��B</br>
	* �����ăQ�[���I�u�W�F�N�g�̏�Ԃ������������ɂȂ�Update�֐����Ă΂��悤�ɂȂ�܂��B</br>
	*@return	true���A���Ă����珉���������B
	*/
	bool Start() override;

	/*!
	*@brief	�X�V�֐��B
	*/
	void Update() override;

	/*!
	*@brief	�`��֐��B
	*/
	void Render(CRenderContext& renderContext);

	void SetCamera(CCamera* camera)
	{
		m_camera = camera;
	}

	void Move();

private:
	/*!
	*@brief	HP�o�[�X�V�֐��B
	*/
	void UpdateHPBar();

	Bar*			m_bar;
	int				m_hp;
	int				m_maxhp;

	CSkinModel				skinModel;					//�X�L�����f��
	CSkinModelData			skinModelData;				//�X�L�����f���f�[�^
	CQuaternion				rotation;					//��]
	CAnimation				Animation;					//�A�j���[�V����
	CCharacterController	characterController;		//�L�����N�^�\�R���g���[���[�B
	CVector3				position = { 0.0f, -20.0f, 0.0f };
	CCamera*				m_camera;

	int						currentAnimationNo;
	float					angle = 180;
	bool					Isjump;
};

