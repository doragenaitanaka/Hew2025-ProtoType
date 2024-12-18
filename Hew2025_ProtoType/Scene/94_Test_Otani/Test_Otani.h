/**	@file 	Test_Otani.h
*	@brief 	��J�p�̃e�X�g�V�[���N���X
*	@date	2024/12/14
*	@memo	�}�l�[�W���[�͐ÓI�����o�ϐ��Ȃ̂Ŏ擾�̂�
*/
#pragma once

// �C���N���[�h
#include"../00_BaseScene/BaseScene.h"
#include"../../Library/Code/self/02_SceneManager/SceneManager.h"
#include"../../Library/Code/self/10_Object/Object.h"

#include"../../Library/Code/self/04_DirextX_11/08_InputLayout/CInputLayout.h"
#include"../../Library/Code/self/04_DirextX_11/09_Shader/01_CVertexShader/CVertexShader.h"
#include"../../Library/Code/self/04_DirextX_11/09_Shader/02_PixelShader/CPixelShader.h"
#include"../../Library/Code/self/04_DirextX_11/10_Sampler/CSampler.h"

/**	@file	Test_Otani.h
*	@brief 	�A�c�p�̃e�X�g�V�[���N���X
*	@date	2024/05/21
*	@memo	���N���X�̏������z�֐����p�����Ă��闠�t��(������p�������h������)�Ɍp�����������o�֐���override�w��q���g�p���Ă���
*/
class Test_Otani :public BaseScene
{
public:
	/**	@brief 	�R���X�g���N�^
	*	* @date 2024/05/21
	*/
	Test_Otani();
	/**	@brief 	�f�X�g���N�^
	*	@date 2024/05/21
	*/
	~Test_Otani()override;
	/**	@brief 	�V�[���S�̂̏�����
	*	@date 2024/05/21
	*/
	void	Initialize(void)override;

	/**	@brief 	�V�[���S�̂̍X�V
	*	@date 2024/05/21
	*/
	void	Update(void)override;

	/**	@brief 	�V�[���S�̂̕`��
	*	@date 2024/05/21
	*/
	void	Draw(void)override;

	/**	@brief 	�V�[���S�̂̏I������
	*	@date 2024/05/21
	*/
	void	Finalize(void)override;

	//�e�X�g�p�̍��W�ϐ�
	XMFLOAT2 TestPos = { -200.0f, 0.0f };
	XMFLOAT2 TestPos2 = { 200.0f, 0.0f };
	//�T�C�Y
	XMFLOAT2 TestSize = { 100.0f,100.0f };
	XMFLOAT2 TestSize2 = { 100.0f,100.0f };

private:
	Object* p_TestObject;
	/** @brief ��ڂ̃I�u�W�F�N�g�p
	*   @date  2024/12/11
	*/
	Object* p_TestObject2;


	//--------------------------------------------------------------------------
	//		�`��֘A
	//--------------------------------------------------------------------------	
	CInputLayout* p_inputLayout;		//  ���̓��C�A�E�g
	CVertexShader* p_vertexShader;		//  ���_�V�F�[�_
	CPixelShader* p_pixelShader;		//  �s�N�Z���V�F�[�_
	CSampler* p_sampler;				// �T���v���[
	ID3D11BlendState* p_brendState;		// �A���t�@�u�����f�B���O�p�X�e�[�g
};