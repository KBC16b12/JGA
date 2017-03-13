#pragma once
class JoinScene : public IGameObject
{
public:
	/*!
	*@brief	�R���X�g���N�^�B
	*/
	JoinScene();

	/*!
	*@brief	�f�X�g���N�^�B
	*/
	~JoinScene();

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

private:
	/*!
	*@brief	��ʑJ�ڊ֐��B
	*/
	void SceneChange();

	CSoundSource* m_bgm = NULL;

	CTexture*					m_texture;							//!<�w�i�̃e�N�X�`���B
	CSprite						m_sprite;							//!<�w�i�̃X�v���C�g�B

	RunStat						m_runstat = enFadeIn;

	SceneData					m_scenedata;
};

