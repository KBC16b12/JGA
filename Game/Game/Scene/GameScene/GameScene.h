#pragma once

class Player;

/*!
 *@brief	�Q�[���V�[���B
 */
class GameScene : public IGameObject
{
public:
	/*!
	 *@brief	�R���X�g���N�^�B
	 */
	GameScene();

	/*!
	 *@brief	�f�X�g���N�^�B
	 */
	~GameScene();

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

	/*!
	*@brief	�x���`��֐��B
	@details
	* �|�X�g�G�t�F�N�g�̌�Ŏ��s����܂��BHUD�Ȃǃ|�X�g�G�t�F�N�g�̉e�����󂯂����Ȃ��`�敨�͂����Ń����_�����O���Ă��������B
	*@param[in]		renderContext		�����_�����O�R���e�L�X�g�B
	*/
	void PostRender(CRenderContext& renderContext) override;

private:
	/*!
	*@brief	��ʑJ�ڊ֐��B
	*/
	void SceneChange();

	CSoundSource*				m_bgm;							//!<BGM�\�[�X�B

	CTexture*					m_SampleTex;						//!<�T���v���̃e�N�X�`���B
	CSprite						m_Sample;							//!<�T���v���̃X�v���C�g�B

	CCamera						m_camera;								//!<�J�����B
	CLight						m_light;								//!<���C�g�B

	Player*						m_player;

	RunStat						m_runstat = enFadeIn;

	SceneData					m_scenedata;
};

extern GameScene* g_gameScene;
